import { Module } from '@nestjs/common';
import { ServeStaticModule } from '@nestjs/serve-static';
import { TypeOrmModule } from '@nestjs/typeorm';
import { AppGateway } from './app.gateway';
import { ChatGateway } from './chat/chat.gateway';
import * as config from './data-source';
import { SocketsService } from './sockets.service';
import { AuthModule } from './auth/auth.module';
import { UserModule } from './user/user.module';
import { User } from './entities/User';
import { GameGateway } from './game/game.gateway';
import { JwtService } from '@nestjs/jwt';
import { UserGateway } from './user/user.gateway';
import { HistoryGateway } from './history/history.gateway';

@Module({
  imports: [
    //ConfigModule.forRoot({}), //TODO config
    TypeOrmModule.forRoot(config),
    TypeOrmModule.forFeature([User]),
    ServeStaticModule.forRoot({
      rootPath: '/frontend/build',
    }),
    AuthModule,
    UserModule,
  ],
  providers: [
    AppGateway,
    ChatGateway,
    SocketsService,
    GameGateway,
    UserGateway,
    JwtService,
    HistoryGateway,
  ],
})
export class AppModule {}
