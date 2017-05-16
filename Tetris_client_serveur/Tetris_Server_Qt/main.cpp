#include <QCoreApplication>
#include "myserver.h"
#include <iostream>

using namespace mikoli;

int main(int argc, char *argv[]){

    QCoreApplication a(argc, argv);

    MyServer server;
    server.startServer();

    QTcpSocket socket;
    bool found = false;
    int cpt = 0;
    while(!found && cpt <= 255){
        int cpt2 = 1;
        while (!found && cpt2<=254){
            QString ip = "192.168."+QString::number(cpt)+"."+QString::number(cpt2);
            std::cout<<ip.toStdString()<<std::endl;
            socket.connectToHost(ip, 53); // google DNS, or something else reliable
            if (socket.waitForConnected(100)) {
                qDebug()
                        << "local IPv4 address for Internet connectivity is"
                        << socket.localAddress().toString();
                found=true;
            }
            ++cpt2;
        }
        ++cpt;
    }

    return a.exec();
}

//while(!found && cpt <= 255){
//    QString ip = "192.168."+QString::number(cpt)+".1";
//    socket.connectToHost(ip, 53); // google DNS, or something else reliable
//    if (socket.waitForConnected(10)) {
//        qDebug()
//                << "local IPv4 address for Internet connectivity is"
//                << socket.localAddress().toString();
//                found=true;
//    }
//    ++cpt;
//}
