import { Injectable } from "@nestjs/common";
import { UserService } from "src/user/user.service";
import { authenticator } from "otplib";
import * as qrCode from 'qrcode';
import { Response } from "express";


@Injectable()
export class twoFactorAuthService{
    constructor(
        private readonly userService: UserService,
    ){}
    async generateTwoFactorAuthenticationSecret(username:string, res:Response){
      const user = await this.userService.getByUsername(username);
      let secret:string;
      if (user && user.twoFactorAuthSecret)
      {
        secret = user.twoFactorAuthSecret;
      }
      else
      {
        secret = authenticator.generateSecret();
        await this.userService.switchTwoFactorAuth(secret, username);
      }
        const otpauthUrl = authenticator.keyuri(username, 'transcendance', secret); 
        const QRCode = await qrCode.toDataURL(otpauthUrl);
        return res.status(201).send(QRCode);
      }
    
      async isTwoFactorAuthenticationCodeValid(twoFactorAuthenticationCode: string, id:string): Promise<boolean | null>{
        const user = await this.userService.getById(id);
        if (user !== null)
        {
          return authenticator.verify({
            token: twoFactorAuthenticationCode,
            secret: user.twoFactorAuthSecret,
          });
        }
        return null;
      }
}