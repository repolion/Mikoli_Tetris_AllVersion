#include "position.h"

namespace mikoli{

//  constructeur par défaut
Position::Position():Position(0,0){}

//  constructeur avec paramètres
Position::Position(int x, int y):_x{x}, _y{y}{}

//  destructeur
Position::~Position(){}


// Getters
int Position::getX(){
    return _x;
}

int Position::getY(){
    return _y;
}

// Setters
void Position::setX(int x){
    _x = x;
}

void Position::setY(int y){
    _y = y;
}

//  autres
//  renvoit vrai si la position courante est la même que la position "position"
bool Position::isSame(Position position){
    return (_x == position.getX()) && (_y == position.getY());
}

}
