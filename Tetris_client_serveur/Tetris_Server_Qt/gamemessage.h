#ifndef GAMEMESSAGE_H
#define GAMEMESSAGE_H

#include "typemessage.h"
#include "serializable.h"
#include "deserializable.h"
#include "gamemode.h"
#include <QString>
#include <vector>

using namespace std;

namespace mikoli {

class GameMessage : public Serializable, Deserializable {
private:
    /*!
     * \brief GameMessage's type
     * see the TypeMessage enumeration
     */
    TypeMessage _message;

    /*!
     * \brief correspond to the lines received by the opponent
     * during a 2 players game.
     * 1st vector is line 1 to add and the int inside the vector
     * are the blocks that have to be free in this line
     */
    std::vector<std::vector<int>> _lines;

    /*!
     * \brief GameMode in a game with a goal to reach.
     * see the GameMode enumeration
     */
    Gamemode _gameMode;

    /*!
     * \brief the goal to reach
     * a number of line, a time in minutes or a score to reach
     */
    int _goalGameMode;

public:
    //  constructeurs
    /*!
     * \brief GameMessage Constructor withour parameters
     */
    GameMessage();

    /*!
     * \brief GameMessage Constructor
     * \param TypeMessage The type of message
     */
    GameMessage(TypeMessage);

    /*!
     * \brief GameMessage Constructor
     * \param TypeMessage The type of message
     * \param vector containing info about the blocks to had to the
     * opponent
     */
    GameMessage(TypeMessage, std::vector<std::vector<int>>);

    /*!
     * \brief GameMessage Constructor
     * \param TypeMessage The type of message
     * \param GameMode the game mode
     * \param the number correspondinf to the goal to reach
     */
    GameMessage(TypeMessage, Gamemode, int);

    /*!
     * \brief GameMessage Constructor by copy
     * \param a reference to a GameMessage
     */
    GameMessage(const GameMessage & copie);

    /*!
     * \brief GameMessage destructor
     */
    ~GameMessage();

    // méthodes
    /*!
     * \brief to get the type of the GameMessage
     */
    TypeMessage getTypeMessage();

    /*!
     * \brief to get the vector correspondinf to the block to add
     * from the opponent player(when did lines)
     */
    std::vector<std::vector<int>> getLines();

    /*!
     * \brief to get the game mode
     */
    Gamemode getGameMode();

    /*!
     * \brief to get the goal to reach when playing with game mode
     */
    int getGoalGameMode();

    /*!
     * \brief to serialize a message to Json
     */
    QJsonObject serialize_to_json();

    /*!
     * \brief to deserialize a message from Json
     */
    void deserialize_from_json(const QJsonObject&);
};

}

#endif // GAMEMESSAGE_H
