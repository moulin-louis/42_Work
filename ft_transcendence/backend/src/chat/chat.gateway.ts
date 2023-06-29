import * as _ from 'lodash';
import * as argon from 'argon2';
import {
  SubscribeMessage,
  WebSocketGateway,
  WebSocketServer,
} from '@nestjs/websockets';
import { Logger } from '@nestjs/common';
import { Server, Socket } from 'socket.io';
import { User } from 'src/entities/User';
import { Message } from 'src/entities/Message';
import { DataSource } from 'typeorm';
import { InjectDataSource } from '@nestjs/typeorm';
import { NotificationType, SocketsService } from 'src/sockets.service';
import { Read } from 'src/entities/Read';
import { Channel } from 'src/entities/Channel';
import { promisify } from 'util';

const wait = promisify(setTimeout);

interface GameProposal {
  sender: string;
  recipient: string;
  game_mode: string;
  limit_max: string;
}

/**
 * A WebSocket Gateway class that facilitates chat operations.
 */
@WebSocketGateway()
export class ChatGateway {
  /**
   * Constructs a ChatGateway.
   * @param dataSource - The data source for the application.
   * @param socketService - The service handling socket operations.
   */
  constructor(
    @InjectDataSource()
    private dataSource: DataSource,
    private socketService: SocketsService,
  ) {}

  @WebSocketServer()
  server: Server;

  game_proposals: Set<GameProposal> = new Set();

  handleDisconnect(socket: Socket) {
    for (const game_p of this.game_proposals) {
      if (game_p.sender == this.socketService.getUserId(socket))
        if (this.game_proposals.delete(game_p)) return;
    }
  }
  /**
   * Asynchronously handles the 'allmessages' WebSocket event.
   * It finds all messages related to the provided username and emits them in a structured format.
   * @param socket - The socket that initiated the 'allmessages' event.
   * @param username - The username for which messages are requested.
   * @returns A promise representing the completion of the event handling.
   */
  @SubscribeMessage('allmessages')
  async allMessages(
    socket: Socket,
    { userId }: { userId: string },
  ): Promise<boolean> {
    const userMessages: Message[] = await this.dataSource.manager.find(
      Message,
      {
        where: [{ toUser: { id: userId } }, { from: { id: userId } }],
        relations: ['from', 'toUser', 'toChannel'],
      },
    );
    const formattedUserMessages =
      _(userMessages)
        .filter((m) => !m.toChannel)
        .map((m) => ({
          message: m.message,
          from: m.from.id,
          toUserId: m.toUser?.id,
          toChannelId: m.toChannel?.id,
          date: m.date,
        }))
        .value() || [];
    const channelMessages: Message[] = await this.dataSource.manager.find(
      Message,
      {
        where: [{ toChannel: { members: { id: userId } } }],
        relations: ['from', 'toUser', 'toChannel'],
      },
    );
    const formattedChannelMessages =
      _(channelMessages)
        .map((m) => ({
          message: m.message,
          from: m.from.id,
          toUserId: m.toUser?.id,
          toChannelId: m.toChannel?.id,
          date: m.date,
        }))
        .value() || [];
    return socket.emit('allmessages', [
      ...formattedUserMessages,
      ...formattedChannelMessages,
    ]);
  }

