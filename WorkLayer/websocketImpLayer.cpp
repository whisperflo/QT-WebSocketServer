#include "websocketImpLayer.h"

WebsocketImpLayer::WebsocketImpLayer(QObject *parent)
    : QObject(parent)
{
    web_service.reset(new WebSocketService(this));
}
WebsocketImpLayer::~WebsocketImpLayer()
{
}

// 将字符串转换为枚举类型
PathType WebsocketImpLayer::getPathType(const std::string &path)
{
    //  路径/pcs/systemState   、/pcs/dataAcquisition
    if (path.find("/pcs/systemState/") != std::string::npos)
    {
        return PathType::PCSSTATUS;
    }
    // pcs数据获取
    else if (path.find("/pcs/dataAcquisition/") != std::string::npos)
    {
        return PathType::PCSDATA;
    }
    else if (path == "/bmsStatus")
    {
        return PathType::BMSSTATUS;
    }
    else if (path == "/runInfo/systemStatus")
    {
        return PathType::SYSTEMINFORMATION;
    }
    else if (path == "/runInfo/energyFlow")
    {
        return PathType::ENERYFLOWDATA;
    }
    else
    {
        return PathType::UNKNOWNPATH;
    }
}

void WebsocketImpLayer::handlePath(const std::string &path)
{
    PathType pathType = getPathType(path);
    switch (pathType)
    {
    case PathType::PCSSTATUS:
        qDebug() << "处理路径类型::PCSSTATUS";
        web_service->send(QString::fromStdString(path), "处理路径类型::PCSSTATUS");
        break;
    case PathType::PCSDATA:
        qDebug() << "处理路径类型::PCSDATA";
        web_service->send(QString::fromStdString(path), "处理路径类型::PCSSTATUS");

        break;
    case PathType::BMSSTATUS:
        qDebug() << "处理路径类型::BMSSTATUS";
        web_service->send(QString::fromStdString(path), "处理路径类型::PCSSTATUS");
        break;
    case PathType::SYSTEMINFORMATION:
        qDebug() << "处理路径类型::SYSTEMINFORMATION";
        web_service->send(QString::fromStdString(path), "处理路径类型::PCSSTATUS");

        break;
    case PathType::ENERYFLOWDATA:
        qDebug() << "处理路径类型::ENERYFLOWDATA";
        web_service->send(QString::fromStdString(path), "处理路径类型::PCSSTATUS");
        break;
    default:
        qDebug() << "未知路径类型";
        break;
    }
}