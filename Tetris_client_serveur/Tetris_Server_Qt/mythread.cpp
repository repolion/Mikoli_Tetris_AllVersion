#include "mythread.h"
#include <iostream>
#include <QJsonObject>
#include <QJsonDocument>

namespace mikoli {

MyThread::MyThread(qintptr ID,QObject *parent) :
    QThread(parent){
    this->_socketDescriptor = ID;
    _socket = new QTcpSocket();

    // set the ID
    if(!_socket->setSocketDescriptor(this->_socketDescriptor)){
        //Si erreur -> signal
        emit error(_socket->error());
        std::cout<<"problème de socket"<<std::endl;
        return;
    }
    connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    qDebug() << _socketDescriptor << " Client connected";

}

void MyThread::run(){

    // le thread commence ici
    qDebug() << " Début du Thread";
    exec();

}

void MyThread::readyRead(){
    GameMessage received;
    received.deserialize_from_json(QJsonDocument::fromJson(_socket->readAll()).object());

    //envoi au serveur le message venant du client
    sendToServer(received,_id);
}

void MyThread::disconnected(){
    qDebug() << _socketDescriptor << " déconnexion";
    _socket->deleteLater();
    exit(0);
}

void MyThread::messageToAllClient(GameMessage message){  
    if(_id==1){
        emit sendToClientTwo(message);
    }
    else if(_id==2){
        emit sendToClientOne(message);
    }

}

void MyThread::sendToClientOne(GameMessage message){
    _socket->write(QJsonDocument(message.serialize_to_json()).toJson());
    _socket->flush();
    std::cout<<"Message envoyé au client 1 "<<std::endl;

}

void MyThread::sendToClientTwo(GameMessage message){
    _socket->write(QJsonDocument(message.serialize_to_json()).toJson());
    _socket->flush();
    std::cout<<"Message envoyé au client 2 "<<std::endl;

}

void MyThread::setId(int id){
    _id = id;
}

void MyThread::closeSocket(){
    _socket->close();
}

}
