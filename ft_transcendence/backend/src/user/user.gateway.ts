import {
  WebSocketGateway,
  SubscribeMessage,
  WebSocketServer,
} from '@nestjs/websockets';
import * as _ from 'lodash';
import { NotificationType, SocketsService } from 'src/sockets.service';
import { Injectable, Logger } from '@nestjs/common';
import { Server, Socket } from 'socket.io';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository, DataSource } from 'typeorm';
import { JwtService } from '@nestjs/jwt';
import { User } from 'src/entities/User';
import { JwtPayload } from 'src/auth/strategies';
import * as argon from 'argon2';

@WebSocketGateway()
@Injectable()
export class UserGateway {
  constructor(
    @InjectRepository(User) private readonly usersRepository: Repository<User>,
    private socketService: SocketsService,
    private readonly jwt: JwtService,
    private dataSource: DataSource,
  ) {}

  @WebSocketServer()
  server: Server;

  async getUserByToken(token: string) {
    const decodedToken = this.jwt.decode(token) as JwtPayload;
    const user: User = await this.usersRepository.findOne({
      where: { id: decodedToken.sub },
    });
    return user;
  }

  /**
   * Handles the 'allusers' WebSocket event.
   * If no users exist, it will first create sample users.
   * Then, it emits an event containing all existing users.
   * @param socket - The socket that initiated the 'allusers' event.
   * @param {string} userId - The id of the current user.
   * @returns - Returns a promise that resolves with the success status of the emit operation..
   */
  @SubscribeMessage('allusers')
  async allUsers(socket: Socket, userId: string): Promise<boolean> {
    const allUsers: User[] = await this.dataSource.manager.find(User, {
      relations: [
        'friends',
        'blocked',
        'friendRequest',
        'wonMatches',
        'wonMatches.winner',
        'wonMatches.loser',
        'lostMatches',
        'lostMatches.winner',
        'lostMatches.loser',
        'messagesSent',
        'messagesReceived',
      ],
    });
    const friendshipRequestSent: User[] = await this.dataSource.manager.find(
      User,
      {
        where: { friendRequest: { id: userId } },
      },
    );
    const isBannedBy: User[] = await this.dataSource.manager.find(User, {
      where: { blocked: { id: userId } },
    });
    const friends: string[] =
      allUsers
        ?.find((user) => user.id === userId)
        ?.friends?.map((friend) => friend.id) ?? [];
    const blocked: string[] =
      allUsers
        ?.find((user) => user.id === userId)
        ?.blocked?.map((friend) => friend.id) ?? [];
    const friendshipRequestReceived =
      allUsers
        ?.find((user) => user.id === userId)
        ?.friendRequest?.map((friend) => friend.id) ?? [];
    return socket.emit(
      'allusers',
      allUsers.map(
        ({
          id,
          avatar,
          username,
          status,
          email,
          wonMatches,
          lostMatches,
          messagesSent,
          messagesReceived,
          logTimeInMinutes,
        }) => ({
          id,
          avatar,
          username,
          status,
          isFriend: friends.includes(id),
          isBanned: blocked.includes(id),
          hasBanned: isBannedBy.map((u) => u.id).includes(id),
          friendshipRequestReceived: friendshipRequestReceived.includes(id),
          friendshipRequestSent: friendshipRequestSent
            .map((u) => u.id)
            .includes(id),
          email,
          blocked,
          friends,
          matches: _.concat(wonMatches, lostMatches)
            .filter(Boolean)
            .map((m) => ({
              ...m,
              isWon: m.winner.id === id,
              loser: m.loser.id,
              winner: m.winner.id,
            })),
          matchesPlayed: _.concat(wonMatches, lostMatches).filter(Boolean)
            .length,
          matchesWon: wonMatches ? wonMatches.filter(Boolean).length : 0,
          matchesLost: lostMatches ? lostMatches.filter(Boolean).length : 0,
          messagesReceived: messagesReceived ? messagesReceived.length : 0,
          messagesSent: messagesSent ? messagesSent.length : 0,
          logTimeInMinutes,
          level: Math.floor(
            Math.sqrt(
              2 * (wonMatches ? wonMatches.filter(Boolean).length : 0) + 0.25,
            ) - 0.5,
          ),
        }),
      ),
    );
  }

  @SubscribeMessage('myfriends')
  async getMyFriends(socket: Socket, token: string) {
    Logger.log('myfriends');
    const decodedToken = this.jwt.decode(token) as JwtPayload;
    const user: User = await this.usersRepository.findOne({
      where: { id: decodedToken.sub },
    });

    if (!user) {
      return;
    }
    const myFriends: User[] = user.friends;
    socket.emit(
      'myfriends',
      myFriends.map(({ id, username }) => ({ id, username })),
    );
  }

