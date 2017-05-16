#-------------------------------------------------
#
# Project created by QtCreator 2017-02-23T19:09:11
#
#-------------------------------------------------

QT       += core gui \
            multimedia

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DEVIR4_CPPL_Tetris_Mike_Olivier
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    position.cpp \
    block.cpp \
    figure.cpp \
    board.cpp \
    score.cpp \
    figuresbag.cpp \
    tetrisgame.cpp \
    observable.cpp \
    observer.cpp \
    viewboard.cpp \
    widget.cpp \
    sideboard.cpp \
    soundplayer.cpp \
    buttons.cpp \
    mode.cpp \
    timer.cpp \
    choiceboard.cpp \
    threadServer/deserializable.cpp \
    threadServer/gamemessage.cpp \
    threadServer/mythread.cpp \
    threadServer/serializable.cpp \
    threadServer/typemessage.cpp \
    gamemode.cpp \
    observerwidget.cpp \
    observablewidget.cpp \
    ipdialog.cpp

HEADERS  += \
    position.h \
    block.h \
    typeshape.h \
    figure.h \
    color.h \
    direction.h \
    board.h \
    score.h \
    figuresbag.h \
    tetrisgame.h \
    mode.h \
    tetrisexception.h \
    observable.h \
    observer.h \
    viewboard.h \
    ui_widget.h \
    widget.h \
    sideboard.h \
    soundplayer.h \
    buttons.h \
    gamemode.h \
    timer.h \
    choiceboard.h \
    threadServer/deserializable.h \
    threadServer/gamemessage.h \
    threadServer/mythread.h \
    threadServer/serializable.h \
    threadServer/typemessage.h \
    observerwidget.h \
    observablewidget.h \
    ipdialog.h

FORMS    += \
    widget.ui

RESOURCES += \
    res.qrc
