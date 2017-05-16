#ifndef CHOICEBOARD_H
#define CHOICEBOARD_H

#include <qlabel.h>
#include "gamemode.h"
#include <QGroupBox>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>
#include "observer.h"
#include "tetrisgame.h"

namespace mikoli {

class ChoiceBoard:public Observer
{
public:
    /*!
     * \brief The constructor of ChoiceBoard without parameters
     */
    ChoiceBoard();

    /*!
     * \brief The constructor of ChoiceBoard with parameters
     * \param fenetre the Widget in which the ChoiceBoard has to appear
     * \param game the TetrisGame
     */
    ChoiceBoard(QWidget & fenetre, TetrisGame & game);

    /*!
     * \brief To get the GameMode
     */
    Gamemode getMode();

    /*!
     * \brief To get the restart Button
     */
    QPushButton *getButtonRestart();

    /*!
     * \brief To get the NewGame Button
     */
    QPushButton *getButtonNewGame();

    /*!
     * \brief To get the QuickGame Button
     */
    QPushButton *getButtonQuickGame();

    /*!
     * \brief To get the Game mode value (which is the goal)
     * \param mode the Gamemode
     */
    int getModeValue(Gamemode mode);

    /*!
     * \brief To hide the ChoiceBoard
     */
    void hide();

    /*!
     * \brief To show the ChoiceBoard with the Buttons
     */
    void show();

    /*!
     * \brief To show the ChoiceBoard (only the radiobuttons and spin boxes)
     */
    void showChooseMenu();

    /*!
     * \brief The method executed when the observable changed
     */
    void Update();

private:
    /*!
     * \brief The QGroupBox in which are the QRadioButtons ant he spin boxes
     */
    QGroupBox *_groupbox;

    /*!
     * \brief The Start QPushButton
     */
    QPushButton *_buttonStart;

    /*!
     * \brief The restart QPushButton
     */
    QPushButton *_buttonRestart;

    /*!
     * \brief The NewGame QPushButton
     */
    QPushButton *_buttonNewGame;

    /*!
     * \brief The QuickGame QPushButton
     */
    QPushButton *_buttonQuickGame;

    /*!
     * \brief The QRadioButtons
     */
    QRadioButton *_radio1;
    QRadioButton *_radio2;
    QRadioButton *_radio3;
    /*!
     * \brief The QspinBoxes
     */
    QSpinBox *_scoreToReach;
    QSpinBox *_nbLines;
    QSpinBox *_timeUp;

    /*!
     * \brief The TetrisGame (Observed)
     */
    TetrisGame  *_game;

};

}

#endif // CHOICEBOARD_H
