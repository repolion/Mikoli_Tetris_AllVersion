#include "figure.h"

namespace mikoli{

//  Constructeur & destructeur

//  Constructeur par défaut
Figure::Figure(){}

//  Constructeur avec paramètre
Figure::Figure(TypeShape typeShape){

    _typeFigure = typeShape;
    int x = 0;
    int y = 0;

    switch(typeShape){
    case TypeShape::I:{
        _Blocks[0] = Block(x, y,Color::CYAN);
        _Blocks[1] = Block(x-1, y,Color::CYAN);
        _Blocks[2] = Block(x+1, y,Color::CYAN);
        _Blocks[3] = Block(x+2, y,Color::CYAN);
    }break;
    case TypeShape::O:{
        _Blocks[0] = Block(x, y,Color::GREEN);
        _Blocks[1] = Block(x, y-1,Color::GREEN);
        _Blocks[2] = Block(x+1, y,Color::GREEN);
        _Blocks[3] = Block(x+1, y-1,Color::GREEN);

    }break;
    case TypeShape::T:{
        _Blocks[0] = Block(x, y,Color::YELLOW);
        _Blocks[1] = Block(x-1, y,Color::YELLOW);
        _Blocks[2] = Block(x+1, y,Color::YELLOW);
        _Blocks[3] = Block(x, y-1,Color::YELLOW);

    }break;
    case TypeShape::J:{
        _Blocks[0] = Block(x, y,Color::BLUE);
        _Blocks[1] = Block(x-1, y,Color::BLUE);
        _Blocks[2] = Block(x+1, y,Color::BLUE);
        _Blocks[3] = Block(x+1, y-1,Color::BLUE);

    }break;
    case TypeShape::L:{
        _Blocks[0] = Block(x, y,Color::RED);
        _Blocks[1] = Block(x+1, y,Color::RED);
        _Blocks[2] = Block(x-1, y,Color::RED);
        _Blocks[3] = Block(x-1, y-1,Color::RED);

    }break;
    case TypeShape::Z:{
        _Blocks[0] = Block(x, y,Color::PURPLE);
        _Blocks[1] = Block(x-1, y,Color::PURPLE);
        _Blocks[2] = Block(x, y-1,Color::PURPLE);
        _Blocks[3] = Block(x+1, y-1,Color::PURPLE);

    }break;
    case TypeShape::S:{
        _Blocks[0] = Block(x, y,Color::DEEPPINK);
        _Blocks[1] = Block(x+1, y,Color::DEEPPINK);
        _Blocks[2] = Block(x, y-1,Color::DEEPPINK);
        _Blocks[3] = Block(x-1, y-1,Color::DEEPPINK);

    }break;
    case TypeShape::C:{

    }break;

    }
}

//  Getter
//  retourne un vecteur avec les positions de la figure
std::vector<Position> Figure::getPositions(){
    std::vector<Position> list;
    for(Block bl : _Blocks){
        list.push_back(bl.getPosition());
    }
    return list;
}

//  retourne le type de la figure
TypeShape Figure::getTypeFigure(){
    return _typeFigure;
}

//  retourne un vecteur avec les blocs de la figure
std::vector<Block> Figure::getBlocks(){
    std::vector<Block> list;
    list.push_back(_Blocks[0]);
    list.push_back(_Blocks[1]);
    list.push_back(_Blocks[2]);
    list.push_back(_Blocks[3]);
    return list;
}

//  autres méthodes
//  déplace la figure dans la direction "direction"
void Figure::move(Direction direction) {
    switch(direction){
    case Direction::LEFT:
        for(int i = 0; i < 4; i++ ){
            _Blocks[i].setPosition(_Blocks[i].getPosition().getX()- 1,
                                   _Blocks[i].getPosition().getY());
        }
        break;
    case Direction::RIGHT:
        for(int i = 0; i < 4; i++ ){
            _Blocks[i].setPosition(_Blocks[i].getPosition().getX()+ 1,
                                   _Blocks[i].getPosition().getY());
        }
        break;
    case Direction::DOWN:
        for(int i = 0; i < 4; i++ ){
            _Blocks[i].setPosition(_Blocks[i].getPosition().getX(),
                                   _Blocks[i].getPosition().getY()-1);
        }
        break;
    }

}

//  rotationne la figure dans la direction "direction"
void Figure::rotate(Direction direction) {
    if(direction==Direction::DOWN){
        throw TetrisException{"Can't turn in this direction"};
    }
    if(_typeFigure != TypeShape::O){

        switch(direction){
        case Direction::LEFT:
            for(int i=0;i<4;i++){

                int x = - (_Blocks[i].getPosition().getY() - _Blocks[0].getPosition().getY()) + _Blocks[0].getPosition().getX();

                int y = (_Blocks[i].getPosition().getX() - _Blocks[0].getPosition().getX()) + _Blocks[0].getPosition().getY();

                _Blocks[i].setPosition(x,y);

            }
            break;
        case Direction::RIGHT:
            for(int i=0;i<4;i++){

                int x = (_Blocks[i].getPosition().getY() - _Blocks[0].getPosition().getY()) + _Blocks[0].getPosition().getX();

                int y = -(_Blocks[i].getPosition().getX() - _Blocks[0].getPosition().getX()) + _Blocks[0].getPosition().getY();

                _Blocks[i].setPosition(x,y);

            }
            break;
        case Direction::DOWN:
            break;
        }
    }

}

//  modifie les positions des blocs de la figure selon la position "position"
void Figure::newPosition(Position position){
    int moveX = position.getX();
    int moveY = position.getY();

    for(int i = 0; i<4; i++){
        _Blocks[i].setPosition(_Blocks[i].getPosition().getX() +
                               moveX, _Blocks[i].getPosition().getY() + moveY);
    }

}

//  remplace les blocs de la figure par ceux du vecteur "bl"
void Figure::setBlocks(std::vector<Block> bl) {
    for(int i=0; i<4; ++i){
        _Blocks[i] = bl.at(i);
    }
}

}










