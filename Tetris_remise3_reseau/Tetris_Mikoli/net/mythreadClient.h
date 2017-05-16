#ifndef MYTHREADCLIENT_H
#define MYTHREADCLIENT_H

#include <QThread>
#include <QTcpSocket>
#include <QtNetwork>
#include <iostream>
#include <QJsonDocument>
#include <QDebug>

#include "model/tetrisgame.h"
#include "view/sideboard.h"
#include "view/choiceboard.h"

namespace mikoli {

class MyThreadClient : public QThread {
    Q_OBJECT
public:
    /*!
     * \brief MyThreadClient
     * \param TetrisGame the game
     * \param SideBoard the sideboard
     * \param ChoiceBoard the choiceboard
     * \param int the port to connect to host
     * \param QString the IP adress to connect to host
     * \param parent
     */
    MyThreadClient(TetrisGame *,SideBoard*,ChoiceBoard*,int,QString, QObject *parent = 0);
    /*!
     * \brief MyThreadClient
     * \param TetrisGame the game
     * \param SideBoard the sideboard
     * \param ChoiceBoard the choiceboard
     * \param GameMode the game mode
     * \param int the value of the goal to reach to
     * \param int the port to connect to host
     * \param QString the IP adress to connect to host
     * \param parent
     */
    MyThreadClient(TetrisGame *,SideBoard*,ChoiceBoard*,Gamemode,int,int,QString, QObject *parent = 0);

    /*!
     * \brief run to run the Qthread
     */
    void run();

    /*!
     * \brief sendMessage to send a Game message to the server
     * \param message the message to send to the server
     */
    void sendMessage(GameMessage message);

    /*!
     * \brief handleQuit to handle the end of a multiplayer game
     * when receiving a message QUIT from the server
     */
    void handleQuit();

    /*!
     * \brief getSocket to get the socket
     * \return the socket
     */
    QTcpSocket * getSocket();

    /*!
     * \brief setIsConnected to set the value isConnected
     * \param b the bool value to set
     */
    void setIsConnected(bool b);

    /*!
     * \brief getIsConnected to get the isConnected value
     * \return isConnected value
     */
    bool getIsConnected();

public slots:
    /*!
     * \brief readyRead called when a message is received
     */
    void readyRead();

    /*!
     * \brief disconnected called by signal emition disconnected
     */
    void disconnected();
signals:
    /*!
     * \brief endThread emit when thread close
     */
    void endThread();

    /*!
     * \brief infoServerStatus emit to inform that infoServerStatus changed;
     * server mode can be on or off
     */
    void infoServerStatus();

private:
    TetrisGame * _game;
    SideBoard * _sideBoard;
    ChoiceBoard * _choiceBoard;
    QTcpSocket * _socket;
    bool _isConnected;
};

}

#endif // MYTHREADCLIENT_H
