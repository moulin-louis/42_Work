import {
  Entity,
  PrimaryGeneratedColumn,
  Column,
  CreateDateColumn,
  JoinColumn,
  ManyToOne,
} from 'typeorm';
import { User } from './User';
import { Channel } from './Channel';

@Entity('messages')
export class Message {
  @PrimaryGeneratedColumn('uuid')
  id: string;

  @Column()
  message: string;

  @ManyToOne(() => User, (user) => user.id)
  @JoinColumn()
  from: User;

  @ManyToOne(() => User, (user) => user.id, { nullable: true })
  @JoinColumn()
  toUser: User;

  @ManyToOne(() => Channel, (channel) => channel.id, { nullable: true })
  @JoinColumn()
  toChannel: Channel;

  @CreateDateColumn()
  date: Date;
}
