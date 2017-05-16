#include "gamemessage.h"


using namespace std;

namespace mikoli {
//*----- CONSTRUCTORS -----*//

GameMessage::GameMessage(){}

GameMessage::GameMessage (TypeMessage msg) {
    _message = msg;
}

GameMessage::GameMessage (TypeMessage msg, std::vector<std::vector<int>> lines) {
    _message = msg;
    _lines = lines;
}

GameMessage::GameMessage (TypeMessage msg, Gamemode gameMode, int goal) {
    _message = msg;
    _gameMode = gameMode;
    _goalGameMode = goal;
}

GameMessage::GameMessage (const GameMessage & copie) {
    _message = copie._message;
    _lines = copie._lines;
    _gameMode = copie._gameMode;
    _goalGameMode = copie._goalGameMode;
}

GameMessage::~GameMessage(){}

//*----- GETTERS -----*//

TypeMessage GameMessage::getTypeMessage() {
    return _message;
}

std::vector<std::vector<int>> GameMessage::getLines() {
    return _lines;
}

Gamemode GameMessage::getGameMode() {
    return _gameMode;
}

int GameMessage::getGoalGameMode() {
    return _goalGameMode;
}

//*----- SERIALIZATION ------*//

QJsonObject GameMessage::serialize_to_json() {
    QJsonObject obj;

    //  sérialisation de l'énumération
    int enumMsgInt = enumToInt(_message);
    obj.insert("message", enumMsgInt);

    //  sérialisation des lignes
    QJsonArray v1;
    for (std::vector<int> l : _lines) {
        QJsonObject temp;
        QJsonArray v2;
        for (int i : l) {
            QJsonObject hole;
            hole.insert("h", i);
            v2.append(hole);
        }
        temp.insert("l", v2);
        v1.append(temp);
    }
    obj.insert("lignes", v1);

    //  sérialisation du gamemode
    int enumGmInt = gmToInt(_gameMode);
    obj.insert("gamemode", enumGmInt);

    //  sérialisation du goal du gamemode
    obj.insert("goal", _goalGameMode);

    return obj;
}

void GameMessage::deserialize_from_json(const QJsonObject & obj) {
    //  désérialisation du type du message
    TypeMessage msg = intToEnum(obj.value("message").toInt());
    _message = msg;

    //  désérialisation des lignes
    std::vector<std::vector<int>> lines;
    QJsonArray v1 = obj.value("lignes").toArray();
    for (QJsonValue tempo : v1) {
        QJsonObject temp = tempo.toObject();
        QJsonArray v2 = temp.value("l").toArray();
        std::vector<int> specificLine;
        for (QJsonValue holeo : v2) {
            QJsonObject hole = holeo.toObject();
            int i = hole.value("h").toInt();
            specificLine.push_back(i);
        }
        lines.push_back(specificLine);
    }
    _lines = lines;

    //  désérialisation du gamemode
    Gamemode gm = intToGm(obj.value("gamemode").toInt());
    _gameMode = gm;

    //  désérialisation du goal du gamemode
    _goalGameMode = obj.value("goal").toInt();
}

}
