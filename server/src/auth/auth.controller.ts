import { Controller, Post, Body, UnauthorizedException } from '@nestjs/common';
import { AuthService } from './auth.service';

@Controller('auth')
export class AuthController {
  constructor(private authService: AuthService) {}

  @Post('register')
  async register(@Body() body: { email: string; passwordHash: string }) {
    return this.authService.register(body.email, body.passwordHash);
  }

  @Post('login')
  async login(@Body() body: { email: string; passwordHash: string }) {
    const user = await this.authService.validateUser(body.email, body.passwordHash);
    if (!user) {
      throw new UnauthorizedException('Невірні дані для входу');
    }
    return this.authService.login(user);
  }
}
