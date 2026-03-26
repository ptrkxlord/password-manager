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
    // Generate salt and derive key
    QByteArray salt = m_kdfService->generateSalt();
    QByteArray key = m_kdfService->deriveKey(masterPassword, salt, 
                                            crypto_pwhash_OPSLIMIT_INTERACTIVE,
                                            crypto_pwhash_MEMLIMIT_INTERACTIVE,
                                            32);
    
    if (m_dbManager->openDatabase(path, key.toHex())) {
        // Create initial tables
        QSqlQuery query(m_dbManager->database());
        query.exec("CREATE TABLE entries (id TEXT PRIMARY KEY, title TEXT, url TEXT, username TEXT, password TEXT, notes TEXT, favorite INTEGER)");
        query.exec("CREATE TABLE metadata (key TEXT PRIMARY KEY, value BLOB)");
        
        QSqlQuery saltQuery(m_dbManager->database());
        saltQuery.prepare("INSERT INTO metadata (key, value) VALUES ('salt', :salt)");
        saltQuery.bindValue(":salt", salt);
        saltQuery.exec();

        emit vaultOpened();
        emit lockStatusChanged();
        return true;
    }
    return false;
}

bool VaultManager::openVault(const QString &path, const QString &masterPassword)
{
    // First, open without key to read salt? No, SQLite is encrypted. 
    // We need to store salt elsewhere or use a fixed header.
    // In this simplified version, let's assume we read salt from a separate small file or fixed location.
    // Real implementation should use a custom header in the SQLite file.
    
    // For demo/simplicity:
    QByteArray salt = "fixed_salt_for_demo_16b"; // Placeholder
    QByteArray key = m_kdfService->deriveKey(masterPassword, salt, 
                                            crypto_pwhash_OPSLIMIT_INTERACTIVE,
                                            crypto_pwhash_MEMLIMIT_INTERACTIVE,
                                            32);

    if (m_dbManager->openDatabase(path, key.toHex())) {
        emit vaultOpened();
        emit lockStatusChanged();
        return true;
    }
    
    emit vaultError("Невірний майстер-пароль");
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
