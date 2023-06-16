import {
  Entity,
  PrimaryGeneratedColumn,
  Column,
  OneToMany,
  CreateDateColumn,
  UpdateDateColumn,
  ManyToMany,
  JoinTable,
} from 'typeorm';
import { Channel } from './Channel';
import { Read } from './Read';
import { Match } from './Match';
import { Message } from './Message';

export enum Status {
  OFFLINE,
  ONLINE,
  PLAYING,
}

@Entity('users')
export class User {
  @PrimaryGeneratedColumn('uuid')
  id: string;

  @Column({ unique: true })
  username: string;

  @Column({ nullable: true })
  login: string;

  @Column({ nullable: true })
  email: string;

  /*@BeforeInsert()
  @BeforeUpdate()
  emailToLowerCase() {
    this.email = this.email.toLowerCase();
  }*/

  @Column({ nullable: true })
  password: string;

  @Column({ nullable: true, type: 'text' })
  avatar: string;

  @Column({ type: 'enum', enum: Status, default: Status.OFFLINE })
  status: Status;

  @Column({ type: 'boolean', default: false })
  authEnable: boolean;

  @Column({ type: 'boolean', default: false })
  twoFactorAuthActivated: boolean;

  @Column({ nullable: true })
  twoFactorAuthSecret: string;

  @Column({ nullable: true })
  token: string;

  @Column({ type: 'float', default: 0 })
  logTimeInMinutes: number;

  @ManyToMany(() => User, (user) => user.id, { nullable: true })
  @JoinTable()
  friends: User[];

  @ManyToMany(() => User, (user) => user.id, { nullable: true })
  @JoinTable()
  friendRequest: User[];

  @ManyToMany(() => User, (user) => user.id, { nullable: true })
  @JoinTable()
  blocked: User[];

  @ManyToMany(() => Channel, (channel) => channel.owner, { nullable: true })
  channelOwner: Channel[];

  @ManyToMany(() => Channel, (channel) => channel.admins, { nullable: true })
  channelAdmin: Channel[];

  @ManyToMany(() => Channel, (channel) => channel.members, { nullable: true })
  channelMember: Channel[];

  @ManyToMany(() => Channel, (channel) => channel.bans, { nullable: true })
  channelBanned: Channel[];

  @ManyToMany(() => Channel, (channel) => channel.mutes, { nullable: true })
  channelMuted: Channel[];

  @OneToMany(() => Match, (match) => match.winner)
  wonMatches: Match[];

  @OneToMany(() => Match, (match) => match.loser)
  lostMatches: Match[];

  @OneToMany(() => Read, (read) => read.toUser)
  read: Read[];

  @OneToMany(() => Message, (message) => message.from)
  messagesSent: Message[];

  @OneToMany(() => Message, (message) => message.toUser)
  messagesReceived: Message[];

  @CreateDateColumn()
  created_at: Date;

  @UpdateDateColumn()
  updated_at: Date;
}
