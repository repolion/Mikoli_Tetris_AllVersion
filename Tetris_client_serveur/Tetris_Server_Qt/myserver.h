#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <utility>
#include "mythread.h"
#include "gamemessage.h"
#include "mythread.h"

namespace mikoli {

/*!
 * \brief The MyServer is used to manage the connection
 * and exchange of information between the clients
 */
class MyServer : public QTcpServer{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);

    /*!
     * \brief to start the server listening to all
     * on a certain port. 1024 by default
     */
    void startServer();
    bool isWaiting();
signals:
    void sendToAllTread(GameMessage);
    void sendToClientOne(GameMessage);
    void sendToClientTwo(GameMessage);

public slots:
    void receivingFromThread(GameMessage,int id);

protected:
    void incomingConnection(qintptr socketDescriptor);

private:
    bool _waiting = false;
    bool _busy = false;
    std::pair<MyThread*,MyThread*> _pairThread;
    Gamemode _gameMode;
    int _goal;

};

}

#endif // MYSERVER_H
