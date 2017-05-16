QT       += core
QT       += network
QT       -= gui

CONFIG += c++11

TARGET = Tetris_Server_Qt
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    myserver.cpp \
    mythread.cpp \
    gamemessage.cpp \
    deserializable.cpp \
    serializable.cpp \
    typemessage.cpp \
    gamemode.cpp

HEADERS += \
    myserver.h \
    mythread.h \
    gamemessage.h \
    typemessage.h \
    deserializable.h \
    serializable.h \
    gamemode.h
