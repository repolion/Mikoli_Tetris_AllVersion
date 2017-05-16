#include "score.h"

namespace mikoli{

//  constructeur par défaut
Score::Score():_score{0},_nbLines{0}, _oldTen{0},_level{0}{
    _levelUpSound = new SoundPlayer("levelUp.mp3", false);
    _levelUpSound->setVolume(20);
}

//  destructeur
Score::~Score(){}

// Getter
//  retourne le nombre de lignes faites
int Score::getNbLines() const {
    return _nbLines;
}

//  retourne le score actuel
int Score::getScore() const{
    return _score;
}

//  retourne le level actuel
int Score::getLevel() const{
    return _level;
}

//  autres méthodes
//  met à jour le score et le level en fonction du nombre de ligne faites et du drop
void Score::updateScore(int nbL, int nbDrop){
    if(nbL < 0){
        throw TetrisException {"Number of lines invalid, must be positive."};
    }

    _oldTen = _nbLines/10;
    _nbLines += nbL;

    if((_nbLines/10 != _oldTen)){
        _level++;
        _levelUpSound->play();
    }

    _score += calculScore(nbL, nbDrop);
}

//  calcule le score à ajouter au joueur en fonction du nombre de lignes faites et du drop
int Score::calculScore(int nbL, int nbDrop){
    int result = 0;

    switch(nbL){
    case 0: result += (40 * nbL) + nbDrop;
        break;
    case 1: result += (40 * nbL) + nbDrop;
        break;
    case 2 : result += (100 * nbL) + nbDrop;
        break;
    case 3: result += (300 * nbL) + nbDrop;
        break;
    case 4: result += (1200 * nbL) + nbDrop;
        break;
    default:
        break;
    }

    return result;
}

}
