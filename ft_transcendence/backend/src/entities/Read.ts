import {
  Entity,
  PrimaryGeneratedColumn,
  CreateDateColumn,
  JoinColumn,
  ManyToOne,
} from 'typeorm';
import { User } from './User';
import { Channel } from './Channel';

@Entity('reads')
export class Read {
  @PrimaryGeneratedColumn('uuid')
  id: string;

  @CreateDateColumn()
  date: Date;

  @ManyToOne(() => User, (user) => user.id)
  @JoinColumn()
  from: User;

  @ManyToOne(() => User, (user) => user.read, { nullable: true })
  @JoinColumn()
  toUser: User;

  @ManyToOne(() => Channel, (channel) => channel.read, {
    nullable: true,
    onDelete: 'CASCADE',
  })
  @JoinColumn()
  toChannel: Channel;
}
