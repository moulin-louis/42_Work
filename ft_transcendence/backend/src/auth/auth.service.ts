import {
  ForbiddenException,
  Injectable,
  NotFoundException,
} from '@nestjs/common';
import { AuthDto } from './dto';
import * as argon from 'argon2';
import fetch from 'node-fetch';
import { User } from '../entities/User';
import { UserService } from 'src/user/user.service';
import { JwtService } from '@nestjs/jwt';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';

@Injectable()
export class AuthService {
  constructor(
    @InjectRepository(User) private readonly usersRepository: Repository<User>,
    private readonly userService: UserService,
    private readonly jwt: JwtService,
  ) {}

  async login(code: string): Promise<User> {
    const uid = process.env.INTRA42_UID;
    const secret = process.env.INTRA42_SECRET;
    const url = process.env.URL42_TOKEN;
    const body = new URLSearchParams();
    body.append('grant_type', 'authorization_code');
    body.append('client_id', uid);
    body.append('client_secret', secret);
    body.append('code', code);
    body.append(
      'redirect_uri',
      `http://localhost:${process.env.PORT}/auth/callback`,
    );

    const response = await fetch(url, {
      method: 'POST',
      body,
    });

    const { access_token: accessToken } = await response.json();

    const currentUser = await (
      await fetch(process.env.URL42_ME, {
        headers: {
          Authorization: `Bearer ${accessToken}`,
        },
      })
    ).json();
    const login: string = currentUser.login;
    const email: string = currentUser.email;
    const avatar: string = currentUser.image.link;
    let user: User | null = await this.userService.getByLogin(login);
    if (user == null) {
      user = await this.userService.create42User(login, email, avatar);
    }
    return user;
  }

  async signin(dto: AuthDto) {
    const user = await this.userService.getByUsername(dto.username);
    if (!user) throw new ForbiddenException('Credentials incorrect');
    const passwordCheck = await argon.verify(user.password, dto.password);
    if (!passwordCheck) throw new ForbiddenException('Credentials incorrect');
    return user;
  }

  async signup(dto: AuthDto) {
    if (!dto.password || !dto.username || !dto.username.replace(/\s/g, '').length || !dto.password.replace(/\s/g, '').length)
      throw new ForbiddenException('Can not be empty or fill with white space');
    const hash = await argon.hash(dto.password);
    const data = {
      username: dto.username,
      password: hash,
      email: '',
    };
    const newUser: User = await this.userService.create(data);
    return newUser;
  }

  async logout(userId: string): Promise<boolean> {
    const user = await this.userService.getById(userId);
    if (!user) {
      throw new NotFoundException('User not found');
    }
    user.token = null;
    await this.usersRepository.save(user);
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
          secret: process.env.JWT_SECRET,
          expiresIn: process.env.JWT_TIME,
        },
      ),
    ]);
    return access_token;
  }

  getCookieWithJwtAccessToken(accessToken: string) {
    return `Authentication=${accessToken}; Path=/;`;
  }

  getCookieWithTemporaryToken(temporaryToken: string) {
    return `Temporary=${temporaryToken}; Path=/;`;
  }

  getCookieWithTemporaryErase() {
    return `Temporary=; Path=/;`;
  }

  getCookieWithJwtLogout() {
    return `Authentication=; Path=/;`;
  }
}
