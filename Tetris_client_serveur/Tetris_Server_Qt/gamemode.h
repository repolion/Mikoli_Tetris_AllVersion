#ifndef GAMEMODE_H
#define GAMEMODE_H

namespace mikoli {

/*!
 * \brief The Gamemode enum
 * All the modes possible
 */
enum class Gamemode {
    NBLINES, TIME, SCORE, NONE
};

//Methods used when sereliaze/deserialize

/*!
 * \brief to convert a GameMode to an int
 * \param Gamemode the game mode to convert
 */
int gmToInt (Gamemode);

/*!
 * \brief to convert an int to a Gamemode
 * \param int the int to convert to a GameMode
 */
Gamemode intToGm (int);

}

#endif // GAMEMODE_H
