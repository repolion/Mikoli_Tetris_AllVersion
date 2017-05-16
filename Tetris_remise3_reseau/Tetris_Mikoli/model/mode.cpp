#include "mode.h"

namespace mikoli{
//  constructeur par défaut
Mode::Mode(){}

//  constructeur avec paramètres
Mode::Mode(Gamemode gm, int goal){
    _gameMode = gm;
    _goal = goal;
}

//  destructeur
Mode::~Mode(){}

//  retourne le gameMode courant
Gamemode Mode::getGameMode(){
    return _gameMode;
}

//  retourne le goal courant
int Mode::getGoal(){
    return _goal;
}

//  modifie le gameMode du jeu
void Mode::setGameMode(Gamemode gm){
    _gameMode = gm;
}

// modifie le but à atteindre du jeu
void Mode::setGoal(int goal){
    _goal = goal;
}

}
