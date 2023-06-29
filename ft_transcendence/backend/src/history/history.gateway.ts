import { Socket } from 'socket.io';
import { Logger } from '@nestjs/common';
import { SubscribeMessage, WebSocketGateway } from '@nestjs/websockets';
import { InjectDataSource } from '@nestjs/typeorm';
import { DataSource } from 'typeorm';
import { User } from '../entities/User';
import { Match } from '../entities/Match';

@WebSocketGateway()
export class HistoryGateway {
  constructor(
    @InjectDataSource()
    private dataSource: DataSource,
  ) {}

  return_win_match = async (client_id: string): Promise<any[]> => {
    const user: {
      wonMatches: Match[];
    } = await this.dataSource.manager.findOne(User, {
      where: { id: client_id },
      relations: ['wonMatches', 'wonMatches.winner', 'wonMatches.loser'],
    });
    if (!user) {
      Logger.error('handleWinHistory: user not found');
      return;
    }
    const result: any[] = [];
    user.wonMatches.forEach((match: Match): void => {
      result.push({
        id: match.id,
        winner: match.winner.username,
        loser: match.loser.username,
        draw: match.draw,
        winnerScore: match.winnerScore,
        loserScore: match.loserScore,
        createdAt: match.createdAt.toString(),
      });
    });
    return result;
  };

  return_lost_match = async (client_id: string): Promise<any[]> => {
    const user: { lostMatches: Match[] } =
      await this.dataSource.manager.findOne(User, {
        where: { id: client_id },
        relations: ['lostMatches', 'lostMatches.winner', 'lostMatches.loser'],
      });
    if (!user) {
      Logger.error('handleLostHistory: user not found');
      return;
    }
    const result: any[] = [];
    user.lostMatches.forEach((match: Match): void => {
      result.push({
        id: match.id,
        winner: match.winner.username,
        loser: match.loser.username,
        draw: match.draw,
        winnerScore: match.winnerScore,
        loserScore: match.loserScore,
        createdAt: match.createdAt.toString(),
      });
    });
    return result;
  };

  @SubscribeMessage('get_win_history_id')
  async handleWinHistoryID(client: Socket, payload: string): Promise<void> {
    Logger.log('get_win_history_id');
    try {
      const result: any[] = await this.return_win_match(payload);
      client.emit('get_win_history_id', result);
    } catch (e) {
      Logger.error('get_win_history_id: ' + e);
    }
  }

  @SubscribeMessage('get_lost_history_id')
  async handleLostHistoryid(client: Socket, payload: string): Promise<void> {
    Logger.log('get_lost_history_id from ');
    try {
      const result: any[] = await this.return_lost_match(payload);
      client.emit('get_lost_history_id', result);
    } catch (e) {
      Logger.error('get_lost_history_id: ' + e);
    }
  }

  @SubscribeMessage('get_draw_history_id')
  async handleDrawHistoryId(client: Socket, payload: string): Promise<void> {
    Logger.log('get_draw_history_id');
    try {
      let result: any[] = await this.return_win_match(payload);
      const tmp: any[] = await this.return_lost_match(payload);
      result = result.concat(tmp);
      const match_to_del: any[] = [];
      for (const match of result) {
        if (!match.draw) match_to_del.push(match);
      }
      for (const match of match_to_del) {
        result.splice(result.indexOf(match), 1);
      }
      client.emit('get_draw_history_id', result);
    } catch (e) {
      Logger.error('get_draw_history_id: ' + e);
    }
  }
}
