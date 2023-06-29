import { Body, Controller, Post, Res, UseGuards } from "@nestjs/common";
import { AccessTokenGuard } from "../guards/accessToken.guard";
import { twoFactorAuthService } from "./twoFactorAuth.service";
import { Response } from "express";
import { UserService } from "src/user/user.service";
import { User } from "src/entities/User";
import { ActivateTwoFactorDTO } from "../dto/twoFactor.dto";
import { AuthService } from "../auth.service";

@Controller('2fa')
export class TwoFactorAuthController{
    constructor(
        private readonly twoFactorService: twoFactorAuthService,
        private readonly userService: UserService,
        private readonly authService: AuthService,
    ){}

    @Post('generate')
    async generateTwoFactor(@Body() body: { username: string }, @Res() res:Response){
        const username = body.username;
        return await this.twoFactorService.generateTwoFactorAuthenticationSecret(username, res);
    }

    @Post('desactivate')
    async desactivateTwoFactor(@Body() body: {username:string}){
        const username = body.username;
        await this.userService.switchTwoFactorAuth('', username);
    }

    @Post('activate')
    async activateTwoFactor(@Body('twoFactorAuthenticationCode') code: string, @Body('id') id: string, @Res() res: Response) {
      const user: User = await this.userService.getById(id);
      if (user) {
        if (!user.twoFactorAuthSecret) {
          res.status(400).json({error: 'Your secret is invalid'});
        }

        const isCodeMatch: boolean | null = await this.twoFactorService.isTwoFactorAuthenticationCodeValid(code, user.id);
        if (!isCodeMatch) {
          res.status(400).json({error:'Your secret is invalid'});
          return ;
        }
        const username = user.username;
        await this.userService.activateTwoFactorAuth(username);
        res.status(201).json({message: 'You have activated the two factors authentication'});
      }
    }
    @Post('validate')
async validateSignin(@Body('id') id: string, @Body('code') code: string, @Res() res: any) {
  const user = await this.userService.getById(id);
  const token = await this.authService.signToken(id, user.username);
  const cookieToken = await this.authService.getCookieWithJwtAccessToken(token);
  const tempCookie = this.authService.getCookieWithTemporaryErase();

  if (!user?.twoFactorAuthSecret) {
    res.status(400).json({ error: 'Your secret is invalid' });
    return;
  }

  const isCodeMatch: boolean | null = await this.twoFactorService.isTwoFactorAuthenticationCodeValid(code, user.id);

  if (!isCodeMatch) {
    res.status(400).json({ error: 'Your secret is invalid' });
  } else {
    res.setHeader('Set-Cookie', [cookieToken, tempCookie]);
    res.status(200).json({ redirectUrl: `http://localhost:${process.env.PORT}/settings?accessToken=${cookieToken}` });
  }
}


}
