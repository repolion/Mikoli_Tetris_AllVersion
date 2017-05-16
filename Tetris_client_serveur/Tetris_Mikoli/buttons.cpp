#include "buttons.h"

namespace mikoli {


Buttons::Buttons(){}

Buttons::Buttons(QWidget & fenetre){
    //création du boutton start new game
    _button = new QPushButton("Quick Game", &fenetre);
    _button->setGeometry(QRect(QPoint(80, 300), QSize(200, 50)));
    _button->setFocusPolicy(Qt::NoFocus);
    _button->setStyleSheet(
                "background-color: darkRed;"
                "border: 1px solid black;"
                "border-radius: 15px;"
                "color: lightGray; "
                "font-size: 25px;"
                );
    QObject::connect(_button,SIGNAL(clicked()),&fenetre,SLOT(start()));
}

Buttons::Buttons(QWidget & fenetre,int x,int y,int width,int height,const QString title){

    _button = new QPushButton(title, &fenetre);
    _button->setGeometry(QRect(QPoint(x, y), QSize(width, height)));
    _button->setFocusPolicy(Qt::NoFocus);
    _button->setStyleSheet(
                "background-color: darkRed;"
                "border: 1px solid black;"
                "border-radius: 15px;"
                "color: lightGray; "
                "font-size: 25px;"
                );
}

QPushButton *Buttons::getButton(){
    return _button;
}

void Buttons::setVisibility(bool visibility){
    _button->setVisible(visibility);

}

}
