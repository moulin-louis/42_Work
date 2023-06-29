import {
  Injectable,
  CanActivate,
  ExecutionContext,
  Logger,
} from '@nestjs/common';
import { JwtService } from '@nestjs/jwt';

/**
 * A service for implementing access token guards.
 */
@Injectable()
export class AccessTokenGuard implements CanActivate {
  constructor(private readonly jwt: JwtService) {}

  /**
   * Determines whether the user can activate a given context.
   *
   * @param context - The execution context.
   * @returns A boolean indicating whether the user can activate a given context.
   */
  canActivate(context: ExecutionContext): boolean {
    const client = context.switchToWs().getClient();

    try {
      const token = client.handshake.query.token;
      const userId = client.handshake.query.userId;
      const user = this.jwt.verify(token, { secret: process.env.JWT_SECRET });

      return userId === user.sub;
    } catch (err) {
      Logger.error(err);

      return false;
    }
  }
}
