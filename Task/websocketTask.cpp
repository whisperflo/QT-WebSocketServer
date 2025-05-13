#include "websocketTask.h"

TaskWebSocket::TaskWebSocket(QObject *parent)
    : QObject(parent)
{
    service_.reset(new WebSocketService(this));
    ptr_wsWork_.reset(new WebsocketImpLayer(this));
    mutex_ = new QMutex();

    // 修正 lambda 表达式，使用 QString 类型作为路径参数
    service_->addPathHandler([this](const QString &path, QWebSocket *socket)
                             {
    qDebug() << "[TaskWebSocket] New connection on path:" << path;

    addConnectionHandler(path, socket); });

    service_->addDisconnectHandler([this](const QString &path, QWebSocket *socket)
                                   {
    qDebug() << "[TaskWebSocket] Disconnected socket from path:" << path;

    handleDisconnection(socket); });
}

TaskWebSocket::~TaskWebSocket()
{
    qDebug() << "[TaskWebSocket] Destructor";
    delete mutex_;
}

void TaskWebSocket::addConnectionHandler(const QString &path, QWebSocket *socket)
{

    // 加锁以确保线程安全
    QMutexLocker locker(mutex_);

    // 保存连接
    activeConnections_[path].append(socket);

    // 打印当前路径下的活跃连接数
    qDebug() << "[TaskWebSocket] New connection on path:" << path
             << "Active connections count:" << activeConnections_[path].size();

    // 创建定时器用于周期性推送数据
    QTimer *timer = new QTimer(this);
    timer->setInterval(2000); // 每 2 秒推送一次
    connect(timer, &QTimer::timeout, this, [this, path, socket]()
            {
        if (socket->state() != QAbstractSocket::ConnectedState)
            return;

        if (ptr_wsWork_) {
            std::string Path = path.toStdString();
            ptr_wsWork_->handlePath(Path);
        }

        QString message = QString("[TaskWebSocket] push data for path: %1").arg(path);
        socket->sendTextMessage(message);
        qDebug() << "[TaskWebSocket] Data pushed for path:" << path; });

    socketTimers_[socket] = timer;
    timer->start();
}

void TaskWebSocket::handleDisconnection(QWebSocket *socket)
{
    QMutexLocker locker(mutex_);

    // 移除所有路径下的该 socket
    for (auto &list : activeConnections_)
    {
        list.removeAll(socket);
    }

    // 停止并删除定时器
    if (socketTimers_.contains(socket))
    {
        QTimer *timer = socketTimers_.take(socket);
        if (timer)
        {
            timer->stop();
            timer->deleteLater();
        }
    }

    socket->deleteLater();

    // 打印当前活跃连接的数量
    for (auto it = activeConnections_.begin(); it != activeConnections_.end(); ++it)
    {
        qDebug() << "[TaskWebSocket] Active connections for path" << it.key() << ":" << it.value().size();
    }
    qDebug() << "[TaskWebSocket] Disconnected socket. Remaining connections:";
}
