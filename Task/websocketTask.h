#pragma once

#include <QObject>
#include <QMap>
#include <QDebug>
#include <QMutex>
#include <QMutexLocker>
#include <QPointer>
#include <QScopedPointer>
#include <QWebSocket>
#include <QString>
#include <QTimer>

#include "webSocketService.h"
#include "websocketImpLayer.h"

class TaskWebSocket : public QObject
{
    Q_OBJECT
public:
    explicit TaskWebSocket(QObject *parent = nullptr);
    ~TaskWebSocket();

private:
    void handleDisconnection(QWebSocket *socket);
    void addConnectionHandler(const QString &path, QWebSocket *socket);

private:
    QScopedPointer<WebSocketService> service_;
    QScopedPointer<WebsocketImpLayer> ptr_wsWork_;

    // 当前活跃的 WebSocket 连接，按路径分组
    QMap<QString, QList<QPointer<QWebSocket>>> activeConnections_;

    // 每个连接对应的定时器
    QMap<QWebSocket *, QTimer *> socketTimers_;

    // 用于保护上面两个成员的并发访问
    QMutex *mutex_;
};
