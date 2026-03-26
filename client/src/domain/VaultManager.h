#ifndef VAULTMANAGER_H
#define VAULTMANAGER_H

#include <QObject>
#include <QString>
#include "../storage/DatabaseManager.h"
#include "../security/CryptoManager.h"
#include "../security/KeyDerivationService.h"

class VaultManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isLocked READ isLocked NOTIFY lockStatusChanged)

public:
    explicit VaultManager(QObject *parent = nullptr);

    Q_INVOKABLE bool createVault(const QString &path, const QString &masterPassword);
    Q_INVOKABLE bool openVault(const QString &path, const QString &masterPassword);
    Q_INVOKABLE void lockVault();

    bool isLocked() const;

signals:
    void lockStatusChanged();
    void vaultOpened();
    void vaultError(const QString &message);

private:
    DatabaseManager *m_dbManager;
    CryptoManager *m_cryptoManager;
    KeyDerivationService *m_kdfService;
};

#endif // VAULTMANAGER_H
