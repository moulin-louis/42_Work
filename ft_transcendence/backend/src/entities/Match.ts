import {
  Entity,
  PrimaryGeneratedColumn,
  Column,
  ManyToOne,
  CreateDateColumn,
} from 'typeorm';
import { User } from './User';

@Entity('matches')
export class Match {
  @PrimaryGeneratedColumn('uuid')
  id: string;

  @ManyToOne(() => User, (user) => user.wonMatches)
  winner: User;

  @ManyToOne(() => User, (user) => user.lostMatches)
  loser: User;

  @Column()
  winnerScore: number;

  @Column()
  loserScore: number;

  @CreateDateColumn()
  createdAt: Date;
}
