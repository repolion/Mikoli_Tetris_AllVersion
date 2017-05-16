#include "block.h"

namespace mikoli{

Block::Block():Block(0,0,Color::RED){}

//      Constructeur avec paramètres
Block::Block(int x, int y, Color color):_position{Position(x, y)}, _color{color}{}

//    Destructeur
Block::~Block(){}

// Getters
Position Block::getPosition() const{
    return _position;
}

QColor Block::getQColor(){
    QColor color;
    switch(this->_color){
    case Color::RED:
        color = Qt::red;
        break;
    case Color::GREEN:
        color = QColor(50,205, 50, 255);
        break;
    case Color::ORANGE:
        color = QColor(238, 154, 0, 255);
        break;
    case Color::BLUE:
        color = QColor(72, 118, 255, 255);
        break;
    case Color::PURPLE:
        color =  QColor(89, 51, 204, 255);
        break;
    case Color::DEEPPINK:
        color = QColor(255, 52, 179, 255);
        break;
    case Color::CYAN:
        color = Qt::cyan;
        break;
    case Color::YELLOW:
        color = Qt::yellow;
        break;
    case Color::GREY:
        color = QColor(204,204,204,255);
        break;

    }
    return color;
}

Color Block::getColor() {
    return _color;
}

// Setter
void Block::setPosition(int x, int y){
    _position.setX(x);
    _position.setY(y);
}

// Autres
void Block::move(Direction direction){
    switch(direction){
    case Direction::DOWN : _position.setY(_position.getY() - 1);
        break;
    case Direction::LEFT : _position.setX(_position.getX() - 1);
        break;
    case Direction::RIGHT : _position.setX(_position.getX() + 1);
        break;
    }
}
}
