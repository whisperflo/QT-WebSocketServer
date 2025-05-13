#ifndef WEBSOCKETSERVICE_H
#define WEBSOCKETSERVICE_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QMap>
#include <QSet>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>
#include <functional>
#include <QString>
#include <QUrl>

class WebSocketService : public QObject
{
    Q_OBJECT

public:
    explicit WebSocketService(QObject *parent = nullptr);
    ~WebSocketService();

    // 向指定路径的所有连接发送消息
    void send(const QString &path, const QString &message);

    // 添加路径连接的处理函数，处理新连接时的操作
    void addPathHandler(std::function<void(const QString &, QWebSocket *)> handler);

    // 添加断开连接时的处理函数
    void addDisconnectHandler(std::function<void(const QString &, QWebSocket *)> handler);

private slots:
    // 处理新的 WebSocket 连接
    void onNewConnection();

    // 处理 WebSocket 连接断开
    void onDisconnected();

private:
    // 提取 URL 中的路径
    QString extractPath(const QUrl &url);

    // WebSocket 服务器实例
    QWebSocketServer *m_server;

    // 存储按路径分类的 WebSocket 连接集合
    QMap<QString, QSet<QWebSocket *>> m_connections;

    // 存储 WebSocket 到路径的映射
    QMap<QWebSocket *, QString> m_socketPathMap;

    // 存储路径连接的处理函数列表
    QList<std::function<void(const QString &, QWebSocket *)>> pathHandlers;

    // 存储断开连接的处理函数列表
    QList<std::function<void(const QString &, QWebSocket *)>> disconnectHandlers;

    // 服务器监听的端口
    quint16 port = 9002;
};

#endif // WEBSOCKETSERVICE_H