  @SubscribeMessage('updatepassword')
  async updatePassword(
    socket: Socket,
    {
      userId,
      password,
      confirmPassword,
    }: { userId: string; password: string; confirmPassword: string },
  ): Promise<boolean | User> {
    const passwordPattern = /((?=.\d)|(?=.\W+))(?![.\n])(?=.[A-Z])(?=.[a-z]).*$/;
    if (!passwordPattern.test(password)){
      return socket.emit('notification', {
        type: NotificationType.Error,
        message: 'Passwords must have at least one lowercase letter, one uppercase letter, one digit, and one special character',
      });
    }
    if (password !== confirmPassword)
      return socket.emit('notification', {
        type: NotificationType.Error,
        message: 'Passwords not matching',
      });
    else if (password.length === 0 || !password.replace(/\s/g, '').length)
      return socket.emit('notification', {
        type: NotificationType.Error,
        message: 'Password can not be empty',
      });
    const user = await this.usersRepository.findOneBy({ id: userId });
    if (!user) return false;
    user.password = await argon.hash(password);
    await this.usersRepository.save(user);
    return socket.emit('notification', {
      type: NotificationType.Success,
      message: 'Password updated',
    });
  }

  @SubscribeMessage('updateusername')
  async updateUsername(socket: Socket, { userId, username }) {
    if (!username || !username.replace(/\s/g, '').length)
      return socket.emit('notification', {
        type: NotificationType.Error,
        message: 'Username can not be empty',
      });
    const user = await this.usersRepository.findOneBy({ id: userId });
    if (!user) return false;
    if (user.username == username)
      return socket.emit('notification', {
        type: NotificationType.Success,
        message: 'Username updated',
      });
    const userCheck = await this.usersRepository.findOneBy({
      username: username,
    });
    if (userCheck)
      return socket.emit('notification', {
        type: NotificationType.Error,
        message: 'Username is not available',
      });
    user.username = username;
    await this.usersRepository.save(user);
    await this.updateAllUsers();
    return socket.emit('notification', {
      type: NotificationType.Success,
      message: 'Username updated',
    });
  }

  @SubscribeMessage('updateavatar')
  async updateAvatar(socket: Socket, { userId, dataUrl }) {
    const user = await this.usersRepository.findOneBy({ id: userId });
    if (!user) return;
  
    const mimeType = dataUrl.split(',')[0].split(':')[1].split(';')[0];
    const isImage = /^image\//.test(mimeType);
    if (isImage) {
      user.avatar = dataUrl;
      await this.usersRepository.save(user);
      await this.updateAllUsers();
      return socket.emit('notification', {
        type: NotificationType.Success,
        message: 'Avatar updated',
      });
    } else {
      return socket.emit('notification', {
        type: NotificationType.Error,
        message: 'Invalid file format. Please choose an image.',
      });
    }
  }

  @SubscribeMessage('banuser')
  async banUser(socket: Socket, { punisherId, recipientId }): Promise<boolean> {
    const punisher = await this.usersRepository.findOneBy({ id: punisherId });
    const recipient = await this.usersRepository.findOneBy({ id: recipientId });
    punisher.blocked = punisher.blocked
      ? [...punisher.blocked, recipient]
      : [recipient];
    await this.dataSource.manager.save(User, punisher);
    await this.updateAllUsers();
    return socket.emit('notification', {
      type: NotificationType.Success,
      message: 'User has been banned',
    });
  }

  @SubscribeMessage('cancelban')
  async cancelBanUser(
    socket: Socket,
    { punisherId, recipientId },
  ): Promise<boolean> {
    const punisher = await this.usersRepository.findOne({
      where: { id: punisherId },
      relations: ['blocked'],
    });
    punisher.blocked = punisher.blocked.filter(
      (user) => user.id !== recipientId,
    );
    await this.usersRepository.save(punisher);
    await this.updateAllUsers();
    return socket.emit('notification', {
      type: NotificationType.Success,
      message: 'Ban has been removed',
    });
  }

  @SubscribeMessage('newfriendrequest')
  async sendNewFriendRequest(
    socket: Socket,
    { senderId, recipientId },
  ): Promise<boolean> {
    const recipient = await this.usersRepository.findOne({
      where: { id: recipientId },
      relations: ['friendRequest'],
    });
    const sender = await this.usersRepository.findOne({
      where: { id: senderId },
      relations: ['friendRequest'],
    });
    const senderHasSentRequest = recipient.friendRequest.find(
      (user) => user.id === senderId,
    );
    const recipientHasSentRequest = sender.friendRequest.find(
      (user) => user.id === recipientId,
    );
    if (senderHasSentRequest) {
      return socket.emit('notification', {
        type: NotificationType.Error,
        message: `You have already sent a friendship request to ${recipient.username}! Be patient!`,
      });
    }
    if (recipientHasSentRequest) {
      return socket.emit('notification', {
        type: NotificationType.Error,
        message: `${recipient.username} has already sent a friendship request.`,
      });
    }
    recipient.friendRequest = recipient.friendRequest
      ? [...recipient.friendRequest, sender]
      : [sender];
    await this.dataSource.manager.save(User, recipient);
    await this.socketService.getSocket(recipientId)?.emit('notification', {
      type: NotificationType.Success,
      message: `You have a new friend request from ${sender.username}`,
    });
    await this.updateAllUsers();
    return socket.emit('notification', {
      type: NotificationType.Success,
      message: 'Friend request send',
    });
  }

