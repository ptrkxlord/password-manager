#include "ApiClient.h"
#include <QNetworkRequest>
#include <QHttpMultiPart>

ApiClient::ApiClient(QObject *parent) : QObject(parent)
{
    m_networkManager = new QNetworkAccessManager(this);
}

void ApiClient::login(const QString &email, const QString &passwordHash)
{
    QUrl url(m_baseUrl + "/auth/login");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["email"] = email;
    json["passwordHash"] = passwordHash;

    QNetworkReply *reply = m_networkManager->post(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, [this, reply]() { onReplyFinished(reply); });
}

void ApiClient::registerUser(const QString &email, const QString &passwordHash)
{
    QUrl url(m_baseUrl + "/auth/register");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["email"] = email;
    json["passwordHash"] = passwordHash;

    QNetworkReply *reply = m_networkManager->post(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, [this, reply]() { onReplyFinished(reply); });
}

void ApiClient::setUserToken(const QString &token)
{
    m_token = token;
    emit loginSuccess(m_token);
}

void ApiClient::backupVault(const QString &deviceId, const QByteArray &blob)
{
    if (m_token.isEmpty()) return;

    QUrl url(m_baseUrl + "/vault/backup");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "Bearer " + m_token.toUtf8());

    QJsonObject json;
    json["deviceId"] = deviceId;
    json["blob"] = QString::fromLatin1(blob.toBase64());

    QNetworkReply *reply = m_networkManager->post(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            emit backupSuccess();
        } else {
            emit errorOccurred("Помилка бекапу: " + reply->errorString());
        }
        reply->deleteLater();
    });
}

void ApiClient::onReplyFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject obj = doc.object();
        
        if (obj.contains("access_token")) {
            m_token = obj["access_token"].toString();
            qDebug() << "Успішна авторизація. Токен отримано.";
            emit loginSuccess(m_token);
        } else {
            qDebug() << "Запит успішний.";
            emit backupSuccess(); 
        }
    } else {
        emit errorOccurred("Мережева помилка: " + reply->errorString());
    }
    reply->deleteLater();
}
