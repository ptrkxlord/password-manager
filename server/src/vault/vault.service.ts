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
    
    // Convert Buffer to Uint8Array for Prisma 7 compatibility
    const blobData = new Uint8Array(encryptedBlob);

    if (existing) {
      return this.prisma.vaultBackup.update({
        where: { id: existing.id },
        data: {
          encryptedBlob: blobData,
          version: { increment: 1 },
        },
      });
    } else {
      return this.prisma.vaultBackup.create({
        data: {
          userId,
          deviceId,
          encryptedBlob: blobData,
          version: 1,
        },
      });
    }
  }
}
