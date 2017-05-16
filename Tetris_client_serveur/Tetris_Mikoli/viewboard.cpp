#include "viewboard.h"

namespace mikoli{

ViewBoard::ViewBoard(){}

void ViewBoard::Update(){
    setDisplay();
}

ViewBoard::ViewBoard(QWidget & fenetre, TetrisGame * game){

    int width = 340;
    int height = 640;

    _game = game;
    _width = game->getBoard().getBoardSize().first;
    _height = game->getBoard().getBoardSize().second;
    _ql = new QLabel(&fenetre);
    _pixmap=QPixmap(width,height);
    _pixmap.fill(QColor("transparent"));

    setDisplay();

}

//Méthode qui permet d'afficher le board ainsi que tout ce qui le compose
void ViewBoard::setDisplay(){

    _width = this->_game->getBoard().getBoardSize().first;
    _height = this->_game->getBoard().getBoardSize().second;
    int block_width=300/_width;

    //dessine le board
    _pixmap = QPixmap(340,640);
    _pixmap.fill(QColor("transparent"));
    for(int i = 1 ; i <= _height ; i++){
        for(int j = 1 ; j <= _width ; j++){
            QPainter painter(&_pixmap);
            painter.setPen(QColor(81, 81, 81, 255));
            painter.setBrush(QColor(40, 40, 40, 255));
            painter.drawRect(QRect(j*block_width,i*block_width,block_width,block_width));
        }
    }

    //dessine la current figure
    if(!this->_game->isGameOver() && !this->_game->isPaused()){
        for(Block b: this->_game->getCurrentFig().getBlocks()){
            ViewBoard::paint(b,block_width,Qt::gray,0,0,0,0,1,false);
            ViewBoard::paint(b,block_width,Qt::black,4,4,6,6,1,false);
            ViewBoard::paint(b,block_width,b.getQColor(),2,2,5,5,1,true);
        }
    }

    //dessine les blocks "tombés" dans le bas du board
    if(!this->_game->isGameOver() && !this->_game->isPaused()){
        for(Block b: this->_game->getBoard().getBlocks()){
            ViewBoard::paint(b,block_width,Qt::white,0,0,0,0,1,false);
            ViewBoard::paint(b,block_width,Qt::black,4,4,6,6,1,false);
            ViewBoard::paint(b,block_width,b.getQColor(),2,2,5,5,1,true);
        }
    }

    //dessine la shadow
    if(!this->_game->isGameOver() && !this->_game->isPaused()){
        for(Block b: this->_game->getShadowCF()){
            QPainter painter(&_pixmap);
            painter.setPen(Qt::white);
            painter.setBrush(Qt::transparent);
            painter.drawRect(QRect(b.getPosition().getX()*block_width,
                                   (_height+1)*block_width-b.getPosition().getY()*block_width,block_width-3,block_width-3));
        }
    }
    if(this->_game->isGameOver()){
        for(Block b: this->_game->getBoard().getBlocks()){
            ViewBoard::paint(b,block_width,Qt::white,0,0,0,0,0.2,false);
            ViewBoard::paint(b,block_width,Qt::black,4,4,6,6,0.2,false);
            ViewBoard::paint(b,block_width,b.getQColor(),2,2,5,5,0.2,true);
        }
    }
    _ql->setPixmap(_pixmap);
}

//pour dessiner les figures avec possibilité d'appliquer une transparence au bloc ainsi qu'un gradient de couleur
void ViewBoard::paint(Block bl,int blSize,QColor color,int a,int b,int c,int d,double opacity,bool grad){

    QPainter painter(&_pixmap);
    painter.setPen(Qt::black);
    painter.setBrush(color);
    painter.setOpacity(opacity);
    QRect myQRect= QRect((bl.getPosition().getX()*blSize)+a,
                         ((_height+1)*blSize-bl.getPosition().getY()*blSize)+b,blSize-c,blSize-d);
    if(grad){
        QLinearGradient gradient(myQRect.topLeft(), myQRect.bottomRight());
        gradient.setColorAt(0, QColor(245, 184, 184,255));
        gradient.setColorAt(0.5, color);
        painter.fillRect(myQRect, gradient);
    }else painter.drawRect(myQRect);
}

}
