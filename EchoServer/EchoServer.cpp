#include "EchoServer.h"

EchoServer::EchoServer(QObject *parent)
    : QObject(parent),
      // 创建一个名字叫 "Echo Server" 的非加密 WebSocket 服务端，并将它作为当前 EchoServer 对象的子对象，
      // 同时将其指针保存在 m_pWebsocketServer 中以备后续使用（如监听端口、接收连接等）
      m_pWebsocketServer(new QWebSocketServer(QStringLiteral("Echo Server"),
                                              QWebSocketServer::NonSecureMode, this))
{
    // 监听端口固定为9002
    const quint16 port = 9002;
    if (m_pWebsocketServer->listen(QHostAddress::Any, port))
    {
        qDebug() << "WebSocket Sever started on port" << port;
        connect(m_pWebsocketServer, &QWebSocketServer::newConnection, this, &EchoServer::onNewConnection);
    }
    else
    {
        qDebug() << "Failed to start Websocket server on port" << port;
    }
}

EchoServer::~EchoServer()
{
    m_pWebsocketServer->close();
    qDeleteAll(m_clients);
}

void EchoServer::onNewConnection()
{
    // 返回一个新的客户端连接的 QWebSocket* 对象
    QWebSocket *pSocket = m_pWebsocketServer->nextPendingConnection();
    connect(pSocket, &QWebSocket::textMessageReceived, this, &EchoServer::processTextMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &EchoServer::socketDisconnected);
    m_clients << pSocket; // 等同于 m_clients.append(pSocket);
    // 获取与当前 WebSocket 连接对应的客户端 IP 地址
    qDebug() << "New connection connected:" << pSocket->peerAddress().toString();
}

void EchoServer::processTextMessage(const QString &message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient)
    {
        qDebug() << "Received message:" << message;
        pClient->sendTextMessage("Echo:" + message); // Echo the message back to the client
    }
}

void EchoServer::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient)
    {
        qDebug() << "Client disconnected:" << pClient->peerAddress().toString();
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}