#include "sideboard.h"

namespace mikoli{

SideBoard::SideBoard(){}

SideBoard::SideBoard(QWidget & fenetre, TetrisGame * game){

    _game = game;
    _width = this->_game->getBoard().getBoardSize().first;
    _height = this-> _game->getBoard().getBoardSize().second;
    _ql = new QLabel(&fenetre);
    setDisplay();
}

void SideBoard::setDisplay(){

    int block_width=300/_width;
    _pixmap = QPixmap(680,1280);
    _pixmap.fill(QColor("transparent"));

    //Affichage de la "Next Figure"
    if(!this->_game->isGameOver() && !this->_game->isPaused()){
        for(Block b: this->_game->getNextFig().getBlocks()){

            SideBoard::paint(b,block_width,Qt::white,0,0,0,0,1,false);
            SideBoard::paint(b,block_width,Qt::black,4,4,6,6,1,false);
            SideBoard::paint(b,block_width,b.getQColor(),2,2,5,5,1,true);
        }
    }

    //Affichage timer
    QString text = convertMin() + ":" + convertSec();
    SideBoard::displayLabel(text,5,112,44,Qt::white,20);

    //Qstrings pour les différents affichages
    QString scoreQ = "Score:  "+QString::number(this->_game->getScore());
    QString levelQ = "Level :  "+QString::number(this->_game->getLevel());
    QString linesQ = "Number of lines:  "+QString::number(this->_game->getNbLines());
    QString pausedQ = "Paused";
    QString gameOverQ = "GAME OVER";
    QString playerWinQ = "WINNER";
    QString nextQ = "Next:";
    QString goalQ = "Goal: " + modeGoal();

    //Affiche les labels
    SideBoard::displayLabel(scoreQ,5,78,12,Qt::white,15);
    SideBoard::displayLabel(levelQ,5,78,17,Qt::white,15);
    SideBoard::displayLabel(linesQ,5,78,22,Qt::white,15);
    SideBoard::displayLabel(nextQ,5,78,33,Qt::white,15);

    //Affiche Les labels IP & PORT
    SideBoard::displayLabel(_ip,5,82,5,Qt::white,11);
    SideBoard::displayLabel(_port,5,112,5,Qt::white,11);

    //Affiche l'objectif à atteindre
    if(_game->getMode().getGameMode()!=Gamemode::NONE){
        SideBoard::displayLabel(goalQ,5,78,27,Qt::white,15);
    }

    //Affiche "pause"
    if(this->_game->isBegin() && this->_game->isPaused() && !this->_isWaiting ){
        SideBoard::displayLabel(pausedQ,15,9,15,Qt::red,20);
    }

    if(_messageVisible){
        SideBoard::displayLabel(_message,15,4,20,Qt::red,20);
    }

    //Affiche "Player won" ou "Game Over"
    if(this->_game->isGameOver() && this->_game->isWon()){
        SideBoard::displayLabel(playerWinQ,10,8,28,Qt::green,40);
    }
    else if(this->_game->isGameOver()){
        SideBoard::displayLabel(gameOverQ,10,4,28,Qt::red,40);
    }
    _ql->setPixmap(_pixmap);
}

//update du display lorsque notifié
void SideBoard::Update(/*const Observable* observable*/){
    setDisplay();
}

//Permet d'afficher les Titres: Score, level,...
void SideBoard::displayLabel(QString title,int caseSize,int column,int line,QColor color,int fontSize){
    QFont font;
    font.setStyleHint(QFont::Times, QFont::PreferAntialias);
    font.setPointSize(fontSize);
    QPainter painter;
    painter.begin(&_pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(color);
    painter.setFont(font);
    painter.drawText(caseSize*column, caseSize*line,title);
    painter.setBrush(QColor(255, 0, 0, 127));
}

//Pour afficher des blocs avec paramètres (sert ici à afficher la prochaine figure)
void SideBoard::paint(Block bl,int blSize,QColor color,int a,int b,int c,int d,double opacity,bool grad){

    QPainter painter(&_pixmap);
    painter.setPen(Qt::black);
    painter.setBrush(color);
    painter.setOpacity(opacity);

    QRect myQRect=(QRect((bl.getPosition().getX()*blSize+450)+a,(_height-bl.getPosition().getY()*blSize+160)+b,blSize-c,blSize-d));
    if(grad){
        QLinearGradient gradient(myQRect.topLeft(), myQRect.bottomRight());
        gradient.setColorAt(0, QColor(245, 184, 184,255));
        gradient.setColorAt(0.5, color);
        painter.fillRect(myQRect, gradient);
    }else painter.drawRect(myQRect);

}

//permet d'afficher le nombre de secondes avec un 0 devant si <10
QString SideBoard::convertSec(){
    if(!_game->isBegin())return "00";
    if(_game->getTimer()->getSeconds()<10){
        return "0"+QString::number(_game->getTimer()->getSeconds());
    }else return QString::number(_game->getTimer()->getSeconds());
}
//permet d'afficher le nombre de minutes avec un 0 devant si <10
QString SideBoard::convertMin(){
    if(!_game->isBegin())return "00";
    if(_game->getTimer()->getMinutes()<10){
        return "0"+QString::number(_game->getTimer()->getMinutes());
    }else return QString::number(_game->getTimer()->getMinutes());
}

QString SideBoard::modeGoal(){
    switch(_game->getMode().getGameMode()){
    case Gamemode::SCORE :return QString::number((_game->getMode().getGoal()))+" points";
        break;
    case Gamemode::NBLINES:return QString::number((_game->getMode().getGoal()))+" lines";
        break;
    case Gamemode::TIME:return QString::number((_game->getMode().getGoal()))+" min";
        break;
    case Gamemode::NONE:return "";
        break;
    }
    return "";
}

void SideBoard::setUnreachable(bool b){
    _isUnreachable = b;
}

void SideBoard::visibleMessage(bool b){
    _messageVisible = b;
}

bool SideBoard::getUnreachable(){
    return _isUnreachable;
}

bool SideBoard::getWaiting(){
    return _isWaiting;
}

void SideBoard::setMessage(QString message){
    _message = message;
}

void SideBoard::setIp(QString ip){
    _ip = ip;
}

void SideBoard::setPort(QString port){
    _port = port;
}

}
