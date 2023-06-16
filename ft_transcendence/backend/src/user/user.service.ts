import { HttpException, HttpStatus, Injectable, ForbiddenException, NotFoundException} from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository, Equal, EqualOperator } from 'typeorm';
import CreateUserDto from './dto/createUser.dto';
import { User } from 'src/entities/User';
import * as argon from 'argon2';


@Injectable()
export class UserService {
    constructor(
        @InjectRepository(User) private readonly usersRepository: Repository<User>,
      ) {}

      async getByUsername(username: string): Promise<User | undefined>{
        console.log(username);
        console.log(typeof username);
  
        const user = await this.usersRepository.findOne({where:{username: Equal(username)} });
        console.log(user);
        return user;
      }

      async getByLogin(login: string): Promise<User | undefined>{
        const user: User = await this.usersRepository.findOne({where:{login:Equal(login)}});
        return user;
      }

      async getById(id: string): Promise<User | undefined>{
        console.log("getById method ", id);
        const user: User = await this.usersRepository.findOne({where:{id:Equal(id)}});
        return user;
      }

      async getAllUsers(): Promise <User[]> | null{
        console.log('getAllUser');
        return (await this.usersRepository.find());
      }

      async getAllFriends(id:string): Promise<User[]> | null {
        return ((await this.getById(id)).friends);
      }

      async getAllChannel(id:string): Promise<User[]> | null {
        return (await this.usersRepository.find({relations:{channelMember:true},}));
      }

      async updateUsername(user: User, newUsername: string): Promise<User>
      {
        if (!newUsername)
            throw new HttpException('New username can not be empty', HttpStatus.FORBIDDEN);
        if (!user)
            throw new HttpException('You must be connected to perform this operation', HttpStatus.FORBIDDEN);
        if (user.username == newUsername)
            return user;
        const userCheck: User = await this.getByUsername(newUsername);
        if (userCheck)
            throw new HttpException('New username is not available', HttpStatus.FORBIDDEN);
        user.username = newUsername;
        await this.usersRepository.save(user);
        return user;
      }

      async updateRefreshToken(userId: string, refreshToken: string): Promise<void>{
          const hashedRefreshToken = await argon.hash(refreshToken);
          const user = await this.usersRepository.findOne({where:{id:Equal(userId)}});
          user.token = hashedRefreshToken;
          await this.usersRepository.save(user);
      }


      async create(userData: CreateUserDto) {
        if (!userData.username || !userData.password)
            throw new HttpException("You must enter a valid password and/or username", HttpStatus.FORBIDDEN);
        const user: User = await this.getByUsername(userData.username);
        console.log(user);
        if (user)
        {
          console.log("error");
            throw new HttpException('Username not availaible', HttpStatus.FORBIDDEN);
        }
        const newUser: User = await this.usersRepository.create(userData);
        return await this.usersRepository.save(newUser);
      }

      async create42User(login: string, email:string, avatar:string)
      {
        if (!login)
          throw new HttpException('You must have 42 account to play this game!', 404);
          let username : string = login;
          let userLogin : User | null = await this.getByUsername(username);
          while (userLogin)
          {
            username = this.addRandomPrefix(3, login);
            userLogin = await this.getByUsername(username);
          }

        const newUser: User = await this.usersRepository.create({login, username, email, avatar});
        return await this.usersRepository.save(newUser);
      }

      addRandomPrefix(length: number, stg: string): string {
        const characters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
        let randomString = '';

        for (let i = 0; i < length; i++) {
          const randomIndex = Math.floor(Math.random() * characters.length);
          randomString += characters.charAt(randomIndex);
        }

        return randomString + stg;
      }


      async delete(id: string) {
        if (!id)
            throw new HttpException("You must be connected to perform this operation", HttpStatus.FORBIDDEN);
        const userToDelete: User = await this.usersRepository.findOne({where:{id:Equal(id)}});
        if (!userToDelete)
            throw new HttpException("Something went wrong, you can't perform this operation", HttpStatus.FORBIDDEN);
        await this.usersRepository.remove(userToDelete);
      }

      async switchTwoFactorAuth(secret: string, username:string){
        console.log("switch service");
        console.log(username);
        const user = await this.getByUsername(username);
        console.log(user);
        if (user){
          console.log("secret ", secret);
          user.twoFactorAuthSecret = secret;
          user.twoFactorAuthActivated = false;
          user.authEnable = false;
          if (secret){
            user.authEnable = true;
          }
          await this.usersRepository.save(user);
        }
      }

      async activateTwoFactorAuth(username:string){
        console.log("username",username);
        const user = await this.getByUsername(username);
        if (user){
          user.twoFactorAuthActivated = true;
          user.authEnable = true;
          await this.usersRepository.save(user);
        }
      }
}
