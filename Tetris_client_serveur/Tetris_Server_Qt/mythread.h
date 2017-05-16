#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include "gamemessage.h"

namespace mikoli {

class MyThread : public QThread{
    Q_OBJECT
public:
    explicit MyThread(qintptr ID, QObject *parent = 0);
    void setId(int id);
    void run();
    void closeSocket();

signals:
    void error(QTcpSocket::SocketError socketerror);
    void sendToServer(GameMessage, int id);

public slots:
    void readyRead();
    void disconnected();
    void messageToAllClient(GameMessage);
    void sendToClientOne(GameMessage);
    void sendToClientTwo(GameMessage);
private:
    QTcpSocket *_socket;
    qintptr _socketDescriptor;
    int _id;
};

}

#endif // MYTHREAD_H
