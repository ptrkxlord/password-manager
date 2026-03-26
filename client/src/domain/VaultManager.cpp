#include "VaultManager.h"
#include <QFile>

VaultManager::VaultManager(QObject *parent) : QObject(parent)
{
    m_dbManager = new DatabaseManager(this);
    m_cryptoManager = new CryptoManager(this);
    m_kdfService = new KeyDerivationService(this);
}

bool VaultManager::createVault(const QString &path, const QString &masterPassword)
{
    QByteArray salt = m_kdfService->generateSalt();
    
    // Save salt to companion file .salt
    QFile saltFile(path + ".salt");
    if (saltFile.open(QIODevice::WriteOnly)) {
        saltFile.write(salt);
        saltFile.close();
    } else {
        emit vaultError("Не вдалося створити файл солі");
        return false;
    }

    QByteArray key = m_kdfService->deriveKey(masterPassword, salt, 
                                            crypto_pwhash_OPSLIMIT_INTERACTIVE,
                                            crypto_pwhash_MEMLIMIT_INTERACTIVE,
                                            32);
    
    if (m_dbManager->openDatabase(path, key.toHex())) {
        QSqlQuery query(m_dbManager->database());
        query.exec("CREATE TABLE entries (id TEXT PRIMARY KEY, title TEXT, url TEXT, username TEXT, password TEXT, notes TEXT, favorite INTEGER)");
        
        emit vaultOpened();
        emit lockStatusChanged();
        return true;
    }
    return false;
}

bool VaultManager::openVault(const QString &path, const QString &masterPassword)
{
    QByteArray salt;
    QFile saltFile(path + ".salt");
    if (saltFile.open(QIODevice::ReadOnly)) {
        salt = saltFile.readAll();
        saltFile.close();
    } else {
        emit vaultError("Файл солі не знайдено");
        return false;
    }

    QByteArray key = m_kdfService->deriveKey(masterPassword, salt, 
                                            crypto_pwhash_OPSLIMIT_INTERACTIVE,
                                            crypto_pwhash_MEMLIMIT_INTERACTIVE,
                                            32);

    if (m_dbManager->openDatabase(path, key.toHex())) {
        emit vaultOpened();
        emit lockStatusChanged();
        return true;
    }
    
    emit vaultError("Невірний майстер-пароль або пошкоджено файл");
    return false;
}

void VaultManager::lockVault()
{
    m_dbManager->closeDatabase();
    emit lockStatusChanged();
}

bool VaultManager::isLocked() const
{
    return !m_dbManager->isOpened();
}
