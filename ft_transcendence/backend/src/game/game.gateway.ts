import { Socket, Server } from 'socket.io';
import { Logger } from '@nestjs/common';
import { InjectDataSource } from '@nestjs/typeorm';
import {
  SubscribeMessage,
  WebSocketGateway,
  WebSocketServer,
} from '@nestjs/websockets';
import { DataSource } from 'typeorm';
import { v4 as uuidv4 } from 'uuid';
import { Match } from '../entities/Match';
import { User } from '../entities/User';
import { SocketsService } from 'src/sockets.service';
import Ball from './Ball';
import Player from './Player';
import { UserGateway } from 'src/user/user.gateway';

enum MODE_GAME {
  SPEED_MODE,
  TIME_MODE,
}

// This code declares the Match interface, which describes the data structure of a pong game.
// The match has a unique id, as well as two players and a ball.
interface Game {
  mode: MODE_GAME;
  id: string;
  playerA: Player;
  playerB: Player;
  ball: Ball;
  limit_max: number;
  started_at: Date;
  match_db: Match;
}

interface matchmaking_mode {
  mode: MODE_GAME;
  limit_max: number;
}

@WebSocketGateway()
export class GameGateway {
  // @param dataSource - The data source for the application.
  constructor(
    @InjectDataSource()
    private dataSource: DataSource,
    private socketService: SocketsService,
    private userGateway: UserGateway,
  ) {}

  @WebSocketServer()
  server: Server;
  private speed_mode: Set<Game> = new Set<Game>();
  private time_mode: Set<Game> = new Set<Game>();
  private client_in_MM = new Map<Socket, matchmaking_mode>();

  emit_payload = (client: Socket, dest: string, payload: any) => {
    try {
      client?.emit(dest, payload);
    } catch (e) {
      Logger.error('emit_payload, trying to send: ' + payload);
      Logger.error('From ' + client.id + ' to event: ' + dest);
      Logger.error('Error is: ' + e);
    }
  };

  sleep = (ms: number) => {
    const date = Date.now();
    let currentDate = null;
    do {
      currentDate = Date.now();
    } while (currentDate - date < ms);
  };

  async handle_db(match: Game, winner: Player, loser: Player): Promise<void> {
    try {
      match.match_db.winnerScore = winner.score;
      match.match_db.loserScore = loser.score;
      match.match_db.createdAt = match.started_at;
      const winner_id = this.socketService.getUserId(winner.socket);
      const loser_id = this.socketService.getUserId(loser.socket);
      const winnerUser = await this.dataSource.manager.findOne(User, {
        where: { id: winner_id },
        relations: ['wonMatches'],
      });
      const loserUser = await this.dataSource.manager.findOne(User, {
        where: { id: loser_id },
        relations: ['lostMatches'],
      });
      match.match_db.winner = winnerUser;
      match.match_db.loser = loserUser;
      winnerUser.wonMatches.push(match.match_db);
      loserUser.lostMatches.push(match.match_db);
      await this.dataSource.manager.save(Match, match.match_db);
      await this.dataSource.manager.save(User, winnerUser);
      await this.dataSource.manager.save(User, loserUser);
    } catch (err) {
      Logger.error('handle_db: ' + err);
    }
  }

  // This code is creating a loop that will run 30 times per second.
  // The loop checks the position of the ball and makes sure it does not go out of bounds.
  // If the ball does go out of bounds, the score is updated and the ball is reset.
  // If the score is 5, the game is ended.
  // Physics is based on the perforamance of the server, so it is not 100% accurate.
  speed_mode_interval: NodeJS.Timeout = setInterval(() => {
    const match_to_del = [];
    for (const game of this.speed_mode) {
      try {
        game.ball.move();
        game.ball.bouncePaddle(game.playerA);
        game.ball.bouncePaddle(game.playerB);
        if (game.ball.bounceEdge()) {
          if (game.ball.x < 10) game.playerB.score += 1;
          else game.playerA.score += 1;
          this.send_score(game);
          const win_state = this.handle_win(game);
          if (win_state) {
            match_to_del.push(game);
            continue;
          } else game.ball.reset();
        }
        this.server.to(String(game.id)).emit('GetPositionBall', {
          x: game.ball.x,
          y: game.ball.y,
        });
      } catch (e) {
        Logger.error('speed_mode_interval: ', e);
      }
    }
    for (const match of match_to_del) {
      this.speed_mode.delete(match);
    }
  }, 1000 / 30); // 30 times per second

