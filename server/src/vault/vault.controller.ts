import { Controller, Post, Get, Body, UseGuards, Request } from '@nestjs/common';
import { VaultService } from './vault.service';
import { JwtAuthGuard } from '../auth/jwt-auth.guard';

@Controller('vault')
export class VaultController {
  constructor(private vaultService: VaultService) {}

  @UseGuards(JwtAuthGuard)
  @Post('backup')
  async backup(@Request() req, @Body() body: { deviceId: string; blob: string }) {
    const buffer = Buffer.from(body.blob, 'base64');
    return this.vaultService.saveBackup(req.user.userId, body.deviceId, buffer);
  }

  @UseGuards(JwtAuthGuard)
  @Get('restore')
  async restore(@Request() req, @Body() body: { deviceId: string }) {
    const backup = await this.vaultService.getBackup(req.user.userId, body.deviceId);
    return {
      blob: backup ? Buffer.from(backup.encryptedBlob).toString('base64') : null,
      version: backup ? backup.version : 0,
    };
  }
}
