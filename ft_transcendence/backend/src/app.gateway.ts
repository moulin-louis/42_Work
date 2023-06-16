import {
  WebSocketGateway,
  OnGatewayConnection,
  WebSocketServer,
  OnGatewayDisconnect,
  SubscribeMessage,
} from '@nestjs/websockets';
import { Logger, UseGuards } from '@nestjs/common';
import { Socket, Server } from 'socket.io';
import { SocketsService } from './sockets.service';
import { AccessTokenGuard } from './auth/guards/accessToken.guard';
import { User, Status } from './entities/User';
import { DataSource } from 'typeorm';

@UseGuards(AccessTokenGuard)
@WebSocketGateway({ cors: true })
export class AppGateway implements OnGatewayConnection, OnGatewayDisconnect {
  constructor(
    private socketService: SocketsService,
    private dataSource: DataSource,
  ) {}

  @WebSocketServer() server: Server;
  private logger: Logger = new Logger('AppGateway');

  handleConnection(socket: Socket) {
    this.logger.log(`Client connected: ${socket.id}`);
    socket.emit('message', 'Server: connection established');
  }

  async handleDisconnect(socket: Socket): Promise<User | undefined> {
    this.logger.log(`Client disconnected: ${socket.id}`);
    const user = this.socketService.removeSocket(socket);
    if (!user) return undefined;
    const connectedUser = await this.dataSource.manager.findOneBy(User, {
      id: user.userId,
    });
    if (!connectedUser) return undefined;
    await this.server.emit('updateuser', {
      userId: user.userId,
      status: Status.OFFLINE,
    });
    connectedUser.logTimeInMinutes += user.minutesSpent;
    connectedUser.status = Status.OFFLINE;
    return this.dataSource.manager.save(connectedUser);
  }

  @SubscribeMessage('saveusersocket')
  async saveUserSocket(socket: Socket, userId: string): Promise<User> {
    Logger.log('saveusersocket');
    console.log('USERID ', userId);
    if (userId) {
      this.socketService.addSocket(userId, socket);
      const connectedUser = await this.dataSource.manager.findOneBy(User, {
        id: userId,
      });
      if (!connectedUser) return undefined;
      await this.server.emit('updateuser', {
        userId,
        status: Status.ONLINE,
      });
      connectedUser.status = Status.ONLINE;
      return this.dataSource.manager.save(connectedUser);
    }
  }
}
