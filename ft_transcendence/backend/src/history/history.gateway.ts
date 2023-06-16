import { Socket } from 'socket.io';
import { Logger } from '@nestjs/common';
import { SubscribeMessage, WebSocketGateway } from '@nestjs/websockets';
import { InjectDataSource } from '@nestjs/typeorm';
import { DataSource } from 'typeorm';
import { SocketsService } from 'src/sockets.service';
import { User } from '../entities/User';

@WebSocketGateway()
export class HistoryGateway {
  constructor(
    @InjectDataSource()
    private dataSource: DataSource,
    private socketService: SocketsService,
  ) {}

  @SubscribeMessage('get_win_history')
  async handleWinHistory(client: Socket): Promise<void> {
    Logger.log('get_win_history');
    try {
      const user = await this.dataSource.manager.findOne(User, {
        where: { id: this.socketService.getUserId(client) },
        relations: ['wonMatches', 'wonMatches.winner', 'wonMatches.loser'],
      });
      if (!user) {
        Logger.error('handleWinHistory: user not found');
        client.emit('get_win_history', { error: 'user not found' });
        return;
      }
      const result = [];
      user.wonMatches.forEach((match) => {
        result.push({
          id: match.id,
          winer: match.winner.username,
          loser: match.loser.username,
          winnerScore: match.winnerScore,
          loserScore: match.loserScore,
          createdAt: match.createdAt.toString(),
        });
      });
      client.emit('get_win_history', result);
    } catch (e) {
      Logger.error('handleWinHistory: ' + e);
    }
  }

  @SubscribeMessage('get_lost_history')
  async handleLostHistory(client: Socket): Promise<void> {
    Logger.log('get_lost_history');
    try {
      const user = await this.dataSource.manager.findOne(User, {
        where: { id: this.socketService.getUserId(client) },
        relations: ['lostMatches', 'lostMatches.winner', 'lostMatches.loser'],
      });
      if (!user) {
        Logger.error('handleLostHistory: user not found');
        client.emit('get_lost_history', { error: 'user not found' });
        return;
      }
      const result = [];
      user.lostMatches.forEach((match) => {
        result.push({
          id: match.id,
          winer: match.winner.username,
          loser: match.loser.username,
          winnerScore: match.winnerScore,
          loserScore: match.loserScore,
          createdAt: match.createdAt.toString(),
        });
      });
      client.emit('get_lost_history', result);
    } catch (e) {
      Logger.error('handleLostHistory: ' + e);
    }
  }
}
