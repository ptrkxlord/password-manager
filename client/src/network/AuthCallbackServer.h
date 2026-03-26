#ifndef AUTHCALLBACKSERVER_H
#define AUTHCALLBACKSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class AuthCallbackServer : public QObject
{
    Q_OBJECT
public:
    explicit AuthCallbackServer(QObject *parent = nullptr);
    
    Q_INVOKABLE bool startServer(quint16 port = 5050);
    Q_INVOKABLE void stopServer();

signals:
    void tokenReceived(QString token);

private slots:
    void onNewConnection();
    void onReadyRead();

private:
    QTcpServer *m_server;
};

#endif // AUTHCALLBACKSERVER_H
