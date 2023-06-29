import { Server, Socket } from 'socket.io';
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
import { User, Status } from '../entities/User';
import { SocketsService } from 'src/sockets.service';
import Ball from './Ball';
import Player from './Player';
import { UserGateway } from 'src/user/user.gateway';
import { WINDOWWIDTH } from './const_game';

enum MODE_GAME {
  SPEED_MODE,
  TIME_MODE,
}

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
  private client_in_MM: Map<Socket, matchmaking_mode> = new Map<
    Socket,
    matchmaking_mode
  >(); 

  emit_payload = async (
    client: Socket,
    dest: string,
    payload: any,
  ): Promise<void> => {
    try {
      client?.emit(dest, payload); 
    } catch (e) {
      Logger.error('emit_payload, trying to send: ' + payload); 
      Logger.error('From ' + client.id + ' to event: ' + dest); 
      Logger.error('Error is: ' + e); 
    }
  };

  sleep = (ms: number): void => {
    const date: number = Date.now(); 
    let currentDate = null; 
    do {
      currentDate = Date.now(); 
    } while (currentDate - date < ms); 
  };

  async handle_db(match: Game, winner: Player, loser: Player, draw: boolean) {
    try {
      match.match_db.winnerScore = winner.score; 
      match.match_db.loserScore = loser.score; 
      match.match_db.createdAt = match.started_at; 
      const winner_id: string = this.socketService.getUserId(winner.socket); 
      const loser_id: string = this.socketService.getUserId(loser.socket); 
      const winnerUser: User = await this.dataSource.manager.findOne(User, {
        where: { id: winner_id },
        relations: ['wonMatches'],
      }); 
      const loserUser: User = await this.dataSource.manager.findOne(User, {
        where: { id: loser_id },
        relations: ['lostMatches'],
      }); 
      match.match_db.winner = winnerUser; 
      match.match_db.loser = loserUser; 
      match.match_db.draw = draw ? 1 : 0; 
      winnerUser.wonMatches.push(match.match_db); 
      winnerUser.status = Status.ONLINE;
      loserUser.lostMatches.push(match.match_db); 
      loserUser.status = Status.ONLINE;
      await this.dataSource.manager.save(Match, match.match_db); 
      await this.dataSource.manager.save(User, winnerUser); 
      await this.dataSource.manager.save(User, loserUser); 
    } catch (err) {
      Logger.error('handle_db: ' + err); 
    }
  }

  speed_mode_interval: NodeJS.Timeout = setInterval((): void => {
    const match_to_del: Game[] = []; 
    for (const game of this.speed_mode) {
      try {
        game.ball.move(); 
        game.ball.bouncePaddle(game.playerA); 
        game.ball.bouncePaddle(game.playerB); 
        if (game.ball.bounceEdge()) {
          if (game.ball.x < 10)
            game.playerB.score += 1; 
          else game.playerA.score += 1; 
          this.send_score(game); 
          const win_state: boolean = this.handle_win_speed(game); 
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
  }, 1000 / 120); 

  time_mode_interval: NodeJS.Timeout = setInterval((): void => {
    const match_to_del: Game[] = []; 
    for (const game of this.time_mode) {
      try {
        game.ball.move(); 
        game.ball.bouncePaddle(game.playerA); 
        game.ball.bouncePaddle(game.playerB); 
        if (game.ball.bounceEdge()) {
          if (game.ball.x < 10)
            game.playerB.score += 1; 
          else game.playerA.score += 1; 
          this.send_score(game); 
          game.ball.reset(); 
        }
        const win_state: boolean = this.handle_win_time(game); 
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
    for (const match of match_to_del) {
      this.time_mode.delete(match); 
    }
  }, 1000 / 120); 


  //USE ONLY INSIDE HANDLEDICONNECT
  async test_match(
    match: Game,
    client: Socket,
    match_to_del: Game[],
  ): Promise<boolean> {
    let tmp: any;
    if (match.playerA?.socket.id === client.id) {
      await this.handle_db(match, match.playerB, match.playerA, false); 
      tmp = match.playerB.socket; 
    } else if (match.playerB?.socket.id === client.id) {
      await this.handle_db(match, match.playerA, match.playerB, false); 
      tmp = match.playerA.socket; 
    } else tmp = null;
    if (!tmp) return false;
    await this.emit_payload(tmp, 'GameOver', { winner: 'you' }); 
    match_to_del.push(match); 
    tmp?.leave(match.id); 
    return true;
  }

  async handleDisconnect(client: Socket): Promise<void> {
    Logger.log('client disconnected: ', client.id);
    const match_to_del: Game[] = []; 
    if (this.client_in_MM.has(client)) {
      this.client_in_MM.delete(client); 
    }
    for (const match of this.speed_mode) {
      const result: boolean = await this.test_match(
        match,
        client,
        match_to_del,
      ); 
      if (result) break; 
    }
    for (const match of match_to_del) {
      this.speed_mode.delete(match); 
    }
    match_to_del.length = 0;
    for (const match of this.time_mode) {
      const result: boolean = await this.test_match(
        match,
        client,
        match_to_del,
      ); 
      if (result) break; 
    }
    for (const match of match_to_del) {
      this.time_mode.delete(match); 
    }
    return;
  }
  
  async handlePlayerWin(
    game: Game,
    winner: Player,
    loser: Player,
  ): Promise<void> {
    if (winner.score == loser.score) {
      await this.handle_db(game, winner, loser, true); 
      await this.emit_payload(loser.socket, 'GameOver', { winner: 'you' }); 
      await this.emit_payload(winner.socket, 'GameOver', { winner: 'you' }); 
    } else {
      await this.handle_db(game, winner, loser, false); 
      await this.emit_payload(winner.socket, 'GameOver', { winner: 'you' }); 
      await this.emit_payload(loser.socket, 'GameOver', { winner: 'not_you' }); 
    }
    game.playerA.socket?.leave(game.id); 
    game.playerB.socket?.leave(game.id); 
    await this.userGateway.updateAllUsers(); 
  }

  handle_win_time(game: Game): boolean {
    try {
      if (game.started_at.getTime() + game.limit_max * 1000 > Date.now()) {
        return false; 
      }
      if (game.playerA.score > game.playerB.score)
        this.handlePlayerWin(game, game.playerA, game.playerB);
      else this.handlePlayerWin(game, game.playerB, game.playerA); 
      return true;
    } catch (e) {
      Logger.error('handle_win: ', e); 
    }
  }

  handle_win_speed(game: Game): boolean {
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
  }

  async send_score(game: Game): Promise<void> {
    try {
      game.playerA.socket?.emit('PlayerScore', game.playerA.score); 
      game.playerA.socket?.emit('EnemyScore', game.playerB.score); 
      game.playerB.socket?.emit('PlayerScore', game.playerA.score); 
      game.playerB.socket?.emit('EnemyScore', game.playerB.score); 
    } catch (e) {
      Logger.error('send_score: ', e); 
    }
  }

  async emit_pos(game: Game): Promise<void> {
    await this.emit_payload(game.playerA.socket, 'Player_Position', {
      x: game.playerA.x,
      y: game.playerA.y,
    }); 
    await this.emit_payload(game.playerA.socket, 'EnemyPos', {
      x: game.playerB.x,
      y: game.playerB.y,
    }); 
    await this.emit_payload(game.playerB.socket, 'Player_Position', {
      x: game.playerB.x,
      y: game.playerB.y,
    }); 
    await this.emit_payload(game.playerB.socket, 'EnemyPos', {
      x: game.playerA.x,
      y: game.playerA.y,
    }); 
  }

  async check_mode(playerA: Socket, playerB: Socket): Promise<boolean> {
    return (
      this.client_in_MM.get(playerA).limit_max ==
      this.client_in_MM.get(playerB).limit_max
    );
  }

  async handle_match(
    client: Socket,
    game: Game,
    key_press: string,
  ): Promise<void> {
    let tmp: any;
    if (game.playerA?.socket.id == client.id)
      tmp = game.playerA; 
    else if (game.playerB?.socket.id == client.id)
      tmp = game.playerB; 
    else tmp = null;
    if (!tmp) return;
    if (key_press === 'ArrowUp' && tmp.y > 10) {
      tmp.y -= 10;
      await this.emit_pos(game); 
    }
    else if (key_press === 'ArrowDown' && tmp.y < 290) {
      tmp.y += 10;
      await this.emit_pos(game); 
    }
  }
  
  @SubscribeMessage('Move')
  async handleMove(client: Socket, key_press: string): Promise<void> {
    if (!key_press) {
      Logger.error('handleMove: no key received, client: ' + client.id);
      await this.emit_payload(client, 'Error', { error: 'no key' });
      return;
    }
    if (key_press !== 'ArrowUp' && key_press !== 'ArrowDown') {
      Logger.error('handleMove: wrong key received, client: ' + client.id);
      await this.emit_payload(client, 'Error', { error: 'wrong key' });
      return;
    }
    try {
      for (const game of this.speed_mode) {
        await this.handle_match(client, game, key_press);
      }
      for (const game of this.time_mode) {
        await this.handle_match(client, game, key_press);
      }
    } catch (e) {
      Logger.error('handleMove: ', e);
    }
  }

  async join_n_leave(
    playerA: Socket,
    playerB: Socket,
    id: string,
  ): Promise<void> {
    playerA?.join(id);
    playerB?.join(id);
    playerA?.leave('matchmaking');
    playerB?.leave('matchmaking');
    this.client_in_MM.delete(playerA);
    this.client_in_MM.delete(playerB);
  }

  @SubscribeMessage('matchmaking')
  async handleJoin_MM(
    client: Socket,
    payload: {
      game_mode: string;
      limit_max: number;
    },
  ): Promise<void> {
    Logger.log('matchmaking from ' + client.id);
    if (this.client_in_MM.has(client)) return;
    this.client_in_MM.set(client, {
      mode:
        payload.game_mode == 'speed'
          ? MODE_GAME.SPEED_MODE
          : MODE_GAME.TIME_MODE,
      limit_max:
        payload.game_mode == 'speed'
          ? payload.limit_max
          : payload.limit_max * 10,
    });
    client.join('matchmaking');
    const clients_in_mm = this.server.sockets.adapter.rooms.get('matchmaking');
    if (clients_in_mm?.size >= 2) {
      const it = clients_in_mm.values();
      const playerA = this.server.sockets.sockets.get(it.next().value);
      const playerB = this.server.sockets.sockets.get(it.next().value);
      if ((await this.check_mode(playerA, playerB)) === false) return;
      const id: string = uuidv4();
      const tmp_match: Game = {
        mode: this.client_in_MM.get(playerA)?.mode,
        id: id,
        playerA: new Player(playerA, 10),
        playerB: new Player(playerB, WINDOWWIDTH - 30),
        ball: new Ball(),
        limit_max: this.client_in_MM.get(playerA).limit_max,
        started_at: new Date(),
        match_db: new Match(),
      };
      tmp_match.match_db.id = id;
      if (tmp_match.mode == MODE_GAME.TIME_MODE) {
        this.time_mode.add(tmp_match);
      } else if (tmp_match.mode == MODE_GAME.SPEED_MODE) {
        this.speed_mode.add(tmp_match);
      }
      await this.join_n_leave(playerA, playerB, id);
      let tmp = await this.dataSource.manager.findOne(User, {
        where: { id: this.socketService.getUserId(tmp_match.playerA.socket) },
      });
      if (!tmp)
        Logger.error('handleJoin_MM: user not found, id: ' + tmp_match.playerA.socket.id);
      tmp.status = Status.PLAYING;
      await this.dataSource.manager.save(tmp);
      tmp = await this.dataSource.manager.findOne(User, {
        where: { id: this.socketService.getUserId(tmp_match.playerB.socket) },
      });
      tmp.status = Status.PLAYING;
      await this.dataSource.manager.save(tmp);
      await this.userGateway.updateAllUsers(); 

      this.server.sockets.to(id).emit('matchmaking', true);
      this.sleep(50);
      await this.emit_pos(tmp_match);
    }
  }

  @SubscribeMessage('quit-matchmaking')
  async handle_quit_matchmaking(client: Socket): Promise<void> {
    Logger.log('quit-matchmaking');
    if (this.client_in_MM.has(client)) {
      client.leave('matchmaking');
      this.client_in_MM.delete(client);
    } else Logger.error('handle_quit_matchmaking: client not in matchmaking');
  }

  @SubscribeMessage('get_info_matchamking')
  async getInfoMatchamking(socket: Socket): Promise<void> {
    Logger.log('get_info_matchamking');
    let match = null;
    this.client_in_MM.forEach((value, key) => {
      if (key == socket) match = value;
    });
    if (!match) {
      return;
    }
    socket.emit('get_info_matchamking', match);
  }
}