  /**
   * Handles the 'newmessage' WebSocket event.
   * It creates a new message and emits the new message to the correct recipient(s).
   * @param origin - The socket that initiated the 'newmessage' event.
   * @param message - The contents of the new message.
   * @param from - The username of the sender of the new message.
   * @param toUser - The username of the intended user recipient (if any).
   * @param toChannel - The name of the intended channel recipient (if any).
   * @returns A promise representing the completion of the event handling.
   */
  @SubscribeMessage('newmessage')
  async newMessage(
    origin: Socket,
    {
      message,
      from,
      toUserId,
      toChannelId,
    }: {
      message: string;
      from: string;
      toUserId: string | undefined;
      toChannelId: string | undefined;
    },
  ): Promise<Message> {
    const date = new Date();
    const newMessage = new Message();
    newMessage.from = await this.dataSource.manager.findOneBy(User, {
      id: from,
    });
    if (toUserId) {
      const payload = { message, from, toUserId, date };
      origin.emit('newmessage', payload);
      this.socketService.getSocket(toUserId)?.emit('newmessage', payload);
      newMessage.toUser = await this.dataSource.manager.findOneBy(User, {
        id: toUserId,
      });
    }
    if (toChannelId) {
      const payload = { message, from, toChannelId, date };
      newMessage.toChannel = await this.dataSource.manager.findOne(Channel, {
        where: {
          id: toChannelId,
        },
        relations: ['members'],
      });
      newMessage.toChannel.members.forEach(({ id }) => {
        this.socketService.getSocket(id)?.emit('newmessage', payload);
      });
    }
    newMessage.date = date;
    newMessage.message = message;
    return this.dataSource.manager.save(Message, newMessage);
  }

  /**
   * Handles the 'setread' WebSocket event.
   * It updates or creates a read receipt, then emits an 'allread' event for the user.
   * @param socket - The socket that initiated the 'setread' event.
   * @param from - The id of the user marking a message as read.
   * @param toUser - The id of the intended user recipient (if any).
   * @param toChannel - The id of the intended channel recipient (if any).
   * @returns A promise representing the completion of the event handling.
   */
  @SubscribeMessage('setread')
  async setRead(
    socket: Socket,
    {
      from,
      toUserId,
      toChannelId,
    }: {
      from: string;
      toUserId: string | undefined;
      toChannelId: string | undefined;
    },
  ): Promise<boolean> {
    const getConditions = () => {
      if (toUserId) return { from: { id: from }, toUser: { id: toUserId } };
      if (toChannelId)
        return { from: { id: from }, toChannel: { id: toChannelId } };
    };
    const readToUpdate = await this.dataSource.manager.findOneBy(
      Read,
      getConditions(),
    );
    if (readToUpdate) {
      readToUpdate.date = new Date();
      await this.dataSource.manager.save(Read, readToUpdate);
    } else {
      const read = new Read();
      read.from = await this.dataSource.manager.findOneBy(User, {
        id: from,
      });
      if (toUserId)
        read.toUser = await this.dataSource.manager.findOneBy(User, {
          id: toUserId,
        });
      if (toChannelId)
        read.toChannel = await this.dataSource.manager.findOneBy(Channel, {
          id: toChannelId,
        });
      read.date = new Date();
      await this.dataSource.manager.save(Read, read);
    }
    return this.allRead(socket, { userId: from });
  }

  /**
   * Handles the 'allread' WebSocket event.
   * It finds all read receipts for the provided user id and emits them.
   * @param socket - The socket that initiated the 'allread' event.
   * @param userId - The id for which read receipts are requested.
   * @returns A promise representing the completion of the event handling.
   */
  @SubscribeMessage('allread')
  async allRead(
    socket: Socket,
    { userId }: { userId: string },
  ): Promise<boolean> {
    const allRead: Read[] = await this.dataSource.manager.find(Read, {
      where: { from: { id: userId } },
      relations: ['from', 'toUser', 'toChannel'],
    });
    const formattedAllRead = _(allRead)
      .map((r) => ({
        from: r.from.id,
        toUserId: r.toUser?.id,
        toChannelId: r.toChannel?.id,
        date: r.date,
      }))
      .value();
    return socket.emit('allread', formattedAllRead);
  }

  /**
   * Formats a channel object for emission by removing unnecessary details.
   * @param channel - The channel object to format.
   * @returns The formatted channel object.
   */
  formatChannel(channel: Channel) {
    return {
      admins: channel.admins.map((a) => a.id),
      bans: channel.bans?.map((b) => b.id),
      id: channel.id,
      secret: channel.secret,
      protected: channel.protected,
      members: channel.members.map((m) => m.id),
      mutes: channel.mutes?.map((b) => b.id),
      name: channel.name,
      owner: channel.owner.id,
    };
  }

