#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QtNetwork>
#include "gamemessage.h"
#include "tetrisgame.h"
#include "sideboard.h"
#include "choiceboard.h"

namespace mikoli {

class MyThread : public QThread {
    Q_OBJECT
public:
    MyThread(TetrisGame *,SideBoard*,ChoiceBoard*,int,QString, QObject *parent = 0);
    MyThread(TetrisGame *,SideBoard*,ChoiceBoard*,Gamemode,int,int,QString, QObject *parent = 0);

    void run();
    void sendMessage(GameMessage message);
    void handleQuit();
    QTcpSocket * getSocket();
    void setIsConnected(bool b);
    bool getIsConnected();

public slots:
    void readyRead();
    void disconnected();
signals:
    void endThread();

private:
    TetrisGame * _game;
    SideBoard * _sideBoard;
    ChoiceBoard * _choiceBoard;
    QTcpSocket * _socket;
    bool _isConnected;
};

}

#endif // MYTHREAD_H
