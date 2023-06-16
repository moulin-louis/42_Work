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
        console.log(username); // Output: lmasson
        console.log(typeof username); // Output: string
        // Rest of your code...
        return await this.twoFactorService.generateTwoFactorAuthenticationSecret(username, res);
    }

    @Post('desactivate')
    async desactivateTwoFactor(@Body() body: {username:string}){
        const username = body.username;
        await this.userService.switchTwoFactorAuth('', username);
    }

    @Post('activate')
    async activateTwoFactor(@Body('twoFactorAuthenticationCode') code: string, @Body('id') id: string, @Res() res: Response) {
      console.debug("enter activateTwoFactor");
      console.log(code);
      console.log(typeof id);
      
      const user: User = await this.userService.getById(id);
      if (user) {
        console.debug("activateTwoFactor: There is a user");
        if (!user.twoFactorAuthSecret) {
          res.send('Your secret is invalid');
        }
        
        const isCodeMatch: boolean | null = await this.twoFactorService.isTwoFactorAuthenticationCodeValid(code, user.id);
        if (!isCodeMatch) {
          console.log("not a match");
          res.send('Your secret is invalid');
          return ;
        }
        console.log("Code is a match, everything is working");
        const username = user.username;
        console.log(username);
        await this.userService.activateTwoFactorAuth(username);
        console.debug("ok");
        console.log(user);
        res.status(201).send();
      }
    }
    @Post('validate')
    async validateSignin(@Body('id') id: string, @Body('code') code: string, @Res() res: Response) {
      console.log("validate method");
      const user = await this.userService.getById(id);
      const token = await this.authService.signToken(id, user.username);
      const cookieToken = await this.authService.getCookieWithJwtAccessToken(token);
      const tempCookie = this.authService.getCookieWithTemporaryErase();
      if (!user?.twoFactorAuthSecret) {
        res.status(400).send('You secret is invalid');
        //TODO
      }
      const isCodeMatch: boolean | null = await this.twoFactorService.isTwoFactorAuthenticationCodeValid(code, user.id);
      if (!isCodeMatch) {
        console.log("not a match");
        res.status(400).send('Your secret is invalid');
        return;
      } else{
      console.log(tempCookie);
      console.log(cookieToken);
      res.setHeader('Set-Cookie', [cookieToken, tempCookie]).status(200).send();
      }
    }
    

}