  /**
   * Handles the 'newchannel' WebSocket event.
   * It creates a new channel and emits the new channel's details.
   * @param socket - The socket that initiated the 'newchannel' event.
   * @param name - The name of the new channel.
   * @param secret - Whether the new channel is secret.
   * @param password - The password for the new channel (if any).
   * @param owner - The id of the owner of the new channel.
   * @returns A promise representing the completion of the event handling.
   */
  @SubscribeMessage('newchannel')
  async newchannel(
    socket: Socket,
    {
      name,
      secret,
      password,
      ownerId,
    }: {
      name: string;
      secret: boolean;
      password: string;
      ownerId: string;
    },
  ): Promise<boolean> {
    if (name === '') {
      socket.emit('notification', {
        type: NotificationType.Error,
        message: 'Channel name cannot be empty',
      });
      return false;
    }
    const newChannel = new Channel();
    newChannel.name = name;
    if (secret) newChannel.secret = true;
    if (password) {
      newChannel.password = await argon.hash(password);
      newChannel.protected = true;
    }
    const user = await this.dataSource.manager.findOneBy(User, {
      id: ownerId,
    });
    newChannel.owner = user;
    newChannel.admins = [user];
    newChannel.members = [user];
    await this.dataSource.manager.save(Channel, newChannel);
    socket.emit('notification', {
      type: NotificationType.Success,
      message: `Channel #${name} created successfully`,
    });
    return this.server.emit('channel', this.formatChannel(newChannel));
  }

  /**
   * Handles the 'allchannels' WebSocket event.
   * It finds all channels and emits them in a formatted structure.
   * @param socket - The socket that initiated the 'allchannels' event.
   * @param username - The username for which channel details are requested.
   * @returns A promise representing the completion of the event handling.
   */
  @SubscribeMessage('allchannels')
  async allChannels(socket: Socket): Promise<boolean> {
    const allChannels: Channel[] = await this.dataSource.manager.find(Channel, {
      relations: ['admins', 'bans', 'members', 'mutes', 'owner'],
    });
    return socket.emit('allchannels', allChannels.map(this.formatChannel));
  }

  /**
   * Handles the 'joinchannel' WebSocket event.
   * It adds the user to a channel and emits the updated channel details.
   * @param socket - The socket that initiated the 'joinchannel' event.
   * @param username - The username of the user joining the channel.
   * @param channelname - The name of the channel to join.
   * @returns A promise representing the completion of the event handling.
   */
  @SubscribeMessage('joinchannel')
  async joinChannel(
    socket: Socket,
    {
      userId,
      channelId,
    }: {
      userId: string;
      channelId: string;
    },
  ): Promise<boolean> {
    const user = await this.dataSource.manager.findOneBy(User, {
      id: userId,
    });
    const channel = await this.dataSource.manager.findOne(Channel, {
      where: { id: channelId },
      relations: ['admins', 'bans', 'members', 'mutes', 'owner'],
    });
    channel.members.push(user);
    await this.dataSource.manager.save(Channel, channel);
    await this.socketService.getSocket(userId)?.emit('notification', {
      type: NotificationType.Success,
      message: `You have joined #${channel.name}`,
    });
    return this.server.emit('channel', this.formatChannel(channel));
  }

  /**
   * Handles the 'leavechannel' WebSocket event.
   * It removes the user from a channel and emits the updated channel details, or deletes the channel if it becomes empty.
   * @param socket - The socket that initiated the 'leavechannel' event.
   * @param username - The username of the user leaving the channel.
   * @returns A promise representing the completion of the event handling.
   */
  @SubscribeMessage('leavechannel')
  async leaveChannel(
    socket: Socket,
    { userId, channelId }: { userId: string; channelId: string },
  ): Promise<boolean> {
    const channel = await this.dataSource.manager.findOne(Channel, {
      where: { id: channelId },
      relations: ['admins', 'bans', 'members', 'mutes', 'owner'],
    });
    channel.members = channel.members.filter((m) => m.id !== userId);
    if (!channel.members.length) {
      const id = channel.id;
      await this.dataSource.manager.remove(Channel, channel);
      return this.server.emit('delchannel', id);
    }
    channel.admins = channel.admins.filter((a) => a.id !== userId);
    if (channel.admins.length === 0) {
      channel.admins = [channel.members[0]];
    }
    if (channel.owner.id === userId) {
      channel.owner = channel.admins[0];
    }
    await this.dataSource.manager.save(Channel, channel);
    await socket.emit('notification', {
      type: NotificationType.Info,
      message: `You have left channel #${channel.name}`,
    });
    return this.server.emit('channel', this.formatChannel(channel));
  }

