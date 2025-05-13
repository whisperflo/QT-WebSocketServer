#pragma once
#include <QObject>
#include <QScopedPointer>
#include "websocketTask.h"

class TaskWebSchedule : public QObject
{
    Q_OBJECT

public:
    explicit TaskWebSchedule(QObject *parent = nullptr);
    ~TaskWebSchedule();

private:
    QScopedPointer<TaskWebSocket> taskWebSocket;
};
