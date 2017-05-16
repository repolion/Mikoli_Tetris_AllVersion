#ifndef MAINCONTROL_H
#define MAINCONTROL_H

#include "gamemode.h"
#include "tetrisgame.h"

namespace mikoli{

/*!
 * \brief The MainControl class
 * This class is the controller of the game.
 * It is the interface between the GUI and the model.
 * It receives the informations from the user and call the methods necessary.
 * It will start the game.
 */
class MainControl
{
private:
    // Private attributes
    /*!
     * \brief _gameMode Defines the rule that will determine the end of the game
     */
    GameMode _gameMode;
    /*!
     * \brief _customFigure Defines if customs figures will be used in the game or not.
     */
    bool _customFig;
    /*!
     * \brief _tetrisGame Defines the rule that will determine the end of the game
     */
    TetrisGame _tetrisGame;

public:
    // Others methods
    /*!
     * \brief startNewGame
     * It create a new game with standard options
     */
    void startNewGame();
    /*!
     * \brief selectMode
     * It makes possible to choose differents game mode.
     */
    void selectMode(GameMode gameMode);
    /*!
     * \brief customize
     * It makes possible to create cusztomized Figures that could be added to the game
     */
    void customize();
    /*!
     * \brief exitApp
     * Method that closes the application.
     */
    void exitApp();

};

}

#endif // MAINCONTROL_H
