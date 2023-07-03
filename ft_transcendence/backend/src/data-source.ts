import { TypeOrmModuleOptions } from '@nestjs/typeorm';
import { Channel } from './entities/Channel';
import { Message } from './entities/Message';
import { Match } from './entities/Match';
import { User } from './entities/User';
import { Read } from './entities/Read';

const config: TypeOrmModuleOptions = {
  type: 'postgres',
  host: process.env.POSTGRES_HOST,
  port: Number(process.env.POSTGRES_PORT),
  username: process.env.POSTGRES_USER,
  password: process.env.POSTGRES_PASSWORD,
  database: process.env.POSTGRES_DB,
  entities: [Channel, Match, Message, Read, User],
  synchronize: true,
};

export = config;
