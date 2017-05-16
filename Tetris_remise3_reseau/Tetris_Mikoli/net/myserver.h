#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <utility>
#include <iostream>

#include "mythreadserver.h"

namespace mikoli {

class MyServer : public QTcpServer{
    Q_OBJECT
public:
    /*!
     * \brief MyServer constructor
     * \param ushort the port to create the TcpServerSocket
     */
    explicit MyServer(ushort, QObject *parent = 0);

    /*!
     * \brief  to start the server
     */
    void startServer();

    /*!
     * \brief isWaiting to know if the server is waiting for a second player
     */
    bool isWaiting();

    /*!
     * \brief to set the game mode value of the Server
     */
    void setMode(Gamemode);

signals:
    /*!
     * \brief sendToAllTread send a message to all the client connected
     * \param message the message to send
     */
    void sendToAllTread(GameMessage message);

    /*!
     * \brief sendToClientOne send a message to the client 1
     * \param message the message to send
     */
    void sendToClientOne(GameMessage message);

    /*!
     * \brief sendToClientTwo send a message to the client 2
     * \param message the message to send
     */
    void sendToClientTwo(GameMessage message);

public slots:
    void receivingFromThread(GameMessage message,int id);

protected:
    void incomingConnection(qintptr socketDescriptor);

private:
    void closeSockets();

    bool _waiting = false;
    bool _busy = false;
    std::pair<mikoli::MyThreadServer*,mikoli::MyThreadServer*> _pairThread;
    Gamemode _gameMode;
    int _goal;
    ushort _port;

};

}

#endif // MYSERVER_H
