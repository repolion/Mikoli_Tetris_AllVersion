#include "gamemode.h"

namespace mikoli {

int gmToInt (Gamemode gm) {
    switch (gm) {
    case Gamemode::NBLINES: return 0;
    case Gamemode::TIME: return 1;
    case Gamemode::SCORE: return 2;
    case Gamemode::NONE: return 3;
    }
}

Gamemode intToGm (int a) {
    switch (a) {
    case 0: return Gamemode::NBLINES;
    case 1: return Gamemode::TIME;
    case 2: return Gamemode::SCORE;
    case 3: return Gamemode::NONE;
    }
}

}
