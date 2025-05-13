#include <QCoreApplication>
#include "Schedule/websocketSchedule.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    TaskWebSchedule taskWebSchedule;

    return app.exec();
}