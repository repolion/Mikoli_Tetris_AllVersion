#include "mysuperthread.h"

using namespace std;

namespace mikoli {

//  cherche l'@IP du serveur et le port et ouvre un serveur avec ce port
MySuperThread::MySuperThread (QObject* parent) : QThread (parent) {
    _port = calculPort();
    _server = new MyServer(_port);
    _server->startServer();
    _ip = calculIP();
}

MySuperThread::~MySuperThread() {}

void MySuperThread::run () {
    exec();
}

MyServer* MySuperThread::getServer () {
    return _server;
}

QString MySuperThread::getIP () {
    return _ip;
}

ushort MySuperThread::getPort () {
    return _port;
}

//  cherche l'IP par trois façon différentes, la première ayant un résultat empêche de passer aux autres
QString MySuperThread::calculIP() {
    QString ip;

    if (IPFromInternet(ip)) return ip;
    if (IPFromGateway(ip)) return ip;
    if (IPFromLoops(ip)) return ip;
}

//  calcul de l'IP quand on a une connexion à internet
bool MySuperThread::IPFromInternet (QString& ip) {
    bool found = false;

    QTcpSocket socket;
    socket.connectToHost("8.8.8.8", 53);
    found = socket.waitForConnected(100);

    if (found) {
        ip = socket.localAddress().toString();
    }

    socket.close();
    return found;
}

//  calcul de l'IP sans connexion à internet
bool MySuperThread::IPFromGateway (QString& ip) {
    bool found = false;

    QTcpSocket socket;
    int cpt = 0;

    while (!found && cpt <= 255) {
        QString buildIP = "192.168." + QString::number(cpt) + ".1";
        socket.connectToHost(buildIP, 53);

        if (socket.waitForConnected(100)) {
            found = true;
            ip = socket.localAddress().toString();
        }

        ++cpt;
    }

    socket.close();
    return found;
}

//  calcul de l'IP parmi toutes les possibilitées (lent)
bool MySuperThread::IPFromLoops (QString& ip) {
    bool found = false;

    QTcpSocket socket;
    int cpt1 = 0;
    int cpt2 = 1;

    while (!found && cpt1 <= 255) {
        while (!found && cpt2 <= 254) {
            QString buildIP = "192.168." + QString::number(cpt1) + "." + QString::number(cpt2);
            socket.connectToHost(buildIP, 53);

            if (socket.waitForConnected(100)) {
                found = true;
                ip = buildIP;
            }

            ++cpt2;
        }
        ++cpt1;
    }

    socket.close();
    return found;
}

//  trouve le premier port disponible
ushort MySuperThread::calculPort () {
    QTcpSocket socket;
    int port = 1024;

    while (port <= 65535) {
        socket.connectToHost("127.0.0.1", port);

        if (socket.waitForConnected(100)) {
            socket.close();
            ++port;
        } else {
            socket.close();
            return static_cast<ushort> (port);
        }
    }
}

}
