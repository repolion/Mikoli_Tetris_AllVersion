#include "widget.h"
#include <QApplication>
#include <tetrisexception.h>
#include <QtGui>
#include <viewboard.cpp>

using namespace mikoli;

int main(int argc, char *argv[]){

    QApplication a(argc, argv);

    try{
        Widget w;
        w.setFixedSize(700, 660);
        w.setWindowTitle(QString("TETRIS"));
        w.show();
        a.exec();

    } catch(TetrisException &e){
        std::cout<<e.what()<<std::endl;
    }
    return (0);
}


