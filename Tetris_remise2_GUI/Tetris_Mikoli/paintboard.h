#ifndef PAINTBOARD_H
#define PAINTBOARD_H

#include <widget.h>
#include <QMainWindow>
#include "tetrisgame.h"
#include "viewboard.h"
#include "figure.h"

namespace mikoli{

class PaintBoard: public Observer{
public:
   PaintBoard();
    PaintBoard(QWidget & fenetre, TetrisGame & game);

    void Update(const Observable* observable);

protected:
    void paintEvent(QWidget & fenetre,QPaintEvent *event);

private:
    void paintFigure(QWidget & fenetre,QPaintEvent *event,Figure fig);

    TetrisGame _game;
    int _width;
    int _height;
};

}

#endif // PAINTBOARD_H
