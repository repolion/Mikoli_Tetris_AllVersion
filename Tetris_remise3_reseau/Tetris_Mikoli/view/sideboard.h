#ifndef SIDEBOARD_H
#define SIDEBOARD_H

#include <Qlabel>

#include "observer/observer.h"
#include "model/tetrisgame.h"
#include "qpainter.h"

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

    /*!
     * \brief to display a custom label for the sideboard window
     * \param label the text to display
     * \param caseSize The square size of an invisible grid
     * \param column the number of invisible case on the left of the label
     * \param label row the number of invisible case ont top of the label
     * \param QColor the label's color
     * \param fontSize the label's font size
     */
    void displayLabel(QString label,int caseSize,int column, int line,QColor, int fontSize);

    /*!
     * \brief paint to display blocks (used to paint figures)
     * paramteters are used to make possible the draw of figures with effects
     *
     * \param bl an object Block to display
     * \param blSize the height and width of a Block
     * \param color the block's color
     * \param a shift on the x axis to place the start of the block's drawing
     * \param b shift on the y axis to place the start of the block's drawing
     * \param c shift on the x axis to diminuate the width of the square
     * \param d shift on the x axis to diminuate the height of the square
     * \param opacity the value for the opacity of the draw
     * \param gradient a value used for the brush of the color
     */
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

    /*!
     * \brief To display custom message in front of the playing board
     */
    QString _message = "";

    /*!
     * \brief To display the host's ip above the sideboard
     */
    QString _ip = "";

    /*!
     * \brief To display the host's port above the sideboard
     */
    QString _port = "";

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
    SideBoard(QWidget &fenetre, TetrisGame * game);

    /*!
     * \brief To display the SideBoard
     */
    void setDisplay();

    /*!
     * \brief The method executed when the observable changed
     */
    void Update();

    /*!
     * \brief bool used to display or not a waiting label
     * when multiplayer gaming
     */
    bool _isWaiting = false;

    /*!
     * \brief bool used to display or not a "server unreachable" label
     * when multiplayer gaming
     */
    bool _isUnreachable = false;

    /*!
     * \brief bool used to display or not a message label in front
     * of the playing board
     */
    bool _messageVisible;
    /*!
     * \brief to make visible or not the message label
     * the one placed in the center of the playing board
     */
    void visibleMessage(bool b);

    bool getWaiting();
    bool getUnreachable();

    /*!
     * \brief to set the bool value used to display an
     * unreachable message
     */
    void setUnreachable(bool b);

    /*!
     * \brief to set The label message
     */
    void setMessage(QString);

    /*!
     * \brief to set the port label
     */
    void setPort(QString);

    /*!
     * \brief to set the ip label
     */
    void setIp(QString);

};

}

#endif // SIDEBOARD_H
