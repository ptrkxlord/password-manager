#include "AuthCallbackServer.h"
#include <QUrl>
#include <QUrlQuery>

AuthCallbackServer::AuthCallbackServer(QObject *parent)
    : QObject(parent), m_server(new QTcpServer(this))
{
    connect(m_server, &QTcpServer::newConnection, this, &AuthCallbackServer::onNewConnection);
}

bool AuthCallbackServer::startServer(quint16 port)
{
    if (m_server->isListening()) return true;
    return m_server->listen(QHostAddress::LocalHost, port);
}

void AuthCallbackServer::stopServer()
{
    m_server->close();
}

void AuthCallbackServer::onNewConnection()
{
    while (m_server->hasPendingConnections()) {
        QTcpSocket *socket = m_server->nextPendingConnection();
        connect(socket, &QTcpSocket::readyRead, this, &AuthCallbackServer::onReadyRead);
        connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    }
}

void AuthCallbackServer::onReadyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;

    QByteArray data = socket->readAll();
    QString request = QString::fromUtf8(data);

    // Simple HTTP Parsing
    if (request.startsWith("GET")) {
        QString line = request.split("\n").first();
        QString path = line.split(" ").at(1);
        QUrl url("http://localhost" + path);
        QUrlQuery query(url);

        if (query.hasQueryItem("token")) {
            QString token = query.queryItemValue("token");
            emit tokenReceived(token);

            // Send Success Response
            socket->write("HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\n\r\n");
            socket->write("<html><body style='background:#050505;color:white;font-family:sans-serif;display:flex;justify-content:center;align-items:center;height:100vh;'>");
            socket->write("<div><h1 style='color:#00f2ff'>Success!</h1><p>Authentication complete. You can close this tab now.</p></div>");
            socket->write("</body></html>");
            socket->disconnectFromHost();
        }
    }
}
