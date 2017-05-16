#ifndef MODE_H
#define MODE_H
#include "gamemode.h"

namespace mikoli{

/*!
 * \brief The Mode class
 * Manage the game mode of the game.
 * By this class, it's possible to switch between different game modes.
 */
class Mode{
private:
    /*!
     * \brief _gameMode
     * The game mode of the game
     */
    Gamemode _gameMode;

    /*!
     * \brief _goal
     * The goal to reach.
     * It's game mode requires a goal to reach.
     */
    int _goal;

public:
    //  Constructor & destructor

    /*!
     * \brief Mode
     * Constructor by default.
     */
    Mode();

    /*!
     * \brief Mode
     * Constructor with parameters.
     * Gamemode is the game mode of the game.
     * int is the goal to reach.
     */
    Mode(Gamemode, int);

    ~Mode();

    /*!
     * \brief getGameMode
     * \return The current game mode of the game.
     */
    Gamemode getGameMode();

    /*!
     * \brief getGoal
     * \return The goal to reach.
     */
    int getGoal();

    /*!
     * \brief setGameMode
     * Set a new game mode to the game.
     */
    void setGameMode(Gamemode);

    /*!
     * \brief setGoal
     * Set a new goal to reach.
     */
    void setGoal(int);
};

}

#endif // MODE_H
