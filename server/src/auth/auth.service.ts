import { Injectable, UnauthorizedException } from '@nestjs/common';
import { UsersService } from '../users/users.service';
import { JwtService } from '@nestjs/jwt';
import * as bcrypt from 'bcrypt';

@Injectable()
export class AuthService {
  constructor(
    private usersService: UsersService,
    private jwtService: JwtService,
  ) {}

  async validateUser(email: string, pass: string): Promise<any> {
    const user = await this.usersService.findOne(email);
    if (user && (await bcrypt.compare(pass, user.passwordHash))) {
      const { passwordHash, ...result } = user;
      return result;
    }
    return null;
  }

  async login(user: any) {
    const payload = { email: user.email, sub: user.id };
    return {
      access_token: this.jwtService.sign(payload),
    };
  }

  async register(email: string, passwordHash: string) {
    // Note: client sends passwordHash, we hash it AGAIN on server for storage 
    // strictly for defense-in-depth, or store as provided. 
    // Principle: master password never leaves client, but we hash it on client 
    // and send the derived "auth hash" to server.
    return this.usersService.create({
      email,
      passwordHash, // This is already hashed on client
    });
  }
}
