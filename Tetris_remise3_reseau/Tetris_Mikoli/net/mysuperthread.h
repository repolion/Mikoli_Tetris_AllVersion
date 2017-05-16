#ifndef MYSUPERTHREAD_H
#define MYSUPERTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <iostream>

#include "myserver.h"

namespace mikoli {

/*!
 * \brief MySuperThread class is a Thread
 * created for the Server
 */
class MySuperThread : public QThread {
    Q_OBJECT

public:
    /*!
     * \brief MySuperThread constructor
     */
    explicit MySuperThread (QObject* parent = 0);

    /*!
     * \brief MySuperThread destructor
     */
    ~MySuperThread();

    /*!
     * \brief to run the Thread Server
     */
    void run();

    /*!
     * \brief to get the Server
     */
    MyServer* getServer();

    /*!
     * \brief getIP to get the IP from the server
     * \return an IP adress
     */
    QString getIP();

    /*!
     * \brief getPort to get the port from the server
     * \return a port
     */
    ushort getPort();

    /*!
     * \brief calculIP to find the local ip of the server
     * \return an IP adress
     */
    QString calculIP ();

    /*!
     * \brief return true if the local ip is found
     * \param QString this value is initialized vy the method
     * \return if the ip is found or not
     */
    bool IPFromInternet (QString&);

    /*!
     * \brief return true if the local ip is found
     * \param QString this value is initialized vy the method
     * \return if the ip is found or not
     */
    bool IPFromGateway (QString&);

    /*!
     * \brief return true if the local ip is found
     * \param QString this value is initialized vy the method
     * \return if the ip is found or not
     */
    bool IPFromLoops (QString&);

    /*!
     * \brief to find the first available port that will
     * be used by the server fot his socket
     * \return the first port available
     */
    ushort calculPort();

private:
    MyServer* _server;
    QString _ip;
    ushort _port;
};

}

#endif // MYSUPERTHREAD_H