  @SubscribeMessage('cancelfriendrequest')
  async cancelFriendRequest(
    socket: Socket,
    { senderId, recipientId },
  ): Promise<boolean> {
    const recipient = await this.usersRepository.findOne({
      where: { id: recipientId },
      relations: ['friendRequest'],
    });
    recipient.friendRequest = recipient.friendRequest.filter(
      (user) => user.id !== senderId,
    );
    await this.usersRepository.save(recipient);
    await this.updateAllUsers();
    return socket.emit('notification', {
      type: NotificationType.Success,
      message: 'Friend Request has been removed',
    });
  }

  @SubscribeMessage('removefriend')
  async removeFromFriends(socket, { senderId, recipientId }) {
    const sender = await this.usersRepository.findOne({
      where: { id: senderId },
      relations: ['friends'],
    });
    const recipient = await this.usersRepository.findOne({
      where: { id: recipientId },
      relations: ['friends'],
    });
    sender.friends = sender.friends.filter((user) => user.id !== recipientId);
    recipient.friends = recipient.friends.filter(
      (user) => user.id !== senderId,
    );
    await this.usersRepository.save(recipient);
    await this.usersRepository.save(sender);
    await this.updateAllUsers();
    return socket.emit('notification', {
      type: NotificationType.Success,
      message: `You remove ${recipient.username} from your friends`,
    });
  }

  @SubscribeMessage('refusefriendrequest')
  async refuseFriendRequest(
    socket,
    { recipientId, senderId },
  ): Promise<boolean> {
    const recipient = await this.usersRepository.findOne({
      where: { id: recipientId },
      relations: ['friendRequest'],
    });
    if (!recipient) return false;
    recipient.friendRequest = recipient.friendRequest.filter(
      (user) => user.id !== senderId,
    );
    await this.usersRepository.save(recipient);
    await this.updateAllUsers();
    await this.socketService.getSocket(senderId)?.emit('notification', {
      type: NotificationType.Error,
      message: `${recipient.username} refused your invitation to be friend`,
    });
    return socket.emit('notification', {
      type: NotificationType.Success,
      message: `You refuse the invitation`,
    });
  }

  @SubscribeMessage('acceptfriendrequest')
  async acceptFriendRequest(
    socket: Socket,
    { senderId, recipientId },
  ): Promise<boolean> {
    const recipient = await this.usersRepository.findOne({
      where: { id: recipientId },
      relations: ['friendRequest', 'friends'],
    });
    const sender = await this.usersRepository.findOne({
      where: { id: senderId },
      relations: ['friendRequest', 'friends'],
    });
    if (!sender || !recipient)
      return socket.emit('notification', {
        type: NotificationType.Error,
        message: 'Something went wrond, check your connexion and try again',
      });
    if (!recipient.friendRequest)
      return socket.emit('notification', {
        type: NotificationType.Error,
        message: 'You have no friendship request pending',
      });
    const isFriend = recipient.friends.find((user) => user.id === senderId);
    if (isFriend)
      return socket.emit('notification', {
        type: NotificationType.Error,
        message: 'You are already friend, we have a little issue, sorry!',
      });
    const senderHasSentRequest = recipient.friendRequest.find(
      (user) => user.id === senderId,
    );
    if (!senderHasSentRequest)
      return socket.emit('notification', {
        type: NotificationType.Error,
        message: 'Friend invitation not valid anymore',
      });
    recipient.friendRequest = recipient.friendRequest.filter(
      (user) => user.id !== senderId,
    );
    recipient.friends = recipient.friends
      ? [...recipient.friends, sender]
      : [sender];
    sender.friends = sender.friends
      ? [...sender.friends, recipient]
      : [recipient];
    await this.usersRepository.save(recipient);
    await this.usersRepository.save(sender);
    await this.updateAllUsers();
    await this.socketService.getSocket(senderId)?.emit('notification', {
      type: NotificationType.Success,
      message: `You have a new friend ${recipient.username}`,
    });
    return socket.emit('notification', {
      type: NotificationType.Success,
      message: `You have a new friend ${sender.username}`,
    });
  }

  public async updateAllUsers(): Promise<boolean[]> {
    return Promise.all(
      Array.from(this.socketService.socketUsers.entries()).map(
        ([userId, connection]) => this.allUsers(connection.socket, userId),
      ),
    );
  }
}
