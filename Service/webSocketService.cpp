#include "webSocketService.h"

WebSocketService::WebSocketService(QObject *parent)
    : QObject(parent),
      m_server(new QWebSocketServer(QStringLiteral("WebSocket Server"),
                                    QWebSocketServer::NonSecureMode, this))
{
    // 尝试启动 WebSocket 服务器并监听指定端口
    if (m_server->listen(QHostAddress::Any, port))
    {
        // 如果成功，连接新连接事件到处理函数
        connect(m_server, &QWebSocketServer::newConnection, this, &WebSocketService::onNewConnection);
        qDebug() << "Listening on port" << port;
    }
    else
    {
        // 启动失败时的警告输出
        qWarning() << "Failed to listen on port" << port;
    }
}

WebSocketService::~WebSocketService()
{
    // 关闭服务器
    m_server->close();

    // 遍历所有 socket 连接并删除
    for (auto &set : m_connections)
    {
        for (QWebSocket *socket : set)
        {
            if (socket)
            {
                socket->deleteLater();
            }
        }
    }

    // 清空所有连接和路径映射
    m_connections.clear();
    m_socketPathMap.clear();

    // 删除服务器对象
    delete m_server;
}

void WebSocketService::onNewConnection()
{
    // 获取新连接的 WebSocket 实例
    QWebSocket *socket = m_server->nextPendingConnection();
    if (!socket)
        return;

    // 连接断开事件到处理函数
    connect(socket, &QWebSocket::disconnected, this, &WebSocketService::onDisconnected);

    // 提取连接路径并将该 socket 存储到对应的路径集合中
    QString path = extractPath(socket->requestUrl());
    m_connections[path].insert(socket);
    qDebug() << "m_connections size:" << m_connections.size();
    m_socketPathMap[socket] = path;
    qDebug() << "m_socketPathMap size:" << m_socketPathMap.size();

    // 执行所有路径相关的处理函数
    for (auto &handler : pathHandlers)
        handler(path, socket);
}

void WebSocketService::onDisconnected()
{
    // 获取断开连接的 WebSocket 实例
    QWebSocket *socket = qobject_cast<QWebSocket *>(sender());
    if (!socket)
        return;

    // 如果 socket 存在于路径映射中，则处理相关的断开操作
    if (m_socketPathMap.contains(socket))
    {
        QString path = m_socketPathMap.value(socket);

        // 从路径集合中移除该 socket
        if (m_connections.contains(path))
        {
            m_connections[path].remove(socket);
            if (m_connections[path].isEmpty())
            {
                m_connections.remove(path); // 如果该路径下没有更多连接，移除路径
            }
        }

        // 移除路径映射
        m_socketPathMap.remove(socket);

        // 执行所有断开连接的处理函数
        for (auto &handler : disconnectHandlers)
        {
            handler(path, socket);
        }
    }

    // 输出当前的连接数和路径映射数
    qDebug() << "m_connections size:" << m_connections.size();
    qDebug() << "m_socketPathMap size:" << m_socketPathMap.size();

    // 安全删除该 socket 对象
    socket->deleteLater();
}

void WebSocketService::send(const QString &path, const QString &message)
{
    // 获取指定路径下的所有连接
    auto connections = m_connections.value(path);
    for (auto *socket : connections)
    {
        // 如果 socket 处于连接状态，则发送消息
        if (socket->state() == QAbstractSocket::ConnectedState)
            socket->sendTextMessage(message);
    }
}

void WebSocketService::addPathHandler(std::function<void(const QString &, QWebSocket *)> handler)
{
    // 添加处理路径连接的回调函数
    pathHandlers.append(handler);
}

void WebSocketService::addDisconnectHandler(std::function<void(const QString &, QWebSocket *)> handler)
{
    // 添加断开连接时的回调函数
    disconnectHandlers.append(handler);
}

QString WebSocketService::extractPath(const QUrl &url)
{
    // 提取 URL 中的路径，如果为空则返回 "/"
    return url.path().isEmpty() ? "/" : url.path();
}
