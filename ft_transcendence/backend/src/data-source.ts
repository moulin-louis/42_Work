import { TypeOrmModuleOptions } from '@nestjs/typeorm';
import { Channel } from './entities/Channel';
import { Message } from './entities/Message';
import { Match } from './entities/Match';
import { User } from './entities/User';
import { Read } from './entities/Read';

const config: TypeOrmModuleOptions = {
  type: 'postgres',
  host: 'database',
  port: 5432,
  // TODO change to env variables
  username: 'my_user',
  password: 'my_password',
  database: 'my_database',
  entities: [Channel, Match, Message, Read, User],
  synchronize: true,
};

export = config;
