#include "KeyDerivationService.h"
#include <sodium.h>

KeyDerivationService::KeyDerivationService(QObject *parent) : QObject(parent) {}

QByteArray KeyDerivationService::deriveKey(const QString &password, const QByteArray &salt, 
                                          unsigned long long opslimit, size_t memlimit, 
                                          size_t keyLen)
{
    QByteArray key;
    key.resize(keyLen);
    
    QByteArray passBytes = password.toUtf8();

    if (crypto_pwhash_argon2id(
            (unsigned char *)key.data(), key.size(),
            passBytes.constData(), passBytes.size(),
            (const unsigned char *)salt.constData(),
            opslimit, memlimit,
            crypto_pwhash_ALG_ARGON2ID13
        ) != 0) {
        return QByteArray();
    }

    return key;
}

QByteArray KeyDerivationService::generateSalt()
{
    QByteArray salt;
    salt.resize(crypto_pwhash_SALTBYTES);
    randombytes_buf(salt.data(), salt.size());
    return salt;
}
