#include "myserver.h"
#include <iostream>

namespace mikoli {

MyServer::MyServer(QObject *parent) :
    QTcpServer(parent){
    _gameMode=Gamemode::NONE;
}

void MyServer::startServer(){
    int port = 1024;
    if(!this->listen(QHostAddress::Any, port)){
        qDebug() << "Erreur: lancement du serveur";
    }
    else{
        qDebug() << "Ecoute sur le port: " << port << "...";
    }

}

//Appel par QtcpServer lors d'une nouvelle connexion
void MyServer::incomingConnection(qintptr socketDescriptor){
    if(_busy){
        std::cout<<"Le serveur est occupé..."<<std::endl;
    }
    else{
        //Nouvelle connexion
        qDebug() << socketDescriptor << " Connexion";

        MyThread *thread = new MyThread(socketDescriptor);
        qRegisterMetaType<GameMessage>("GameMessage");
        connect(thread, SIGNAL(sendToServer(GameMessage,int)),
                this, SLOT(receivingFromThread(GameMessage,int)));
        thread->start();

        if(!_waiting){
            thread->setId(1);
            _pairThread.first = thread;
            _waiting = true;
            std::cout<<"client 1 en config"<<std::endl;
            connect(this, SIGNAL(sendToClientOne(GameMessage)),
                    thread, SLOT(sendToClientOne(GameMessage)));
        }else if(_waiting){
            std::cout<<"client 2 en config"<<std::endl;
            thread->setId(2);
            _pairThread.second = thread;
            _busy = true;
            _waiting = false;
            connect(this, SIGNAL(sendToClientTwo(GameMessage)),
                    thread, SLOT(sendToClientTwo(GameMessage)));
            std::cout<<"serveur n'écoute plus"<<std::endl;
        }

        connect(this, SIGNAL(sendToAllTread(GameMessage)),
                thread, SLOT(messageToAllClient(GameMessage)));
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
        std::cout<<"start du thread"<<std::endl;
        if(_busy){
            if(_gameMode!=Gamemode::NONE){
                emit sendToAllTread(GameMessage(TypeMessage::PLAYPARAM,_gameMode,_goal));
            }else{
                emit sendToAllTread(GameMessage(TypeMessage::PLAY));
            }
        }
    }
}

bool MyServer::isWaiting(){
    return _waiting;
}

void MyServer::receivingFromThread(GameMessage message,int id){
    std::cout<<"Serveur: message reçu du thread -> "<<id<<std::endl;
    if(message.getTypeMessage()==TypeMessage::DISCONNECT){
        std::cout<<"Le client "<<id<<" a quitte la partie"<<std::endl;
        std::cout<<"Fermeture des threads client "<<id<<std::endl;
        if(id==1){
            _pairThread.first->closeSocket();
            _pairThread.first->exit();
        }else{
            _pairThread.second->closeSocket();
            _pairThread.second->exit();
        }
        _busy = false;
    }
    else if(message.getTypeMessage()==TypeMessage::QUIT){
        if(id==1){
            emit sendToClientTwo(message);
            _pairThread.first->closeSocket();
            _pairThread.first->exit();
        }else{
            emit sendToClientOne(message);
            _pairThread.second->closeSocket();
            _pairThread.second->exit();
        }
        _waiting = false;
    }else if(message.getTypeMessage()==TypeMessage::PLAYPARAM){
        _gameMode = message.getGameMode();
        _goal = message.getGoalGameMode();
    }
    else{
        if(id==1){
            emit sendToClientTwo(message);
        }
        else if(id==2){
            emit sendToClientOne(message);
        }
    }
}
}




