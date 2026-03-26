#include "DatabaseManager.h"
#include <QVariant>

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
}

DatabaseManager::~DatabaseManager()
{
    closeDatabase();
}

bool DatabaseManager::openDatabase(const QString &path, const QString &password)
{
    m_db.setDatabaseName(path);
    
    if (!m_db.open()) {
        return false;
    }

    // Apply SQLCipher password
    QSqlQuery query(m_db);
    query.prepare("PRAGMA key = :password");
    query.bindValue(":password", password);
    
    if (!query.exec()) {
        m_db.close();
        return false;
    }

    m_opened = true;
    return true;
}

void DatabaseManager::closeDatabase()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
    m_opened = false;
}

bool DatabaseManager::isOpened() const
{
    return m_opened;
}
