import {
  WebSocketGateway,
  OnGatewayConnection,
  WebSocketServer,
  OnGatewayDisconnect,
  SubscribeMessage,
} from '@nestjs/websockets';
import { UseGuards } from '@nestjs/common';
import { Socket, Server } from 'socket.io';
import { SocketsService } from './sockets.service';
import { AccessTokenGuard } from './auth/guards/accessToken.guard';
import { User, Status } from './entities/User';
import { DataSource } from 'typeorm';
import { UserGateway } from './user/user.gateway';

@UseGuards(AccessTokenGuard)
@WebSocketGateway({ cors: true })
export class AppGateway implements OnGatewayConnection, OnGatewayDisconnect {
  constructor(
    private socketService: SocketsService,
    private dataSource: DataSource,
    private userGateway: UserGateway,
  ) {}

  @WebSocketServer() server: Server;

  /**
   * Handles connection events.
   *
   * @param {Socket} socket - The client socket that has connected to the server.
   */
  handleConnection(socket: Socket) {
    socket.emit('message', 'Server: connection established');
  }

  /**
   * Handles disconnect events.
   *
   * @async
   * @param {Socket} socket - The client socket that has disconnected from the server.
   * @returns {Promise<User | undefined>} The user that disconnected, or undefined if the user was not found.
   */
  async handleDisconnect(socket: Socket): Promise<boolean[] | undefined> {
    const user = this.socketService.removeSocket(socket);
    if (!user) return undefined;
    const connectedUser = await this.dataSource.manager.findOneBy(User, {
      id: user.userId,
    });
    if (!connectedUser) return undefined;
    this.server.emit('updateuser', {
      userId: user.userId,
      status: Status.OFFLINE,
    });
    connectedUser.logTimeInMinutes += user.minutesSpent;
    connectedUser.status = Status.OFFLINE;
    await this.dataSource.manager.save(connectedUser);
    return this.userGateway.updateAllUsers();
  }

  /**
   * Saves a user's socket upon connection and updates their status to online.
   *
   * @async
   * @param {Socket} socket - The client socket that is connected.
   * @param {string} userId - The ID of the user whose socket is to be saved.
   * @returns {Promise<User>} The updated user object.
   */
  @SubscribeMessage('saveusersocket')
  async saveUserSocket(socket: Socket, userId: string): Promise<boolean[]> {
    if (userId) {
      this.socketService.addSocket(userId, socket);
      const connectedUser = await this.dataSource.manager.findOneBy(User, {
        id: userId,
      });
      if (!connectedUser) return undefined;
      this.server.emit('updateuser', {
        userId,
        status: Status.ONLINE,
      });
      connectedUser.status = Status.ONLINE;
      await this.dataSource.manager.save(connectedUser);
      return this.userGateway.updateAllUsers();
    }
  }
}
