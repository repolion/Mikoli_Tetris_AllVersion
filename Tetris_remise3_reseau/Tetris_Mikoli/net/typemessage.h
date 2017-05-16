#ifndef TYPEMESSAGE_H
#define TYPEMESSAGE_H

#include <QString>

namespace mikoli {

enum class TypeMessage{

    RESTART,QUIT,INFORM,WAIT,READY,PARAM,BUSY,RESULT,PLAY,DISCONNECT,LOOSE,WIN,PLAYPARAM

};

TypeMessage intToEnum(int);
int enumToInt(TypeMessage);

}

#endif // TYPEMESSAGE_H
