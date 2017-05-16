#include "typemessage.h"

namespace mikoli {

TypeMessage intToEnum(int a) {
    switch(a) {
    case 0: return TypeMessage::RESTART;
    case 1: return TypeMessage::QUIT;
    case 2: return TypeMessage::INFORM;
    case 3: return TypeMessage::WAIT;
    case 4: return TypeMessage::READY;
    case 5: return TypeMessage::PARAM;
    case 6: return TypeMessage::BUSY;
    case 7: return TypeMessage::RESULT;
    case 8: return TypeMessage::PLAY;
    case 9:return TypeMessage::DISCONNECT;
    case 10:return TypeMessage::LOOSE;
    case 11:return TypeMessage::WIN;
    case 12:return TypeMessage::PLAYPARAM;
    }
}

int enumToInt (TypeMessage msg) {
    switch(msg) {
    case TypeMessage::RESTART: return 0;
    case TypeMessage::QUIT: return 1;
    case TypeMessage::INFORM: return 2;
    case TypeMessage::WAIT: return 3;
    case TypeMessage::READY: return 4;
    case TypeMessage::PARAM: return 5;
    case TypeMessage::BUSY: return 6;
    case TypeMessage::RESULT: return 7;
    case TypeMessage::PLAY: return 8;
    case TypeMessage::DISCONNECT: return 9;
    case TypeMessage::LOOSE: return 10;
    case TypeMessage::WIN: return 11;
    case TypeMessage::PLAYPARAM: return 12;
    }
}

}
