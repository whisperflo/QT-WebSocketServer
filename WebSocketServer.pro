QT += core websockets network
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app
TARGET = WebSocketServer

INCLUDEPATH += $$PWD/Common
INCLUDEPATH += $$PWD/Schedule
INCLUDEPATH += $$PWD/Service
INCLUDEPATH += $$PWD/Task
INCLUDEPATH += $$PWD/WorkLayer

SOURCES += \
    main.cpp \
    Schedule/websocketSchedule.cpp \
    Service/webSocketService.cpp \
    Task/websocketTask.cpp \
    WorkLayer/websocketImpLayer.cpp

HEADERS += \
    Common/DataStructure.h \
    Schedule/websocketSchedule.h \
    Service/webSocketService.h \
    Task/websocketTask.h \
    WorkLayer/websocketImpLayer.h
