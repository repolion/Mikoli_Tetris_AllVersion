#include "myserver.h"


namespace mikoli {

MyServer::MyServer (ushort port, QObject *parent) : QTcpServer(parent) {
    _gameMode=Gamemode::NONE;
    _port = port;
}

void MyServer::startServer (){
    if(!this->listen(QHostAddress::Any, _port)){
        qDebug() << "Erreur: lancement du serveur";
    }
}

//Appel par QtcpServer lors d'une nouvelle connexion
void MyServer::incomingConnection (qintptr socketDescriptor){

    if(!_busy){
        //Nouvelle connexion

        MyThreadServer *thread = new MyThreadServer(socketDescriptor);
        qRegisterMetaType<GameMessage>("GameMessage");
        connect(thread, SIGNAL(sendToServer(GameMessage,int)), this, SLOT(receivingFromThread(GameMessage,int)));
        thread->start();

        if (!_waiting) {
            thread->setId(1);
            _pairThread.first = thread;
            _waiting = true;
            connect(this, SIGNAL(sendToClientOne(GameMessage)), thread, SLOT(sendToClientOne(GameMessage)));
        } else if (_waiting) {
            thread->setId(2);
            _pairThread.second = thread;
            _busy=true;
            _waiting= false;
            connect(this, SIGNAL(sendToClientTwo(GameMessage)), thread, SLOT(sendToClientTwo(GameMessage)));
        }

        connect(this, SIGNAL(sendToAllTread(GameMessage)), thread, SLOT(messageToAllClient(GameMessage)));
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

        if (_busy) {
            if (_gameMode!=Gamemode::NONE) {
                emit sendToAllTread(GameMessage(TypeMessage::PLAYPARAM,_gameMode,_goal));
            } else {
                emit sendToAllTread(GameMessage(TypeMessage::PLAY));
            }
        }
    }
}

void MyServer::setMode (Gamemode gm) {
    _gameMode = gm;
}

bool MyServer::isWaiting (){
    return _waiting;
}

void MyServer::receivingFromThread (GameMessage message,int id) {

    if (message.getTypeMessage()==TypeMessage::QUIT) {
        if (id==1) {
            emit sendToClientTwo(message);
            closeSockets();
        } else {
            emit sendToClientOne(message);
            closeSockets();
        }
        _waiting = false;
        _busy = false;
    } else if (message.getTypeMessage()==TypeMessage::PLAYPARAM) {
        _gameMode = message.getGameMode();
        _goal = message.getGoalGameMode();
    } else {
        if (id==1) {
            emit sendToClientTwo(message);
        }
        else if (id ==2) {
            emit sendToClientOne(message);
        }
    }
}

void MyServer::closeSockets () {
    if(_pairThread.second != NULL){
        _pairThread.second->closeSocket();
        _pairThread.second->exit();
    }
    if(_pairThread.first != NULL){
        _pairThread.first->closeSocket();
        _pairThread.first->exit();
    }
}
}






