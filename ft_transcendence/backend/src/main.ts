import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import * as cookieParser from 'cookie-parser';
import { ValidationPipe } from '@nestjs/common';
import * as os from 'os';
import { ExpressAdapter } from '@nestjs/platform-express';


const hostname = os.hostname().split('.')[0];
export default hostname;
async function bootstrap() {
  const app = await NestFactory.create(AppModule, new ExpressAdapter());
 // console.log(hostname);
  app.enableCors({
    origin: `http://localhost:4000`,
    credentials: true,
  });
  app.useGlobalPipes(
    new ValidationPipe({
      whitelist: true,
    }),
  );
  app.use(cookieParser());
  await app.listen(3000);
}
bootstrap();
