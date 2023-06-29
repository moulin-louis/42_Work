import { Body, Controller, Post, Get, UseGuards, Res, HttpCode, HttpStatus, UnauthorizedException, Req, Query, Redirect} from '@nestjs/common';
import { AuthService } from './auth.service';
import { AuthDto } from './dto';
import { AccessTokenGuard } from './guards/accessToken.guard';
import { JwtService } from '@nestjs/jwt';
import { UserService } from 'src/user/user.service';
import { JwtPayload } from './strategies';
import { User } from 'src/entities/User';
import { InjectRepository } from '@nestjs/typeorm';
import { Equal, Repository } from 'typeorm';
import { Response } from 'express';


@Controller('auth')
export class AuthController {
  constructor(
    @InjectRepository(User) private readonly usersRepository: Repository<User>,
    private authService: AuthService,
    private readonly userService: UserService,
    private readonly jwt: JwtService,) { }

    @Get('me')
    async findMe(@Query('token') token: string){
      const decodedToken = this.jwt.decode(token);
      const id = decodedToken?.sub;
      const user: User = await this.usersRepository.findOne({ where: { id: id } });
      return user;
    }

    @Get('callback')
    async login(@Req() req, @Res() res: any) {
      const user = await this.authService.login(req.query.code);
      if (!user)
        throw new UnauthorizedException();
      const token = await this.authService.signToken(user.id, user.username);
      let accessTokenCookie = this.authService.getCookieWithJwtAccessToken(token);
      let temporaryTokenCookie = this.authService.getCookieWithTemporaryToken(token);
      if (user.twoFactorAuthActivated){
        accessTokenCookie = this.authService.getCookieWithJwtLogout();
        res.setHeader('Set-Cookie', [accessTokenCookie, temporaryTokenCookie]).redirect(`http://localhost:${process.env.PORT}/2fa`);
      }else{
        user.token = token;
        await this.usersRepository.save(user);
        temporaryTokenCookie = this.authService.getCookieWithTemporaryErase();
        res.setHeader('Set-Cookie', [accessTokenCookie, temporaryTokenCookie]);
        res.redirect(`http://localhost:${process.env.PORT}/settings`); // Redirect with the accessToken as a query parameter
      }
    }

  @Post('signup')
  async signup(@Body() dto: AuthDto, @Res() res:any) {
    const user = await this.authService.signup(dto);
    const token = await this.authService.signToken(user.id, user.username);
    user.token = token;
    await this.usersRepository.save(user);
    const accessTokenCookie = this.authService.getCookieWithJwtAccessToken(token);
    res.setHeader('Set-Cookie', [accessTokenCookie]);
    res.sendStatus(201);
  }

  @Post('signin')
  async signin(@Body() dto: AuthDto, @Res() res: any) {
    const user = await this.authService.signin(dto);
    const token = await this.authService.signToken(user.id, user.username);
    let accessTokenCookie = this.authService.getCookieWithJwtAccessToken(token);
    let temporaryTokenCookie = this.authService.getCookieWithTemporaryToken(token);

    if (user.twoFactorAuthActivated) {
      accessTokenCookie = this.authService.getCookieWithJwtLogout();
      res.setHeader('Set-Cookie', [accessTokenCookie, temporaryTokenCookie]);
      res.status(200).json({ redirectUrl: `http://localhost:${process.env.PORT}/2fa` });
    } else {
      temporaryTokenCookie = this.authService.getCookieWithTemporaryErase();
      res.setHeader('Set-Cookie', [accessTokenCookie, temporaryTokenCookie]);
      res.status(200).json({ redirectUrl: `http://localhost:${process.env.PORT}/settings?accessToken=${accessTokenCookie}` });
    }
  }

  @Get('logout')
  @HttpCode(HttpStatus.OK)
  async logout(@Res() res, @Req() req) {
    const accessToken = req.headers.authorization.split(' ')[1];
    const decodedToken = this.jwt.decode(accessToken);
    await this.authService.logout(decodedToken.sub);
    const user = await this.userService.getById(decodedToken.sub);
    const cookie = this.authService.getCookieWithJwtLogout();
    res.setHeader('Set-Cookie', [cookie]);
    res.status(200).send();
  }
}