  time_mode_interval: NodeJS.Timeout = setInterval(() => {
    const match_to_del = [];
    for (const game of this.time_mode) {
      try {
        game.ball.move();
        game.ball.bouncePaddle(game.playerA);
        game.ball.bouncePaddle(game.playerB);
        if (game.ball.bounceEdge()) {
          if (game.ball.x < 10) game.playerB.score += 1;
          else game.playerA.score += 1;
          this.send_score(game);
          game.ball.reset();
        }
        const win_state = this.handle_win(game);
        if (win_state) {
          match_to_del.push(game);
          continue;
        }
        this.server.to(String(game.id)).emit('GetPositionBall', {
          x: game.ball.x,
          y: game.ball.y,
        });
      } catch (e) {
        Logger.error('time_mode_interval: ', e);
      }
    }
  }, 1000 / 30);

  // A player socket has been disconnected, so we check which game he was in,
  //and send a message to the othe  player of the game, telling him that he won.
  handleDisconnect(client: Socket): void {
    const match_to_del = [];
    for (const match of this.speed_mode) {
      let tmp;
      if (match.playerA?.socket.id == client.id) {
        this.handle_db(match, match.playerB, match.playerA);
        tmp = match.playerB.socket;
      } else if (match.playerB?.socket.id == client.id) {
        this.handle_db(match, match.playerA, match.playerB);
        tmp = match.playerA.socket;
      } else tmp = null;
      if (tmp) {
        this.emit_payload(tmp, 'GameOver', {
          winner: 'you',
        });
        match_to_del.push(match);
        tmp?.leave(match.id);
        break;
      }
    }
    for (const match of match_to_del) {
      this.speed_mode.delete(match);
    }
    return;
  }

  // This function is called when a player has won a game.
  handlePlayerWin(game: Game, winner: Player, loser: Player): void {
    this.handle_db(game, winner, loser);
    this.emit_payload(winner.socket, 'GameOver', { winner: 'you' });
    this.emit_payload(loser.socket, 'GameOver', { winner: 'not_you' });
    game.playerA.socket?.leave(game.id);
    game.playerB.socket?.leave(game.id);
    this.userGateway.updateAllUsers();
  }

  // This function checks if any player has reached a score of 5.
  //If so, it will emit a message to the player that won and to the player that lost.
  //It will then remove both players from the room.
  handle_win(game: Game): boolean {
    if (game.mode == MODE_GAME.TIME_MODE) {
      try {
        if (game.started_at.getTime() + 25 * 1000 < Date.now()) {
          if (game.playerA.score > game.playerB.score)
            this.handlePlayerWin(game, game.playerA, game.playerB);
          else if (game.playerB.score > game.playerA.score)
            this.handlePlayerWin(game, game.playerB, game.playerA);
          else this.handlePlayerWin(game, game.playerA, game.playerB);
          return true;
          // need to handle draw
        } else return false;
      } catch (e) {
        Logger.error('handle_win: ', e);
      }
    } else if (game.mode == MODE_GAME.SPEED_MODE) {
      try {
        if (game.playerA.score == game.limit_max) {
          this.handlePlayerWin(game, game.playerA, game.playerB);
          return true;
        } else if (game.playerB.score == game.limit_max) {
          this.handlePlayerWin(game, game.playerB, game.playerA);
          return true;
        }
        return false;
      } catch (e) {
        Logger.error('handle_win: ', e);
      }
    } else {
      console.log('cant figure out the mode');
    }
  }

  // This code is responsible for updating the scores of the two players in the game.
  //It is called every time a player scores a point.
  send_score(game: Game): void {
    try {
      game.playerA.socket?.emit('PlayerScore', game.playerA.score);
      game.playerA.socket?.emit('EnemyScore', game.playerB.score);
      //need to switch the score to properly display it on the clientB side
      game.playerB.socket?.emit('PlayerScore', game.playerA.score);
      game.playerB.socket?.emit('EnemyScore', game.playerB.score);
    } catch (e) {
      Logger.error('send_score: ', e);
    }
  }

  // This code sends the player's position to the client
  emit_pos(game: Game): void {
    this.emit_payload(game.playerA.socket, 'Player_Position', {
      x: game.playerA.x,
      y: game.playerA.y,
    });
    this.emit_payload(game.playerA.socket, 'EnemyPos', {
      x: game.playerB.x,
      y: game.playerB.y,
    });
    this.emit_payload(game.playerB.socket, 'Player_Position', {
      x: game.playerB.x,
      y: game.playerB.y,
    });
    this.emit_payload(game.playerB.socket, 'EnemyPos', {
      x: game.playerA.x,
      y: game.playerA.y,
    });
  }

