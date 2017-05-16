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

Buttons::Buttons(QWidget & fenetre,bool b){
    //création du boutton start new game
    if(b)_button = new QPushButton("server on", &fenetre);
    else _button = new QPushButton("server off", &fenetre);
    _button->setGeometry(QRect(QPoint(600, 120), QSize(60, 25)));
    _button->setFocusPolicy(Qt::NoFocus);

    if(b){

        _button->setStyleSheet(
                    "background-color: darkGreen;"
                    "border: 1px solid black;"
                    "border-radius: 12px;"
                    "color: lightGray; "
                    "font-size: 12px;"
                    );
    }else{
        _button->setStyleSheet(
                    "background-color: darkRed;"
                    "border: 1px solid black;"
                    "border-radius: 12px;"
                    "color: lightGray; "
                    "font-size: 12px;"
                    );
    }

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
