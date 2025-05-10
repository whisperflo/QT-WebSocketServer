#pragma once

#include <QObject>
#include <QList>
#include <QDebug>
#include <QWebSocketServer>
#include <QWebSocket>

class EchoServer : public QObject
{
    Q_OBJECT

public:
    explicit EchoServer(QObject *parent = nullptr);
    ~EchoServer();

private slots:
    void onNewConnection();
    void processTextMessage(const QString &message);
    void socketDisconnected();

private:
    QWebSocketServer *m_pWebsocketServer;
    QList<QWebSocket *> m_clients;
};
