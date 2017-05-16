#-------------------------------------------------
#
# Project created by QtCreator 2017-02-23T19:09:11
#
#-------------------------------------------------

#QT       += core gui \
#            multimedia \
#            network

QT  += core
QT  += network
QT  += multimedia
QT  -= gui

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
    widget.cpp \
    model/block.cpp \
    model/board.cpp \
    model/figure.cpp \
    model/figuresbag.cpp \
    model/gamemode.cpp \
    model/mode.cpp \
    model/position.cpp \
    model/score.cpp \
    model/tetrisgame.cpp \
    model/timer.cpp \
    net/deserializable.cpp \
    net/gamemessage.cpp \
    net/myserver.cpp \
    net/mysuperthread.cpp \
    net/mythreadClient.cpp \
    net/mythreadserver.cpp \
    net/serializable.cpp \
    net/typemessage.cpp \
    observer/observable.cpp \
    observer/observablewidget.cpp \
    observer/observer.cpp \
    observer/observerwidget.cpp \
    sounds/soundplayer.cpp \
    view/buttons.cpp \
    view/choiceboard.cpp \
    view/ipdialog.cpp \
    view/sideboard.cpp \
    view/viewboard.cpp

HEADERS  += \
    ui_widget.h \
    widget.h \
    model/block.h \
    model/board.h \
    model/color.h \
    model/direction.h \
    model/figure.h \
    model/figuresbag.h \
    model/gamemode.h \
    model/mode.h \
    model/position.h \
    model/score.h \
    model/tetrisexception.h \
    model/tetrisgame.h \
    model/timer.h \
    model/typeshape.h \
    net/deserializable.h \
    net/gamemessage.h \
    net/myserver.h \
    net/mysuperthread.h \
    net/mythreadClient.h \
    net/mythreadserver.h \
    net/serializable.h \
    net/typemessage.h \
    observer/observable.h \
    observer/observablewidget.h \
    observer/observer.h \
    observer/observerwidget.h \
    sounds/soundplayer.h \
    view/buttons.h \
    view/choiceboard.h \
    view/ipdialog.h \
    view/sideboard.h \
    view/viewboard.h

FORMS    += \
    widget.ui

RESOURCES += \
    res.qrc

DISTFILES += \
    image/background.png
