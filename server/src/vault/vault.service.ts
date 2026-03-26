import { Injectable } from '@nestjs/common';
import { PrismaService } from '../prisma.service';

@Injectable()
export class VaultService {
  constructor(private prisma: PrismaService) {}

  async getBackup(userId: string, deviceId: string) {
    return this.prisma.vaultBackup.findFirst({
      where: { userId, deviceId },
      orderBy: { updatedAt: 'desc' },
    });
  }

  async saveBackup(userId: string, deviceId: string, encryptedBlob: Buffer) {
    return this.prisma.vaultBackup.upsert({
      where: {
        // We'd ideally need a unique constraint on userId + deviceId in schema.prisma 
        // to use a simple upsert here, but for now we find and update or create.
        id: (await this.prisma.vaultBackup.findFirst({ where: { userId, deviceId } }))?.id || 'new-id',
      },
      update: {
        encryptedBlob,
        version: { increment: 1 },
      },
      create: {
        userId,
        deviceId,
        encryptedBlob,
        version: 1,
      },
    });
  }
}
