import { Injectable } from '@nestjs/common';
import { Socket } from 'socket.io';

export enum NotificationType {
  Info,
  Success,
  Warning,
  Error,
}

type Connection = {
  socket: Socket;
  date: Date;
};

@Injectable()
export class SocketsService {
  public socketUsers = new Map<string, Connection>();

  addSocket(userId: string, socket: Socket) {
    this.socketUsers.set(userId, { socket, date: new Date() });
  }

  removeSocket(
    socket: Socket,
  ): { userId: string; minutesSpent: number } | undefined {
    for (const [userId, connection] of this.socketUsers.entries()) {
      if (connection.socket === socket)
        return {
          userId,
          minutesSpent:
            (new Date().getTime() - connection.date.getTime()) / 60000,
        };
    }
    return undefined;
  }

  getSocket(userId: string): Socket | undefined {
    return this.socketUsers.get(userId)?.socket;
  }

  getUserId(to_search: Socket): string | undefined {
    for (const [key, value] of this.socketUsers.entries()) {
      if (value.socket === to_search) return key;
    }
    return undefined;
  }
}
