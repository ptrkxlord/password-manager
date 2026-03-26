#include "EntryService.h"
#include <QUuid>

EntryService::EntryService(DatabaseManager *dbManager, QObject *parent) 
    : QObject(parent), m_dbManager(dbManager) {}

QVariantList EntryService::getAllEntries()
{
    QVariantList list;
    if (!m_dbManager->isOpened()) return list;

    QSqlQuery query("SELECT * FROM entries", m_dbManager->database());
    while (query.next()) {
        QVariantMap map;
        map["id"] = query.value("id");
        map["title"] = query.value("title");
        map["username"] = query.value("username");
        map["password"] = query.value("password");
        list.append(map);
    }
    return list;
}

bool EntryService::addEntry(const QVariantMap &entry)
{
    if (!m_dbManager->isOpened()) return false;

    QSqlQuery query(m_dbManager->database());
    query.prepare("INSERT INTO entries (id, title, url, username, password, notes, favorite) "
                  "VALUES (:id, :title, :url, :username, :password, :notes, :favorite)");
    query.bindValue(":id", QUuid::createUuid().toString());
    query.bindValue(":title", entry["title"]);
    query.bindValue(":url", entry["url"]);
    query.bindValue(":username", entry["username"]);
    query.bindValue(":password", entry["password"]);
    query.bindValue(":notes", entry["notes"]);
    query.bindValue(":favorite", entry["favorite"].toInt());

    return query.exec();
}

bool EntryService::updateEntry(const QString &id, const QVariantMap &entry)
{
    if (!m_dbManager->isOpened()) return false;

    QSqlQuery query(m_dbManager->database());
    query.prepare("UPDATE entries SET title=:title, url=:url, username=:username, password=:password, notes=:notes, favorite=:favorite WHERE id=:id");
    query.bindValue(":id", id);
    query.bindValue(":title", entry["title"]);
    query.bindValue(":url", entry["url"]);
    query.bindValue(":username", entry["username"]);
    query.bindValue(":password", entry["password"]);
    query.bindValue(":notes", entry["notes"]);
    query.bindValue(":favorite", entry["favorite"].toInt());

    return query.exec();
}

bool EntryService::deleteEntry(const QString &id)
{
    if (!m_dbManager->isOpened()) return false;

    QSqlQuery query(m_dbManager->database());
    query.prepare("DELETE FROM entries WHERE id=:id");
    query.bindValue(":id", id);
    return query.exec();
}
