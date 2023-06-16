import {
  WINDOWHEIGHT,
  MIDDLE_WIN,
  DFSPEED,
  DFRADIUS,
  PADDLEHEIGHT,
  WINDOWWIDTH,
} from './const_game';
import Player from './Player';

class Ball {
  public x: number; // The x coordinate of the center of the circle
  public y: number; // The y coordinate of the center of the circle
  public vx: number; // The x component of the velocity of the circle
  public vy: number; // The y component of the velocity of the circle
  public speed: number; // The speed of the circle
  public radius: number; // The radius of the circle

  // This code creates a ball object that moves horizontally across the screen. The ball has a random horizontal velocity, and it moves at a constant vertical speed. The ball's position is represented by the center of the ball, and the ball's radius is 10 pixels.
  constructor() {
    this.x = WINDOWHEIGHT / 2;
    this.vx = (Math.random() > 0.5 ? 1 : -1) * (1 + Math.random());
    this.y = MIDDLE_WIN;
    this.vy = (Math.random() > 0.5 ? 1 : -1) * (1 + Math.random());
    this.speed = DFSPEED;
    this.radius = DFRADIUS;
  }

  // This code moves the sprite at the speed specified by the vx and vy variables.
  public move(): void {
    this.x += this.vx * this.speed;
    this.y += this.vy * this.speed;
  }

  // This code checks if the ball has collided with the paddle, and if so, it
  // makes the ball bounce off the paddle at an angle.
  public bouncePaddle(player: Player): void {
    if (
      this.x - this.radius < player.x &&
      this.x + this.radius > player.x - 10 &&
      this.y - this.radius < player.y + PADDLEHEIGHT &&
      this.y + this.radius > player.y
    ) {
      const hitLocation = (this.y - player.y) / PADDLEHEIGHT; // calculate where the ball hit the paddle
      this.vx < 0 ? (this.vx -= 0.5) : (this.vx += 0.5); // increase the speed of the ball
      this.vx = -this.vx;
      this.vy = 3 * hitLocation - 1; // deflect the ball's direction based on where it hit the paddle
    }
  }

  // This function checks if the ball has bounced off the top, bottom, or sides of the window.
  // If so, it inverts the ball's velocity in the appropriate direction.
  //It returns true if the ball has bounced off the window or  not
  public bounceEdge(): boolean {
    if (this.y - this.radius < 0 || this.y + this.radius > WINDOWHEIGHT)
      this.vy = -this.vy;
    if (this.x - this.radius < 0 || this.x + this.radius > WINDOWWIDTH)
      return true;
    return false;
  }

  // This code resets the ball's position and velocity.
  public reset() {
    this.x = WINDOWHEIGHT / 2;
    this.vx = (Math.random() > 0.5 ? 1 : -1) * (1 + Math.random());
    this.y = MIDDLE_WIN;
    this.vy = (Math.random() > 0.5 ? 1 : -1) * (1 + Math.random());
    this.speed = DFSPEED;
    this.radius = DFRADIUS;
  }
}

export default Ball;
