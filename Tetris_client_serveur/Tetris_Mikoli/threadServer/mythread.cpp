#include "mythread.h"
#include <iostream>
#include <QJsonDocument>
#include <QDebug>

namespace mikoli {

MyThread::MyThread (TetrisGame * game,SideBoard * sideboard,ChoiceBoard * choiceBoard,int port,QString ip, QObject *parent) : QThread(parent) {
    _socket = new QTcpSocket();

    connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    _socket->connectToHost(ip, port);

    if(!_socket->waitForConnected()) {
        qDebug() << "Client: impossible de se connecter à ce serveur.";
        sideboard->setMessage(QString(" Server unreachable"));
        sideboard->visibleMessage(true);
        sideboard->setDisplay();
        return;
    }

    qDebug() << "Client: connecté.";
    _game = game;
    _sideBoard = sideboard;
    _choiceBoard = choiceBoard;
    qDebug() << "Client: thread créé.";
    _isConnected = true;

    start();
}
MyThread::MyThread (TetrisGame * game,SideBoard * sideboard,ChoiceBoard * choiceBoard,Gamemode mode,int goal,int port,QString ip, QObject *parent):
    MyThread(game,sideboard,choiceBoard,port,ip){

    sendMessage(GameMessage(TypeMessage::PLAYPARAM,mode,goal));
}

void MyThread::run() {
    qDebug() << "Client: lancement du thread.";
    exec();
}

void MyThread::readyRead() {
    qDebug() << "Client: un message a été reçu et va être traité.";

    GameMessage received;
    received.deserialize_from_json(QJsonDocument::fromJson(_socket->readAll()).object());

    switch (received.getTypeMessage()) {
    case TypeMessage::RESTART:
        _choiceBoard->getButtonRestart()->setVisible(false);
        _game->restart();
        std::cout<<"client a reçu message: restart"<<std::endl;
        break;
    case TypeMessage::PLAYPARAM:
        _game->startWithMode(received.getGameMode(),received.getGoalGameMode(),false);
        _sideBoard->visibleMessage(false);
        _choiceBoard->getButtonRestart()->setVisible(false);
        _choiceBoard->getButtonNewGame()->setVisible(false);
        _sideBoard->setDisplay();
        std::cout<<"client a reçu message: playparam"<<std::endl;
        break;
    case TypeMessage::PLAY:
        _game->startWithMode(Gamemode::NONE, 0,false);
        _sideBoard->visibleMessage(false);
        _choiceBoard->getButtonRestart()->setVisible(false);
        _choiceBoard->getButtonNewGame()->setVisible(false);
        _sideBoard->setDisplay();
        std::cout<<"client a reçu message: play"<<std::endl;
        break;
    case TypeMessage::LOOSE:
        _game->endGameFromOpponent(received);
        std::cout<<"client a reçu message: loose"<<std::endl;
        break;
    case TypeMessage::PARAM:  _game->updateGameFromOpponent(received.getLines());
        std::cout<<"client a reçu message: mettre ligne"<<std::endl;
        break;
    case TypeMessage::QUIT:
        sendMessage(GameMessage(TypeMessage::DISCONNECT));
        std::cout<<"L'adversaire a abandonne"<<std::endl;
        handleQuit();
        emit endThread();
        std::cout<<"client a reçu message: quit"<<std::endl;
        break;
    case TypeMessage::WIN:
        _game->endGameFromOpponent(received);
        std::cout<<"L'adversaire a Gagne"<<std::endl;
        std::cout<<"client a reçu message: win"<<std::endl;
        break;

    default: break;
    }
    qDebug() << "Client: un message a été reçu et correctement traité.";
}

void MyThread::sendMessage(GameMessage message) {
    qDebug() << "Client: un message va être envoyé.";
    std::cout<<enumToInt(message.getTypeMessage())<<std::endl;
    _socket->write(QJsonDocument(message.serialize_to_json()).toJson());
    _socket->flush();
    qDebug() << "Client: un message a été envoyé.";
}

void MyThread::disconnected() {
    qDebug() << "Client: déconnecté du serveur.";
    _socket->deleteLater();
    exit(0);
}

void MyThread::handleQuit(){
    _choiceBoard->hide();
    _game->startWithMode(Gamemode::NONE,0,true);
    _game->switchPause();
    _game->setIsBegin(false);

    _isConnected = false;
    _choiceBoard->getButtonQuit()->setVisible(false);
    _choiceBoard->getButtonQuickGame()->setVisible(false);
    _choiceBoard->getButtonRestart()->setVisible(false);
    _choiceBoard->getButtonNewGame()->setVisible(false);
    _choiceBoard->getButtonTwoPlayers()->setVisible(true);
    _choiceBoard->getButtonSinglePlayer()->setVisible(true);
    _choiceBoard->getButtonHome()->setVisible(false);
    _sideBoard->visibleMessage(false);
    _sideBoard->setDisplay();
}

QTcpSocket * MyThread::getSocket(){
    return _socket;
}

bool MyThread::getIsConnected(){
    return _isConnected;
}

void MyThread::setIsConnected(bool b){
    _isConnected = b;
}

}
