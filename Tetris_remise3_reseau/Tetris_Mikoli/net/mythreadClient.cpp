#include "mythreadClient.h"

namespace mikoli {

MyThreadClient::MyThreadClient (TetrisGame * game,SideBoard * sideboard,ChoiceBoard * choiceBoard,int port,QString ip, QObject *parent) : QThread(parent) {
    _socket = new QTcpSocket();

    connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    _socket->connectToHost(ip, port);

    if(!_socket->waitForConnected(2000)) {
        sideboard->setMessage(QString(" Server unreachable"));
        sideboard->visibleMessage(true);
        sideboard->setDisplay();
        return;
    }

    _game = game;
    _sideBoard = sideboard;
    _choiceBoard = choiceBoard;
    _isConnected = true;

    start();

}
MyThreadClient::MyThreadClient (TetrisGame * game,SideBoard * sideboard,ChoiceBoard * choiceBoard,Gamemode mode,int goal,int port,QString ip, QObject *parent):
    MyThreadClient(game,sideboard,choiceBoard,port,ip){

    sendMessage(GameMessage(TypeMessage::PLAYPARAM,mode,goal));
}

void MyThreadClient::run() {
    exec();
}

void MyThreadClient::readyRead() {

    GameMessage received;
    received.deserialize_from_json(QJsonDocument::fromJson(_socket->readAll()).object());

    switch (received.getTypeMessage()) {
    case TypeMessage::RESTART:
        _choiceBoard->getButtonRestart()->setVisible(false);
        _game->restart();
        break;
    case TypeMessage::PLAYPARAM:
        _game->startWithMode(received.getGameMode(),received.getGoalGameMode(),false);
        _sideBoard->visibleMessage(false);
        _choiceBoard->getButtonRestart()->setVisible(false);
        _choiceBoard->getButtonNewGame()->setVisible(false);
        _sideBoard->setDisplay();
        break;
    case TypeMessage::PLAY:
        _choiceBoard->getButtonServerOff()->setVisible(false);
        _choiceBoard->getButtonServerOn()->setVisible(false);
        _game->startWithMode(Gamemode::NONE, 0,false);
        _sideBoard->visibleMessage(false);
        _choiceBoard->getButtonRestart()->setVisible(false);
        _choiceBoard->getButtonNewGame()->setVisible(false);
        _sideBoard->setDisplay();
        break;
    case TypeMessage::LOOSE:
        _game->endGameFromOpponent(received);
        break;
    case TypeMessage::PARAM:  _game->updateGameFromOpponent(received.getLines());
        break;
    case TypeMessage::QUIT:
        handleQuit();
        emit endThread();
        break;
    case TypeMessage::WIN:
        _game->endGameFromOpponent(received);
        break;

    default: break;
    }
}

void MyThreadClient::sendMessage(GameMessage message) {
    _socket->write(QJsonDocument(message.serialize_to_json()).toJson());
    _socket->flush();
}

void MyThreadClient::disconnected() {
    _socket->deleteLater();
    exit(0);
}

void MyThreadClient::handleQuit(){
    emit infoServerStatus();
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

QTcpSocket * MyThreadClient::getSocket(){
    return _socket;
}

bool MyThreadClient::getIsConnected(){
    return _isConnected;
}

void MyThreadClient::setIsConnected(bool b){
    _isConnected = b;
}

}
