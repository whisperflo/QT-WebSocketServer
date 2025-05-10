QT += core websockets
CONFIG += console c++11
TARGET = EchoServer
TEMPLATE = app

SOURCES += main.cpp \
           EchoServer.cpp

HEADERS += EchoServer.h