  // This function joins two players to a room and then removes them from matchmaking
  join_n_leave(playerA: Socket, playerB: Socket, id: string): void {
    playerA?.join(id);
    playerB?.join(id);
    playerA?.leave('matchmaking');
    playerB?.leave('matchmaking');
    this.client_in_MM.delete(playerA);
    this.client_in_MM.delete(playerB);
  }

  check_mode(playerA: Socket, playerB: Socket): boolean {
    if (
      this.client_in_MM.get(playerA).mode != this.client_in_MM.get(playerB).mode
    )
      return false;
    if (
      this.client_in_MM.get(playerA).limit_max !=
      this.client_in_MM.get(playerB).limit_max
    )
      return false;
    return true;
  }

  // handles movement of the player
  @SubscribeMessage('Move')
  handleMove(client: Socket, key_press: string): void {
    if (!key_press) {
      Logger.error('handleMove: no key received, client: ' + client.id);
      this.emit_payload(client, 'Error', { error: 'no key' });
      return;
    }
    if (key_press !== 'ArrowUp' && key_press !== 'ArrowDown') {
      Logger.error('handleMove: wrong key received, client: ' + client.id);
      this.emit_payload(client, 'Error', { error: 'wrong key' });
      return;
    }
    try {
      for (const game of this.speed_mode) {
        let tmp: any;
        if (game.playerA?.socket.id == client.id) tmp = game.playerA;
        else if (game.playerB?.socket.id == client.id) tmp = game.playerB;
        else tmp = null;
        if (!tmp) continue;
        // if 'w' is pressed and player is not at the top of the screen
        if (key_press === 'ArrowUp' && tmp.y > 10) {
          tmp.y -= 10;
          this.emit_pos(game);
        }
        // else if 's' is pressed and player is not at the bottom of the screen
        else if (key_press === 'ArrowDown' && tmp.y < 290) {
          tmp.y += 10;
          this.emit_pos(game);
        }
      }
      for (const game of this.time_mode) {
        let tmp: any;
        if (game.playerA?.socket.id == client.id) tmp = game.playerA;
        else if (game.playerB?.socket.id == client.id) tmp = game.playerB;
        else tmp = null;
        if (!tmp) continue;
        // if 'w' is pressed and player is not at the top of the screen
        if (key_press === 'ArrowUp' && tmp.y > 10) {
          tmp.y -= 10;
          this.emit_pos(game);
        }
        // else if 's' is pressed and player is not at the bottom of the screen
        else if (key_press === 'ArrowDown' && tmp.y < 290) {
          tmp.y += 10;
          this.emit_pos(game);
        }
      }
    } catch (e) {
      Logger.error('handleMove: ', e);
    }
  }

  //payload need to contains:
  // - game mode ( speed mode or time mode)
  // - score max

  // This function handles when a client attempts to join the matchmaking process.

  //payload.game_mode => game_mode selected by the player
  //payload.limit_max => limit_max selected by the player
  @SubscribeMessage('matchmaking')
  handleJoin_MM(client: Socket, payload: any): void {
    Logger.log('matchmaking');
    console.log('payload = ', payload);

    if (this.client_in_MM.has(client)) return;
    this.client_in_MM.set(client, {
      mode:
        payload.game_mode == 'speed'
          ? MODE_GAME.SPEED_MODE
          : MODE_GAME.TIME_MODE,
      limit_max: payload.limit_max,
    });
    client.join('matchmaking');

    const clients_in_mm = this.server.sockets.adapter.rooms.get('matchmaking');
    if (clients_in_mm?.size >= 2) {
      const it = clients_in_mm.values();
      const playerA = this.server.sockets.sockets.get(it.next().value);
      const playerB = this.server.sockets.sockets.get(it.next().value);
      if (this.check_mode(playerA, playerB) == false) return;
      const id = uuidv4();
      const tmp_match: Game = {
        mode: this.client_in_MM.get(playerA)?.mode,
        id: id,
        playerA: new Player(playerA, 10),
        playerB: new Player(playerB, 580),
        ball: new Ball(),
        limit_max: this.client_in_MM.get(playerA).limit_max,
        started_at: new Date(),
        match_db: new Match(),
      };
      tmp_match.match_db.id = id;
      if (tmp_match.mode == MODE_GAME.TIME_MODE) {
        console.log('adding match to time mode array');
        this.time_mode.add(tmp_match);
      } else if (tmp_match.mode == MODE_GAME.SPEED_MODE) {
        this.speed_mode.add(tmp_match);
      }
      this.join_n_leave(playerA, playerB, id);
      this.server.sockets.to(id).emit('matchmaking', true);

      this.sleep(50);
      this.emit_pos(tmp_match);
    }
    return;
  }
}
