#pragma once
#include <QObject>
#include "Common/DataStructure.h"
#include "webSocketService.h"
class WebsocketImpLayer : public QObject
{

    Q_OBJECT
public:
    WebsocketImpLayer(QObject *parent = nullptr);
    ~WebsocketImpLayer();
    // 根据路径类型处理对应的功能
    void handlePath(const std::string &path);

private:
    // 将字符串转换为枚举类型
    PathType getPathType(const std::string &path);
    QScopedPointer<WebSocketService> web_service;
};