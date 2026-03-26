#ifndef KEYDERIVATIONSERVICE_H
#define KEYDERIVATIONSERVICE_H

#include <QObject>
#include <QByteArray>

class KeyDerivationService : public QObject
{
    Q_OBJECT
public:
    explicit KeyDerivationService(QObject *parent = nullptr);

    // Argon2id KDF
    static QByteArray deriveKey(const QString &password, const QByteArray &salt, 
                               unsigned long long opslimit, size_t memlimit, 
                               size_t keyLen);

    static QByteArray generateSalt();
};

#endif // KEYDERIVATIONSERVICE_H
