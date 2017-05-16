#ifndef SCORE_H
#define SCORE_H

#include "soundplayer.h"
#include "tetrisexception.h"
#include <stdexcept>

namespace mikoli{

/*!
 * \brief The Score class
 * This class will inform the score of the user and the number
 * of lines he's done.
 * Also used buy the GUI.
 */
class Score{

private:
    //Private Attributes
    /*!
     * \brief _score
     * The score can't be negative and is set to 0
     * at the start of the game.
     */
    int _score;

    /*!
     * \brief _nbLines
     * The number of lines can't be negative and is set to 0
     * at the start of the game.
     */
    int _nbLines;

    /*!
     * \brief _oldTen
     * A copy of the actuel ten
     */
    int _oldTen;

    /*!
     * \brief _level
     * The current level
     */
    int _level;

    /*!
     * \brief _levelUpSound
     * The sound when we level up.
     */
    SoundPlayer * _levelUpSound;

public:
    //Constructor / destructor

    /*!
     * \brief Score's constructor without parameters.
     * This only constructor will set the score to 0
     * and the number of lines to 0 at the start of the game.
     */
    Score();

    /*!
     * \brief Score's destructor.
     */
    ~Score();

    //Getter
    /*!
      * \brief getNbLines
      * \return The number of lines made by the player from the start of the game.
      */

    int getNbLines() const;

    /*!
     * \brief getScore
     * \return The current score
     */
    int getScore() const;

    /*!
     * \brief getLevel
     * \return The current level
     */
    int getLevel() const;

    //Other method
    /*!
     * \brief updateScore
     * \param the number of lines the player made at the last move.
     * This number will be added to the previous score.
     * \param nbDrop the number of lines the player cross during a fall.
     * \throw TetrisException if nb is negative.
     */
    void updateScore(int nbL, int nbDrop);

    /*!
     * \brief calculScore
     * \param nbL the number of lines the player made at the last move.
     * \param nbDrop the number of lines the player cross during a fall.
     * \return the amount to add to the score.
     */
    int calculScore(int nbL, int nbDrop);
};

}
#endif // SCORE_H
