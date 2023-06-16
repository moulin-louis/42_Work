import { Socket } from 'socket.io';

// This code defines a Player object which contains information about a player in the game.
// socket: The socket through which the player communicates with the server.
// x: The player's x-coordinate.
// y: The player's y-coordinate.
// score: The player's current score.
class Player {
  socket: Socket;
  x: number;
  y: number;
  score: number;
  constructor(socket: Socket, x: number) {
    this.socket = socket;
    this.x = x;
    this.y = 150;
    this.score = 0;
  }
}

export default Player;
