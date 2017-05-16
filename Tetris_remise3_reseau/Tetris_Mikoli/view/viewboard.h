#ifndef VIEWBOARD_H
#define VIEWBOARD_H

#include "observer/observer.h"
#include <Qlabel>
#include "model/tetrisgame.h"

namespace mikoli{
class ViewBoard: public Observer{
private:
    /*!
     * \brief The Label which set the pixmap
     */
    QLabel* _ql;

    /*!
     * \brief The Tetris Game (observed)
     */
    TetrisGame  *_game;

    /*!
     * \brief The Board width
     */
    int _width;

    /*!
     * \brief The Board height
     */
    int _height;

    /*!
     * \brief The pixmap used to paint the board,currentFigure,... on it
     */
    QPixmap _pixmap;

public:

    /*!
     * \brief The constructor of ViewBoard without parameter
     */
    ViewBoard();

    /*!
     * \brief The constructor of ViewBoard with parameters
     * \param fenetre the Widget in which the Viewboard has to appear
     * \param game The TetrisGame (observed)
     */
    ViewBoard(QWidget &fenetre, TetrisGame * game);

    /*!
     * \brief The method called to display the board
     */
    void setDisplay();

    /*!
     * \brief Method to paint blocks with parameters
     * With a relief effect
     * \param bl the block to paint
     * \param blSize the block's width
     * \param color the block's color
     * \param a value used to print the first level of the block painting (position)
     * \param b value used to print the first level of the block painting (width)
     * \param c value used to print the second level of the block painting (position)
     * \param d value used to print the second level of the block painting (width)
     * \param opacity the opacity of the block painting
     */
    void paint(Block bl,int blSize,QColor color,int a,int b,int c,int d,double opacity,bool grad);
    //    void paintGrad(Block bl,int blSize,QColor color,int a,int b,int c,int d,double opacity);

    /*!
     * \brief The method executed when the observable changed
     */
    void Update();

};

}

#endif // VIEWBOARD_H
