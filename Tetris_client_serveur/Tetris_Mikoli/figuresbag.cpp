#include "figuresbag.h"

namespace mikoli{

//  Constructeur par défaut
FiguresBag::FiguresBag(){
    refresh();
}

//  destructeur
FiguresBag::~FiguresBag(){}

//  retourne la figure suivante
Figure FiguresBag::getNextFigure(){
    Figure fig = _nextFigure;
    if(_listFigures.size() == 0){
        refresh();
    } else {
        _nextFigure = _listFigures.back();
        _listFigures.pop_back();
    }
    return fig;
}

//  réinitialise le "sac de brique" quand il est vide
void FiguresBag::refresh(){
    const std::vector<TypeShape> allTypes = {TypeShape::I, TypeShape::J,
                                             TypeShape::L, TypeShape::O, TypeShape::S,
                                             TypeShape::T, TypeShape::Z};
    for(int i=0; i<7; ++i){
        _listFigures.emplace_back(allTypes.at(i));
    }

    std::random_shuffle(_listFigures.begin(), _listFigures.end(), [](int i){
        srand((int)time(0));
        int randomNumber = (rand() % i);
        return randomNumber;
    });

    _nextFigure = _listFigures.back();
    _listFigures.pop_back();
}

}
