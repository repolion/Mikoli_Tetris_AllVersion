#ifndef TETRISGAME_H
#define TETRISGAME_H

#include "figuresbag.h"
#include "board.h"
#include "soundplayer.h"
#include "gamemode.h"
#include "mode.h"
#include "score.h"
#include "timer.h"
#include "figure.h"
#include "position.h"
#include <QTimerEvent>
#include <QObject>
#include <chrono>
#include <list>
#include <vector>
#include "observablewidget.h"

namespace mikoli{
/*!
 * \brief The TetrisGame class
 *
 * This class will be used for build a new game.
 *
 * \ref _figuresBag The list in which are each figure
 * that will become the next figure and then the current Figure.
 * \ref _currentFigure The figure that can be rotated or moved
 *  during its descent.
 * \ref _nextFigure
 */
class TetrisGame: public Observable,public ObservableWidget, public QObject {

private:
    // Privates attributes
    /*!
     * \brief _figuresBag
     * The list in which are each figure
     * that will become the next figure and then the current Figure.
     */
    FiguresBag _figuresBag;

    /*!
     * \brief _currentFigure The figure that can be rotated or moved,
     * by the player, during Its descent.
     */
    Figure _currentFigure;

    /*!
     * \brief _shadowCF
     * The shadow is the ghost figure, in white, that indicates
     * the player where it's figure will fall.
     */
    Block _shadowCF[4];

    /*!
     * \brief _nextFigure The next figure that will be played by the player
     */
    Figure _nextFigure;

    /*!
     * \brief _board
     */
    Board _board;

    /*!
     * \brief _currentScore
     * .
     */
    Score _currentScore;

    /*!
     * \brief _mode
     * The game mode.
     */
    Mode _mode;

    /*!
     * \brief _timerGame
     * A timer of the time the game is running.
     */
    Timer* _timerGame;

    /*!
     * \brief _isBegin
     */
    bool _isBegin;

    /*!
     * \brief _isPaused
     */
    bool _isPaused;

    /*!
     * \brief _isGameOver
     */
    bool _isGameOver;

    /*!
     * \brief _isFalling
     */
    bool _isFalling;

    /*!
     * \brief _autoDown
     */
    bool _autoDown;

    /*!
     * \brief _isWon
     */
    bool _isWon;

    bool _isSinglePlayer;

    /*!
     * \brief _tetrisMusic
     * The music of the game.
     */
    SoundPlayer * _tetrisMusic;

    /*!
     * \brief _goPause
     * Sound when we set the game in pause.
     */
    SoundPlayer * _goPause;

    /*!
     * \brief _backPause
     * Sound when we resume the game.
     */
    SoundPlayer * _backPause;

    /*!
     * \brief _gameOverSound
     * Sound when the game is over.
     */
    SoundPlayer * _gameOverSound;

    /*!
     * \brief _fallSound
     * Sound when the current figure touch the bottom after a fall.
     */
    SoundPlayer * _fallSound;

    //  differents sounds if we delete one, two, three of four line
    //  in one move.
    SoundPlayer * _deleteOneLineSound;
    SoundPlayer * _deleteTwoLineSound;
    SoundPlayer * _deleteThreeLineSound;
    SoundPlayer * _deleteFourLineSound;

public:
    // Constructor / destructor
    /*!
     * \brief TetrisGame's constructor without parameter.
     * Build a standard game with level mode "normal" and difficulty "normal".
     */
    TetrisGame();

    /*!
     * \brief TetrisGame's constructor with size parameters.
     * Build a standard game with level mode "normal" and difficulty "normal".
     */
    TetrisGame(int width,int height);

    /*!
     * \brief TetrisGame destructor.
     * Deallocate the memory that was previously reserved for the Game.
     */
    ~TetrisGame();

    //Getter

    /*!
     * \brief getCurrentFig
     * \return The current figure
     */
    Figure getCurrentFig();

    /*!
     * \brief getShadowCF
     * \return A vector with the blocks of the shadow.
     */
    std::vector<Block> getShadowCF() const;