  /**
   * Handles the 'banfromchannel' WebSocket event.
   * It bans a user from a channel and emits the updated channel details.
   * @param socket - The socket that initiated the 'banfromchannel' event.
   * @param username - The username of the user to ban.
   * @param channelname - The name of the channel from which to ban the user.
   * @param duration - The duration of the ban in seconds.
   * @returns A promise representing the completion of the event handling.
   */
  @SubscribeMessage('banfromchannel')
  async banFromChannel(
    socket: Socket,
    {
      userId,
      channelId,
    }: {
      userId: string;
      channelId: string;
      duration: number;
    },
  ): Promise<boolean> {
    const channel = await this.dataSource.manager.findOne(Channel, {
      where: { id: channelId },
      relations: ['admins', 'bans', 'members', 'mutes', 'owner'],
    });
    const user = await this.dataSource.manager.findOneBy(User, {
      id: userId,
    });
    channel.bans = channel.bans ? [...channel.bans, user] : [user];
    await this.dataSource.manager.save(Channel, channel);
    this.socketService.getSocket(userId)?.emit('notification', {
      type: NotificationType.Error,
      message: `You have been banned from channel #${channel.name}`,
    });
    return this.server.emit('channel', this.formatChannel(channel));
  }

  /**
   * Handles the 'unbanfromchannel' WebSocket event.
   * It bans a user from a channel and emits the updated channel details.
   * @param socket - The socket that initiated the 'banfromchannel' event.
   * @param username - The username of the user to ban.
   * @param channelname - The name of the channel from which to ban the user.
   * @param duration - The duration of the ban in seconds.
   * @returns A promise representing the completion of the event handling.
   */
  @SubscribeMessage('unbanfromchannel')
  async unbanFromChannel(
    socket: Socket,
    {
      userId,
      channelId,
    }: {
      userId: string;
      channelId: string;
      duration: number;
    },
  ): Promise<boolean> {
    const channel = await this.dataSource.manager.findOne(Channel, {
      where: { id: channelId },
      relations: ['admins', 'bans', 'members', 'mutes', 'owner'],
    });
    channel.bans = channel.bans.filter((b) => b.id !== userId);
    await this.dataSource.manager.save(Channel, channel);
    this.socketService.getSocket(userId)?.emit('notification', {
      type: NotificationType.Success,
      message: `You have been unbanned from channel #${channel.name}`,
    });
    return this.server.emit('channel', this.formatChannel(channel));
  }

