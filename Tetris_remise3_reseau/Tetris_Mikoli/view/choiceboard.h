#ifndef CHOICEBOARD_H
#define CHOICEBOARD_H

#include <qlabel.h>
#include <QGroupBox>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>
#include <QPainter>
#include <QVBoxLayout>

#include "model/gamemode.h"
#include "buttons.h"
#include "observer/observer.h"
#include "model/tetrisgame.h"
#include "ipdialog.h"

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
    ChoiceBoard(QWidget & fenetre, TetrisGame * game);

    /*!
     * \brief To get the GameMode
     */
    Gamemode getMode();

    /*!
     * \brief To get the restart Button
     */
    QPushButton *getButtonRestart();

    /*!
     * \brief To get the cheat code Button (GodMode)
     */
    QPushButton *getButtonGodMode();

    /*!
     * \brief To get the NewGame Button
     */
    QPushButton *getButtonNewGame();

    /*!
     * \brief To get the QuickGame Button
     */
    QPushButton *getButtonQuickGame();

    /*!
     * \brief To get the 2 players Button
     */
    QPushButton *getButtonTwoPlayers();

    /*!
     * \brief To get the 1 player Button
     */
    QPushButton *getButtonSinglePlayer();

    /*!
     * \brief To get the 1 player Button
     */
    QPushButton *getButtonHome();

    /*!
     * \brief To get the cancel multi players Button
     */
    QPushButton *getButtonQuit();

    /*!
     * \brief To get the server ON Button
     */
    QPushButton *getButtonServerOn();

    /*!
     * \brief To get the join Button
     */
    QPushButton *getButtonJoin();

    /*!
     * \brief To get the server OFF Button
     */
    QPushButton *getButtonServerOff();

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

    /*!
     * \brief To get the Dialog Box Ip
     * Used for asking the ip and port for
     * connecting to the host in multiplayer game
     */
    IpDialog *getIpDialog();

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
     * \brief The cheat code invisible Button
     */
    QPushButton *_buttonGodMode;

    /*!
     * \brief The QuickGame QPushButton
     */
    QPushButton *_buttonQuickGame;

    /*!
     * \brief The 2 Players QPushButton
     */
    QPushButton *_buttonTwoPlayers;

    /*!
     * \brief The 1 Player QPushButton
     */
    QPushButton *_buttonSinglePlayer;

    /*!
     * \brief The Button to go back to choice between
     * one or two player
     */
    QPushButton *_buttonHome;

    /*!
     * \brief The 2 Quit QPushButton
     *  to cancel a 2 players game
     */
    QPushButton *_buttonQuit;

    /*!
     * \brief To make the application a client
     * that can join a server if playing multi player game
     */
    QPushButton *_buttonServerOn;

    /*!
     * \brief To make the application a server
     * to host a multi player game
     */
    QPushButton *_buttonServerOff;

    /*!
     * \brief The join button to make a player
     * join a multiplayer game
     */
    QPushButton *_buttonJoin;

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
    IpDialog *_ipDialog;

};

}

#endif // CHOICEBOARD_H