    /*!
     * \brief getNextFig
     * \return The next figure.
     */
    Figure getNextFig();

    /*!
     * \brief getBoard
     * \return The board.
     */
    Board getBoard();

    /*!
     * \brief isGameOver
     * \return True is the game is over, false otherwise.
     */
    bool isGameOver();

    /*!
     * \brief isWon
     * \return True if the player reached it's goal, false otherwise.
     */
    bool isWon();

    /*!
     * \brief getScore
     * \return The current score.
     */
    int getScore();

    /*!
     * \brief getLevel
     * \return The current level.
     */
    int getLevel();

    /*!
     * \brief getNbLines
     * \return The current number of lines made.
     */
    int getNbLines();

    /*!
     * \brief getMode
     * \return The mode of the game.
     */
    Mode getMode();

    /*!
     * \brief isBegin
     * \return True if the game is began, false otherwise.
     */
    bool isBegin();

    /*!
     * \brief isPaused
     * \return True if the game is paused, false otherwise.
     */
    bool isPaused();

    /*!
     * \brief statutSpeed
     * \return The actual speed of the game.
     * It's a calcul made according of the level.
     */
    int getSpeed();

    /*!
     * \brief statutIsFalling
     * \return True if the current figure is falling.
     */
    bool getIsFalling();

    bool isSinglePlayer();

    bool checkIfIsBlocked();

    /*!
     * \brief getTimer
     * \return The timer instance with the elapsed time.
     */
    Timer* getTimer();

    /*!
     * \brief isWin
     * Check if the conditions of win are completed.
     */
    void isWin();

    // Others methods

    /*!
     * \brief move
     * \param direction The direction we want to move.
     * Move the current figure in the direction "direction".
     */
    void move(Direction direction);

    /*!
     * \brief rotate
     * \param direction The direction we want to rotate.
     * Rotate the current figure in the direction "direction".
     */
    void rotate(Direction direction);

    /*!
     * \brief fall
     */
    void fall();

    /*!
     * \brief fallSlow
     */
    void fallSlow();

    /*!
     * \brief endMove
     * \param nbDrop The number of lines crossed by a fall.
     * Handle the end of a move:
     * Add the current figure to the board, check and remove lines if necessary,
     * update the score, change the current figure with the next one,
     * check if the next current figure can be placed in the board,
     * check the conditions of win, ..., call endGame() is necessary.
     */
    void endMove(int nbDrop);

    /*!
     * \brief endGame
     * Stop the "tetris" music and play the "game over" sound,
     * replace all the blocks from the board with grey blocks.
     */
    void endGame();

    /*!
     * \brief calculateShadow
     * Calcul the positions of the shadow according to the positions
     * of the current figure.
     */
    void calculateShadow();

    /*!
     * \brief switchPause
     * Switch the game into paused / not paused mode.
     */
    void switchPause();

    //Setter
    /*!
     * \brief setIsBegin
     * \param isBegin
     * Set the attribute _isBegin with the parameter.
     */
    void setIsBegin(bool isBegin);

    /*!
     * \brief setIsFalling
     * \param isFalling
     * Set the attribute _isFalling with the parameter.
     */
    void setIsFalling(bool isFalling);

    /*!
     * \brief setAutoDown
     * \param autoDown
     * Set the attribute _autoDown with the parameter.
     */
    void setAutoDown(bool autoDown);


    /*!
     * \brief start() To start the game initialized.
     * Actives the timer and make te "first current figure" moving down.
     */
    void start();

    /*!
     * \brief startWithMode
     * Do the same as start() but change the game mode and the goal.
     */
    void startWithMode(Gamemode, int,bool);

    /*!
     * \brief restart
     * Restart the game: reset the score, level, number of lines, board, figure's bag,
     * reset the sounds, reset the attriubutes, ...
     */
    void restart();

    void upCurrentFigure (int);

    void updateGameFromOpponent(std::vector<std::vector<int>>);

    void endGameFromOpponent(GameMessage);

};

}

#endif // TETRISGAME_H
