const { PrismaClient } = require('@prisma/client');
const prisma = new PrismaClient({});
prisma.$connect()
  .then(() => { console.log('Successfully connected!'); process.exit(0); })
  .catch(err => { console.error('Connection failed:', err); process.exit(1); });