  /**
   * Handles the 'mutefromchannel' WebSocket event.
   * It mutes a user in a channel for a specified duration and emits the updated channel details.
   * @param socket - The socket that initiated the 'mutefromchannel' event.
   * @param userId - The id of the user to mute.
   * @param channelId - The id of the channel in which to mute the user.
   * @param duration - The duration of the mute in seconds.
   * @returns A promise representing the completion of the event handling.
   */
  @SubscribeMessage('mutefromchannel')
  async muteFromChannel(
    socket: Socket,
    {
      userId,
      channelId,
      duration = 1,
    }: {
      userId: string;
      channelId: string;
      duration: number;
    },
  ): Promise<boolean> {
    const channel = await this.dataSource.manager.findOne(Channel, {
      where: { id: channelId },
      relations: ['admins', 'bans', 'members', 'mutes', 'owner'],
    });
    const user = await this.dataSource.manager.findOneBy(User, {
      id: userId,
    });
    channel.mutes = channel.mutes ? [...channel.mutes, user] : [user];
    await this.dataSource.manager.save(Channel, channel);
    this.server.emit('channel', this.formatChannel(channel));
    if (!duration) return;
    this.socketService.getSocket(userId)?.emit('notification', {
      type: NotificationType.Error,
      message: `You have been muted from channel #${channel.name} for ${duration} minute`,
    });
    await wait(duration * 60000);
    channel.mutes = channel.mutes.filter((b) => b.id !== userId);
    await this.dataSource.manager.save(Channel, channel);
    this.socketService.getSocket(userId)?.emit('notification', {
      type: NotificationType.Success,
      message: `You have been unmuted from channel #${channel.name}`,
    });
    return this.server.emit('channel', this.formatChannel(channel));
  }

  /**
   * Handles the 'changechannelpassword' WebSocket event.
   * It changes a channel's password and emits the updated channel details.
   * @param socket - The socket that initiated the 'changechannelpassword' event.
   * @param name - The name of the channel.
   * @param password - The new password for the channel.
   * @returns A promise representing the completion of the event handling.
   */
  @SubscribeMessage('changechannelpassword')
  async changeChannelPassword(
    socket: Socket,
    {
      id,
      password,
    }: {
      id: string;
      password: string;
    },
  ): Promise<boolean> {
    const channel = await this.dataSource.manager.findOne(Channel, {
      where: { id },
      relations: ['admins', 'bans', 'members', 'mutes', 'owner'],
    });
    if (!password) {
      channel.protected = false;
      channel.password = null;
    } else {
      channel.protected = true;
      channel.password = await argon.hash(password);
    }
    await this.dataSource.manager.save(Channel, channel);
    return this.server.emit('channel', this.formatChannel(channel));
  }

  /**
   * Handles the 'checkchannelpassword' WebSocket event.
   * It checks whether a provided password matches a channel's password and emits the result.
   * @param socket - The socket that initiated the 'checkchannelpassword' event.
   * @param channelname - The name of the channel.
   * @param password - The password to check.
   * @returns A promise representing the completion of the event handling.
   */
  @SubscribeMessage('checkchannelpassword')
  async checkChannelPassword(
    socket: Socket,
    {
      id,
      password,
    }: {
      id: string;
      password: string;
    },
  ): Promise<boolean> {
    const channel = await this.dataSource.manager.findOneBy(Channel, {
      id,
    });
    if (!channel.password)
      return this.server.emit('checkchannelpassword', true);
    const isCorrect = await argon.verify(channel.password, password);
    return this.server.emit('checkchannelpassword', isCorrect);
  }

  /**
   * Handles the 'addadmintochannel' WebSocket event.
   * It adds a user as an admin to a channel and emits the updated channel details.
   * @param socket - The socket that initiated the 'addadmintochannel' event.
   * @param username - The username of the user to add as an admin.
   * @param channelname - The name of the channel.
   * @returns A promise representing the completion of the event handling.
   */
  @SubscribeMessage('addadmintochannel')
  async addAdminToChannel(
    socket: Socket,
    {
      userId,
      channelId,
    }: {
      userId: string;
      channelId: string;
    },
  ): Promise<boolean> {
    const channel = await this.dataSource.manager.findOne(Channel, {
      where: { id: channelId },
      relations: ['admins', 'bans', 'members', 'mutes', 'owner'],
    });
    const user = await this.dataSource.manager.findOneBy(User, {
      id: userId,
    });
    channel.admins.push(user);
    await this.dataSource.manager.save(Channel, channel);
    this.socketService.getSocket(userId)?.emit('notification', {
      type: NotificationType.Success,
      message: `You have been added as an admin to channel #${channel.name}`,
    });
    return this.server.emit('channel', this.formatChannel(channel));
  }

