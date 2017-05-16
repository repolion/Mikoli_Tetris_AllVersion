#include "paintboard.h"
#include "tetrisgame.h"
#include "viewboard.h"
#include <QPainter>
#include <widget.h>
#include <QWidget>


namespace mikoli{

PaintBoard::PaintBoard(){
    std::cout<<"hello";
}

PaintBoard::PaintBoard(QWidget & fenetre, TetrisGame & game){
    _game = game;
    _width = game.getBoard().getBoardSize().first;
    _height = game.getBoard().getBoardSize().second;

}
void PaintBoard::paintEvent(QWidget & fenetre,QPaintEvent *event){
    for(int i = 1 ; i <= 20 ; i++){
        for(int j = 1 ; j <= 10 ; j++){
            QPainter painter(&fenetre);
            painter.setPen(Qt::black);
            painter.setBrush(Qt::gray);
            painter.drawRect(QRect(j*30,i*30,30,30));
        }

    }
    Figure fig = Figure(TypeShape::L);
    fig.newPosition(Position(5,17));
    paintFigure(fenetre,event,fig);

   PaintBoard::paintEvent(fenetre,event);
}

void PaintBoard::paintFigure(QWidget & fenetre,QPaintEvent *event,Figure fig){
    for(Block b: fig.getBlocks()){
        QPainter painter(&fenetre);
        painter.setPen(Qt::black);
        painter.setBrush(Qt::green);
        painter.drawRect(QRect(b.getPosition().getX()*30,630-b.getPosition().getY()*30,30,30));
    }




}
void PaintBoard::Update(const Observable* observable){
    std::cout<<"updateddddd";
}

}


