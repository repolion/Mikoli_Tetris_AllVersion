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

    TypeMessage _message;
    std::vector<std::vector<int>> _lines;
    Gamemode _gameMode;
    int _goalGameMode;

public:
    //  constructeurs
    GameMessage();
    GameMessage(TypeMessage);
    GameMessage(TypeMessage, std::vector<std::vector<int>>);
    GameMessage(TypeMessage, Gamemode, int);
    GameMessage(const GameMessage & copie);
    ~GameMessage();

    // méthodes
    void afficherInformations() const;
    TypeMessage getTypeMessage();
    std::vector<std::vector<int>> getLines();
    Gamemode getGameMode();
    int getGoalGameMode();
    QJsonObject serialize_to_json();
    void deserialize_from_json(const QJsonObject&);
};

}

#endif // GAMEMESSAGE_H