  /**
   * Handles the 'removeadminfromchannel' WebSocket event.
   * It removes a user from the admin role of a channel and emits the updated channel details.
   * @param socket - The socket that initiated the 'removeadminfromchannel' event.
   * @param username - The username of the user to remove from admin role.
   * @param channelname - The name of the channel.
   * @returns A promise representing the completion of the event handling.
   */
  @SubscribeMessage('removeadminfromchannel')
  async removeAdminFromChannel(
    socket: Socket,
    {
      userId,
      channelId,
    }: {
      userId: string;
      channelId: string;
    },
  ): Promise<boolean> {
    const channel = await this.dataSource.manager.findOne(Channel, {
      where: { id: channelId },
      relations: ['admins', 'bans', 'members', 'mutes', 'owner'],
    });
    const user = await this.dataSource.manager.findOneBy(User, {
      id: userId,
    });
    channel.admins = channel.admins.filter((a) => a.id !== user.id);
    await this.dataSource.manager.save(Channel, channel);
    this.socketService.getSocket(userId)?.emit('notification', {
      type: NotificationType.Error,
      message: `You have been removed from admin role of channel #${channel.name}`,
    });
    return this.server.emit('channel', this.formatChannel(channel));
  }
  async updateModal(
    socket: Socket,
    payload: { username: string; modal: any },
  ): Promise<void> {
    const socket_dest = this.socketService.getSocket(payload.username);
    if (socket_dest) {
      socket_dest.emit('update_modal', payload.modal);
    } else {
      Logger.error(
        `update_modal: ${payload.username} ${payload.modal} not sent, socket not found`,
      );
    }
  }

  @SubscribeMessage('create_game_proposal')
  async createGameProposal(socket: Socket, payload: any): Promise<void> {
    Logger.log('create_game_proposal');
    this.game_proposals.add({
      sender: this.socketService.getUserId(socket),
      recipient: payload.recipient,
      game_mode: payload.game_mode,
      limit_max: payload.limit_max,
    });
    await this.updateModal(socket, {
      username: payload.recipient,
      modal: 8,
    });
  }

  @SubscribeMessage('accept_game_proposal')
  async acceptGameProposal(socket: Socket): Promise<void> {
    let game_p = null;
    for (const game_p_tmp of this.game_proposals) {
      if (game_p_tmp.recipient == this.socketService.getUserId(socket)) {
        game_p = game_p_tmp;
        break;
      }
    }
    if (!game_p) {
      Logger.error(
        `accept_game_proposal: ${this.socketService.getUserId(
          socket,
        )} game proposal not found`,
      );
      return;
    }
    socket.emit('launch_game_proposal', {
      game_mode: game_p.game_mode,
      limit_max: game_p.limit_max,
    });
    this.socketService.getSocket(game_p.sender)?.emit('launch_game_proposal', {
      game_mode: game_p.game_mode,
      limit_max: game_p.limit_max,
    });
    this.game_proposals.delete(game_p);
  }

  @SubscribeMessage('refuse_game_proposal')
  async refuseGameProposal(socket: Socket): Promise<void> {
    Logger.log('refuse_game_proposal');
    let game_p = null;
    for (const game_p_tmp of this.game_proposals) {
      if (game_p_tmp.recipient == this.socketService.getUserId(socket)) {
        game_p = game_p_tmp;
        break;
      }
    }
    if (!game_p) {
      Logger.error('refuse_game_proposal: game proposal not found');
      return;
    }
    this.game_proposals.delete(game_p);
  }

  @SubscribeMessage('get_game_proposal')
  async getGameProposal(socket: Socket): Promise<void> {
    Logger.log('get_game_proposal');
    let game_p = null;
    for (const game_p_tmp of this.game_proposals) {
      if (game_p_tmp.recipient == this.socketService.getUserId(socket)) {
        game_p = game_p_tmp;
        break;
      }
    }
    if (!game_p) {
      Logger.error('get_game_proposal: game proposal not found');
      return;
    }
    socket.emit('get_game_proposal', {
      game_mode: game_p.game_mode,
      limit_max: game_p.limit_max,
    });
  }
}
