#ifndef APICLIENT_H
#define APICLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

class ApiClient : public QObject
{
    Q_OBJECT
public:
    explicit ApiClient(QObject *parent = nullptr);

    Q_INVOKABLE void login(const QString &email, const QString &passwordHash);
    Q_INVOKABLE void registerUser(const QString &email, const QString &passwordHash);
    Q_INVOKABLE void backupVault(const QString &deviceId, const QByteArray &blob);

signals:
    void loginSuccess(const QString &token);
    void errorOccurred(const QString &message);
    void backupSuccess();

private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_networkManager;
    QString m_token;
    QString m_baseUrl = "http://localhost:3000";
};

#endif // APICLIENT_H
