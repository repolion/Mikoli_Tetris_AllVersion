#ifndef MYTHREADSERVER_H
#define MYTHREADSERVER_H

#include <QThread>
#include <QTcpSocket>
#include <iostream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

#include "gamemessage.h"

namespace mikoli {

/*!
 * \brief The MyThreadServer class
 *  An instance of this class is a thread connected to a specific client.
 *  When the server receives a client, it creates an instance of this class to communicate with him.
 */
class MyThreadServer : public QThread{
    Q_OBJECT

public:

    /*!
     * \brief MyThreadServer
     * \param ID The socket descriptor of the client connected to this thread.
     * \param parent
     *  Default's constructor for a thread server.
     */
    explicit MyThreadServer(qintptr ID, QObject *parent = 0);

    /*!
     * \brief setId
     * \param id 1 if this thread is connected to the first client, 2 if it's the second.
     */
    void setId(int id);

    /*!
     * \brief run
     */
    void run();

    /*!
     * \brief closeSocket
     *  Close correctly the socket of this thread.
     */
    void closeSocket();

    /*!
     * \brief getSocket
     * \return  The socket of this thread.
     */
    QTcpSocket* getSocket();

signals:
    void error(QTcpSocket::SocketError socketerror);
    void sendToServer(GameMessage message,int id);

public slots:

    /*!
     * \brief readyRead
     *  This slot handles a message received on the socket.
     */
    void readyRead();

    /*!
     * \brief disconnected
     *  This slot handles a deconnexion of the socket.
     */
    void disconnected();

    /*!
     * \brief messageToAllClient
     * \param message The message to send to the two clients.
     *  This slots send a message to the two clients.
     */
    void messageToAllClient(GameMessage message);

    /*!
     * \brief sendToClientOne
     * \param message The message to send
     */
    void sendToClientOne(GameMessage message);

    /*!
     * \brief sendToClientTwo
     * \param message The message to send
     */
    void sendToClientTwo(GameMessage message);
private:
    QTcpSocket *_socket;
    qintptr _socketDescriptor;
    int _id;
};

}

#endif // MYTHREADSERVER_H
