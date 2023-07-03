import { Module, forwardRef } from "@nestjs/common";
import { AuthService } from "./auth.service";
import { AuthController } from "./auth.controller";
import { UserModule } from "src/user/user.module";
import { JwtModule } from "@nestjs/jwt";
import { AccessTokenStrategy } from "./strategies/accessToken.strategy";
import { TypeOrmModule } from "@nestjs/typeorm";
import { User } from "src/entities/User";
import { PassportModule } from '@nestjs/passport';
import { TwoFactorAuthController } from "./2fa/twoFactorAuth.controller";
import { twoFactorAuthService } from "./2fa/twoFactorAuth.service";

@Module({
    imports: [UserModule, PassportModule, JwtModule.register({
        secret: process.env.JWT_SECRET,
        signOptions:{expiresIn: '15m'},
    }), TypeOrmModule.forFeature([User])],
    controllers: [AuthController, TwoFactorAuthController],
    providers: [AuthService, AccessTokenStrategy, twoFactorAuthService],
    exports: [AuthService],
})
export class AuthModule{}
