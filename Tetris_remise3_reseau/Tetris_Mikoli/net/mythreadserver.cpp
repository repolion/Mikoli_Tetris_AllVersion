#include "mythreadserver.h"

namespace mikoli {

MyThreadServer::MyThreadServer(qintptr ID,QObject *parent) :
    QThread(parent){
    this->_socketDescriptor = ID;
    _socket = new QTcpSocket();

    // set the ID
    if(!_socket->setSocketDescriptor(this->_socketDescriptor)){
        //Si erreur -> signal
        emit error(_socket->error());
        return;
    }

    connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

void MyThreadServer::run(){
    exec();
}

//  lecture des messages reçu par le thread
void MyThreadServer::readyRead(){
    GameMessage received;
    received.deserialize_from_json(QJsonDocument::fromJson(_socket->readAll()).object());

    //envoi au serveur le message venant du client
    sendToServer(received,_id);

}

//  fermeture du thread
void MyThreadServer::disconnected(){
    _socket->deleteLater();
    exit(0);
}

//  envois un message aux deux clients
void MyThreadServer::messageToAllClient(GameMessage message){
    if(_id==1){
        emit sendToClientTwo(message);
    }
    else if(_id==2){
        emit sendToClientOne(message);
    }
}

//  envois un message au client 1
void MyThreadServer::sendToClientOne(GameMessage message){
    _socket->write(QJsonDocument(message.serialize_to_json()).toJson());
    _socket->flush();
}

//  envois un message au client 2
void MyThreadServer::sendToClientTwo(GameMessage message){
    _socket->write(QJsonDocument(message.serialize_to_json()).toJson());
    _socket->flush();
}

void MyThreadServer::setId(int id){
    _id = id;
}

void MyThreadServer::closeSocket(){
    _socket->close();
}

QTcpSocket* MyThreadServer::getSocket(){
    return _socket;
}


}
