import {
  Entity,
  PrimaryGeneratedColumn,
  Column,
  ManyToMany,
  OneToMany,
  JoinColumn,
  ManyToOne,
  JoinTable,
} from 'typeorm';
import { Message } from './Message';
import { User } from './User';
import { Read } from './Read';

@Entity('channels')
export class Channel {
  @PrimaryGeneratedColumn('uuid')
  id: string;

  @Column({ unique: true })
  name: string;

  @OneToMany(() => Message, (message) => message.toChannel)
  messages: Message[];

  @Column({ nullable: true })
  password: string;

  @Column({ type: 'boolean', default: false })
  secret: boolean;

  @Column({ type: 'boolean', default: false })
  protected: boolean;

  @ManyToOne(() => User, (user) => user.channelOwner, { nullable: true })
  @JoinColumn()
  owner: User;

  @ManyToMany(() => User, (user) => user.channelAdmin, { nullable: true })
  @JoinTable()
  admins: User[];

  @ManyToMany(() => User, (user) => user.channelMember, { nullable: true })
  @JoinTable()
  members: User[];

  @ManyToMany(() => User, (user) => user.channelBanned, { nullable: true })
  @JoinTable()
  bans: User[];

  @ManyToMany(() => User, (user) => user.channelBanned, { nullable: true })
  @JoinTable()
  mutes: User[];

  @OneToMany(() => Read, (read) => read.toChannel, { nullable: true })
  read: Read[];
}
