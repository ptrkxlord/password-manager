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
    const existing = await this.prisma.vaultBackup.findFirst({ where: { userId, deviceId } });
    if (existing) {
      return this.prisma.vaultBackup.update({
        where: { id: existing.id },
        data: {
          encryptedBlob,
          version: { increment: 1 },
        },
      });
    } else {
      return this.prisma.vaultBackup.create({
        data: {
          userId,
          deviceId,
          encryptedBlob,
          version: 1,
        },
      });
    }
  }
}
