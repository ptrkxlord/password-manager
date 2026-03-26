#ifndef ENTRYSERVICE_H
#define ENTRYSERVICE_H

#include <QObject>
#include <QVariantList>
#include <QVariantMap>
#include "../storage/DatabaseManager.h"

class EntryService : public QObject
{
    Q_OBJECT
public:
    explicit EntryService(DatabaseManager *dbManager, QObject *parent = nullptr);

    Q_INVOKABLE QVariantList getAllEntries();
    Q_INVOKABLE bool addEntry(const QVariantMap &entry);
    Q_INVOKABLE bool updateEntry(const QString &id, const QVariantMap &entry);
    Q_INVOKABLE bool deleteEntry(const QString &id);

private:
    DatabaseManager *m_dbManager;
};

#endif // ENTRYSERVICE_H
