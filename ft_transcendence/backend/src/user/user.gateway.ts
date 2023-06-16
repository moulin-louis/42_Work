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
import { Channel } from 'src/entities/Channel';

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
   * Asynchronously creates sample users and channels for testing.
   * @returns A promise representing the completion of the sample data creation.
   */
  async createExamples(): Promise<void> {
    const benoît = new User();
    benoît.username = 'Benoît';
    benoît.password = await argon.hash('password');
    await this.dataSource.manager.save(User, benoît);
    const laure = new User();
    laure.username = 'Laure';
    laure.password = await argon.hash('password');
    await this.dataSource.manager.save(User, laure);
    const aлександр = new User();
    aлександр.username = 'Александр';
    aлександр.password = await argon.hash('password');
    await this.dataSource.manager.save(User, aлександр);
    const louis = new User();
    louis.username = 'Louis';
    louis.password = await argon.hash('password');
    louis.friends = [benoît, laure, aлександр];
    await this.dataSource.manager.save(User, louis);
    const chan1 = new Channel();
    chan1.name = 'chan1';
    chan1.owner = laure;
    chan1.admins = [laure];
    chan1.members = [benoît, laure, aлександр, louis];
    await this.dataSource.manager.save(Channel, chan1);
    const chan2 = new Channel();
    chan2.name = 'chan2';
    chan2.owner = aлександр;
    chan2.admins = [aлександр];
    chan2.members = [laure, aлександр, louis];
    await this.dataSource.manager.save(Channel, chan2);
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
    Logger.log('allusers');
    if ((await this.dataSource.manager.count(User)) === 1)
      await this.createExamples();
    const allUsers: User[] = await this.dataSource.manager.find(User, {
      relations: [
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
    const friendshipRequestReceived: User[] =
      await this.dataSource.manager.find(User, {
        where: { friendRequest: { id: userId } },
      });
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
    const friendshipRequestSent =
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
          hasBanned: blocked.includes(id),
          isBanned: isBannedBy.map((u) => u.id).includes(userId),
          friendshipRequestSent: friendshipRequestSent.includes(id),
          friendshipRequestReceived: friendshipRequestReceived
            .map((u) => u.id)
            .includes(userId),
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
      // TODO handle error
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
    if (password !== confirmPassword)
      return socket.emit('notification', {
        type: NotificationType.Error,
        message: 'Passwords not matching',
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
    if (!username)
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
    return socket.emit('notification', {
      type: NotificationType.Success,
      message: 'Username updated',
    });
  }

  @SubscribeMessage('updateavatar')
  async updateAvatar(socket: Socket, { userId, dataUrl }) {
    const user = await this.usersRepository.findOneBy({ id: userId });
    if (!user) return;
    user.avatar = dataUrl;
    await this.usersRepository.save(user);
    return socket.emit('notification', {
      type: NotificationType.Success,
      message: 'Avatar updated',
    });
  }

  @SubscribeMessage('banuser')
  async banUser(socket: Socket, { punisherId, recipientId }): Promise<boolean> {
    const punisher = await this.usersRepository.findOneBy({ id: punisherId });
    const recipient = await this.usersRepository.findOneBy({ id: recipientId });
    punisher.blocked = punisher.blocked
      ? [...punisher.blocked, recipient]
      : [recipient];
    await this.dataSource.manager.save(User, punisher);
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
    const punisher = await this.usersRepository.findOneBy({ id: punisherId });
    punisher.blocked = punisher.blocked.filter(
      (user) => user.id !== recipientId,
    );
    await this.usersRepository.save(punisher);
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
    const sender = await this.usersRepository.findOneBy({ id: senderId });
    const recipient = await this.usersRepository.findOneBy({ id: recipientId });
    recipient.friendRequest = recipient.friendRequest
      ? [...recipient.friendRequest, sender]
      : [sender];
    await this.dataSource.manager.save(User, recipient);
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
    const recipient = await this.usersRepository.findOneBy({ id: recipientId });
    recipient.friendRequest = recipient.friendRequest.filter(
      (user) => user.id !== senderId,
    );
    await this.usersRepository.save(recipient);
    return socket.emit('notification', {
      type: NotificationType.Success,
      message: 'Friend Request has been removed',
    });
  }

  @SubscribeMessage('removefriend')
  async removeFromFriends(socket, { senderId, recipientId }) {
    const sender = await this.usersRepository.findOneBy({ id: senderId });
    const recipient = await this.usersRepository.findOneBy({ id: recipientId });
    sender.friends = sender.friends.filter((user) => user.id !== recipientId);
    recipient.friends = recipient.friends.filter(
      (user) => user.id !== senderId,
    );
    await this.usersRepository.save(recipient);
    await this.usersRepository.save(sender);
    return socket.emit('notification', {
      type: NotificationType.Success,
      message: `You remove ${recipient.id} from your friends`,
    });
  }

  @SubscribeMessage('refusefriendrequest')
  async refuseFriendRequest(
    socket,
    { recipientId, senderId },
  ): Promise<boolean> {
    const recipient = await this.usersRepository.findOneBy({ id: recipientId });
    recipient.friendRequest = recipient.friendRequest.filter(
      (user) => user.id !== senderId,
    );
    await this.usersRepository.save(recipient);
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
    const sender = await this.usersRepository.findOneBy({ id: senderId });
    const recipient = await this.usersRepository.findOneBy({ id: recipientId });
    const isFriendRequest = recipient.friendRequest.filter(
      (user) => user.id === senderId,
    );
    if (isFriendRequest.length === 0)
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

  // @SubscribeMessage('newfriendrequest')
  // async sendNewFriendRequest(socket: Socket, { senderId, recipientId }) {
  //   const sender = await this.usersRepository.findOneBy({ id: senderId });
  //   const recipient = await this.usersRepository.findOneBy({ id: recipientId });
  //   const friendRequest = new FriendshipRequest();
  //   friendRequest.sender = sender;
  //   friendRequest.recipient = recipient;
  //   const request = await this.dataSource.manager.create(
  //     FriendshipRequest,
  //     friendRequest,
  //   );
  //   console.log(request);
  //   return socket.emit('notification', {
  //     type: NotificationType.Success,
  //     message: 'Friend request send',
  //   });
  // }

  // @SubscribeMessage('ban')
  // async banUser(socket: Socket, { banById, banId }) {
  //   const punisher = await this.usersRepository.findOneBy({ id: banById });
  //   const recipient = await this.usersRepository.findOneBy({ id: banId });
  //   const ban = new BanRequest();
  //   ban.banBy = punisher;
  //   ban.ban = recipient;
  //   const request = await this.dataSource.manager.create(
  //     BanRequest,
  //     ban,
  //   );
  //   console.log(ban);
  //   return socket.emit('notification', {
  //     type: NotificationType.Success,
  //     message: 'User banned',
  //   });
  // }

  // @SubscribeMessage('removefriendrequest')
  // async cancelFriendRequest(socket: Socket, { senderId, recipientId }) {
  //   const friendshipRequest = await this.dataSource.manager.find(
  //     FriendshipRequest,
  //     {
  //       where: [{ sender: { id: senderId } }, { recipient: { id: recipientId } }],
  //       relations: ['sender', 'recipient'],
  //     },
  //   );
  //   console.log(friendshipRequest);

  //   if (friendshipRequest) {
  //     await this.dataSource.manager.remove(
  //       FriendshipRequest,
  //       friendshipRequest,
  //     );
  //     console.log('UNFRIENDDDDDD');
  //   }
  //   return socket.emit('notification', {
  //     type: NotificationType.Success,
  //     message: 'Friend request cancel',
  //   });

  // }

  // @SubscribeMessage('removeban')
  // async cancelBan(socket: Socket, { banById, recipientId }) {
  //   const ban = await this.dataSource.manager.find(
  //     BanRequest,
  //     {
  //       where: [{ banBy: { id: banById } }, { ban: { id: recipientId } }],
  //       relations: ['banBy', 'ban'],
  //     },
  //   );
  //   console.log(ban);

  //   if (ban) {
  //     await this.dataSource.manager.remove(
  //       BanRequest,
  //       ban,
  //     );
  //   }
  //   return socket.emit('notification', {
  //     type: NotificationType.Success,
  //     message: 'Ban cancel',
  //   });
  // }

  // async updateUsers() {
  //   return this.socketService.socketUsers.forEach(this.allUsers)
  // }

  // @SubscribeMessage('allFriends')
  // async getAllFriends(socket: Socket, token: string)
  // {
  //   Logger.log('allFriends');
  //   const decodedToken = this.jwt.decode(token) as JwtPayload;
  //   const allFriends: User = await
  // }
}
