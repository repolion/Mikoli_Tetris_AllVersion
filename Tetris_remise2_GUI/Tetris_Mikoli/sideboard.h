#ifndef SIDEBOARD_H
#define SIDEBOARD_H

#include "observer.h"
#include <Qlabel>
#include "tetrisgame.h"

namespace mikoli{

/*!
 * \brief The SideBoartd class
 */
class SideBoard: public Observer{
private:

    /*!
     * \brief The Label which set the pixmap
     */
    QLabel* _ql;

    /*!
     * \brief The TetrisGame (observable)
     */
    TetrisGame * _game;

    /*!
     * \brief The pixmap used to paint the nextFigure on it
     */
    QPixmap _pixmap;

    /*!
     * \brief The height of the board
     */
    int _height;

    /*!
     * \brief The width of the board
     */
    int _width;


    void displayLabel(QString label,int caseSize,int column, int line,QColor, int fontSize);
    void paint(Block bl,int blSize,QColor color,int a,int b,int c,int d,double opacity,bool gradient);

    /*!
     * \brief To display the seconds from the timer with a zero Before the first digit of
     * seconds if seconds are below 10 seconds
     */
    QString convertSec();

    /*!
     * \brief To display the minutes from the timer with a zero Before the first digit of minutes
     * if the minutes are below 10 minutes
     */
    QString convertMin();

    /*!
     * \brief To display the Game mode's goal
     */
    QString modeGoal();

public:

    /*!
     * \brief Constructor of SideBoard without parameters
     */
    SideBoard();

    /*!
     * \brief Constructor of SideBoard with parameters
     * \param fenetre the Widget in which the SideBoard has to appear
     * \param game the TetrisGame (observable)
     */
    SideBoard(QWidget &fenetre, TetrisGame & game);

    /*!
     * \brief To display the SideBoard
     */
    void setDisplay();

    /*!
     * \brief The method executed when the observable changed
     */
    void Update();
};

}

#endif // SIDEBOARD_H
