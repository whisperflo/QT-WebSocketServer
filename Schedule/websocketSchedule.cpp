#include "websocketSchedule.h"

TaskWebSchedule::TaskWebSchedule(QObject *parent)
    : QObject(parent)
{

    taskWebSocket.reset(new TaskWebSocket(this));
}
TaskWebSchedule::~TaskWebSchedule()
{
}
