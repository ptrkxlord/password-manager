                                                                                                                                                                        #ifndef CRYPTOMANAGER_H
#define CRYPTOMANAGER_H

#include <QObject>
#include <QByteArray>
#include <sodium.h>

class CryptoManager : public QObject
{
    Q_OBJECT
public:
    explicit CryptoManager(QObject *parent = nullptr);
    ~CryptoManager();

    // Encrypt logic
    static QByteArray encrypt(const QByteArray &data, const QByteArray &key, const QByteArray &nonce);
    static QByteArray decrypt(const QByteArray &data, const QByteArray &key, const QByteArray &nonce);

    // Key generation
    static QByteArray generateRandom(int size);
    
    // Constant time comparison
    static bool constantTimeCompare(const QByteArray &a, const QByteArray &b);

private:
    bool initialized = false;
};

#endif // CRYPTOMANAGER_H
