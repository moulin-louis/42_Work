import { ForbiddenException,  Injectable } from "@nestjs/common";
import { AuthDto } from "./dto";
import * as argon from 'argon2';
import fetch from 'node-fetch';
import { User } from '../entities/User';
import { UserService } from "src/user/user.service";
import { JwtService } from "@nestjs/jwt";
import { InjectRepository } from "@nestjs/typeorm";
import { Repository } from "typeorm";
import { NotFoundException } from '@nestjs/common';



@Injectable()
export class AuthService {
  constructor(
    @InjectRepository(User) private readonly usersRepository: Repository<User>,
    private readonly userService: UserService,
    private readonly jwt: JwtService,
  ) { }

  async login(code: string): Promise<User>{
    console.log("login service");
    const uid =
      'u-s4t2ud-84c20f8d4c77eabe9e303a277c56fc8e113f81b79804c6596c299b6f2a2f5de8'; //process.env.INTRA42_UID;
    const secret =
      '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'; //process.env.INTRA42_SECRET;
    //TODO changer en secret .env
    const url = 'https://api.intra.42.fr/oauth/token'; //process.env.URL42_TOKEN
    const body = new URLSearchParams();
    body.append('grant_type', 'authorization_code');
    body.append('client_id', uid);
    body.append('client_secret', secret);
    body.append('code', code);
    body.append('redirect_uri', `http://localhost:3000/auth/callback`); //'process.env.URL42_TOKEN'

    const response = await fetch(url, {
      method: 'POST',
      body,
    });

    const { access_token: accessToken } = await response.json();

    const currentUser = await (
      await fetch('https://api.intra.42.fr/v2/me', {
        headers: {
          Authorization: `Bearer ${accessToken}`,
        },
      })
    ).json();
    const login: string = currentUser.login;
    const email: string = currentUser.email;
    const avatar:string = currentUser.image.link;
    //console.log("AVATAR : ", avatar);
    let user: User | null = await this.userService.getByLogin(login);
    console.log(user);
    if (user == null)
    {
      console.log("new user");
      user = await this.userService.create42User(login, email, avatar);
    }
    console.log(user);
    return user;
  }

  async signin(dto: AuthDto) {
    const user = await this.userService.getByUsername(dto.username);
    if (!user)
      throw new ForbiddenException('Credentials incorrect');
    const passwordCheck = await argon.verify(
      user.password,
      dto.password,
    );
    if (!passwordCheck)
      throw new ForbiddenException('Credentials incorrect');
    return user;
  }

  async signup(dto: AuthDto){
    const hash = await argon.hash(dto.password);
    const data = {
      username: dto.username,
      password: hash,
      email:"",
    }
    const newUser: User = await this.userService.create(data);
    return newUser;
  }



  async logout(userId: string): Promise<boolean> {
    console.log(userId);
    const user = await this.userService.getById(userId);
    if (!user) {
      throw new NotFoundException('User not found');
    }
    user.token = null;
    const updatedUser = await this.usersRepository.save(user);
    return true;
  }


  async signToken(userId: string, username: string): Promise<string> {
    const [access_token] = await Promise.all([
      this.jwt.signAsync(
        {
          sub: userId,
          username: username,
        },
        {
          secret: 'my_super_secret', //TODO config
          expiresIn: '7d',
        },
      ),
    ]);
    return access_token;
  }

  getCookieWithJwtAccessToken(accessToken:string){
    return `Authentication=${accessToken}; Path=/;`;
  };

  getCookieWithTemporaryToken(temporaryToken:string){
    return `Temporary=${temporaryToken}; Path=/;`;
  };

  getCookieWithTemporaryErase(){
    return `Temporary=; Path=/;`;
  };

    getCookieWithJwtLogout(){
    return `Authentication=; Path=/;`;
  };



}
