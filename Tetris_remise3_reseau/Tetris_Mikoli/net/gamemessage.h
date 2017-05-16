#ifndef GAMEMESSAGE_H
#define GAMEMESSAGE_H

#include <iostream>
#include <QJsonArray>
#include <QString>
#include <vector>

#include "typemessage.h"
#include "serializable.h"
#include "deserializable.h"
#include "model/gamemode.h"


using namespace std;

namespace mikoli {

/*!
 * \brief The GameMessage class
 *  This is the message each player can send to each other.
 *  This class is serializable and deserializable in order to be send through the network via TCP.
 */

class GameMessage : public Serializable, Deserializable {

private:

    /*!
     * \brief _message
     *  According to the message, the receiver do some specific actions.
     *  The differents messages come from an enumeration.
     */
    TypeMessage _message;

    /*!
     * \brief _lines
     *  Each vector represents a line, each int represents a abscisse in this line where there is a hole.
     */
    std::vector<std::vector<int>> _lines;

    /*!
     * \brief _gameMode
     */
    Gamemode _gameMode;

    /*!
     * \brief _goalGameMode
     */
    int _goalGameMode;

public:

    /*----- CONSTRUCTORS -----*/

    /*!
     * \brief GameMessage
     *  Default's constructor
     */
    GameMessage();

    /*!
     * \brief GameMessage
     *  Constructor with only a message.
     */
    GameMessage(TypeMessage);

    /*!
     * \brief GameMessage
     *  Constructor with a message and the lines to send to the opponent.
     */
    GameMessage(TypeMessage, std::vector<std::vector<int>>);

    /*!
     * \brief GameMessage
     *  Constructor with a message, a gamemode and the goal for this gamemode.
     */
    GameMessage(TypeMessage, Gamemode, int);

    /*!
     * \brief GameMessage
     * \param copie A Gamemessage
     *  Constructor by copy.
     */
    GameMessage(const GameMessage & copie);

    /*!
     *  \brief ~GameMessage
     *   Default's destructor
     */
    ~GameMessage();

    /*----- GETTERS -----*/

    /*!
     * \brief getTypeMessage
     * \return The message
     */
    TypeMessage getTypeMessage();

    /*!
     * \brief getLines
     * \return The lines from the opponent to add in the board
     */
    std::vector<std::vector<int>> getLines();

    /*!
     * \brief getGameMode
     * \return The gamemode
     */
    Gamemode getGameMode();

    /*!
     * \brief getGoalGameMode
     * \return The goal for the gamemode
     */
    int getGoalGameMode();

    /*!
     * \brief serialize_to_json
     * \return An JSON object representation of the message.
     *  This method transform an instance of this class into a QJsonObject.
     *  It's necessary because a QJsonObject can be send through the network via TCP.
     */
    QJsonObject serialize_to_json();

    /*!
     * \brief deserialize_from_json
     *  This method transform a QJsonObject into an instance of this class.
     */
    void deserialize_from_json(const QJsonObject&);
};

}

#endif // GAMEMESSAGE_H
