import { Module } from '@nestjs/common';
import { VaultService } from './vault.service';
import { VaultController } from './vault.controller';
import { PrismaService } from '../prisma.service';

@Module({
  providers: [VaultService, PrismaService],
  controllers: [VaultController],
})
export class VaultModule {}
