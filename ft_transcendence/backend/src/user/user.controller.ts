import { Controller, Get, Param, Post, Req, Res } from '@nestjs/common';
import { UserService } from './user.service';
import { User } from 'src/entities/User';
import { JwtService } from "@nestjs/jwt";
import { JwtPayload } from 'src/auth/strategies';



@Controller('user')
export class UserController {
    constructor(private readonly userService: UserService,
      private readonly jwt: JwtService,){}
    @Post('work')
    print(){
      return console.log('work');
    }



    @Get('all')
    async findAll(): Promise<User[] | undefined>{
            return await this.userService.getAllUsers();
    }

    @Get('friends')
    async findMyFriends(@Req() req:any, @Res() res:any) {
      res.send(req.user.friends);
  }

  @Get('friends/:id')
  async showFriends(@Req() req, @Param('id') id:string):Promise<User[]>{
    return await this.userService.getAllFriends(id);
  }

  @Get('blocked')
  async findBlockedUsers(@Req() req, @Res() res){
      res.send(req.user.blocked);
  }
//TODO method update username
//TODO method update token
//TODO method delete
//all method must be protected @UseGuards(AccessTokenGuard)

}
