#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    bool openDatabase(const QString &path, const QString &password);
    void closeDatabase();
    bool isOpened() const;

    QSqlDatabase& database() { return m_db; }

private:
    QSqlDatabase m_db;
    bool m_opened = false;
};

#endif // DATABASEMANAGER_H
