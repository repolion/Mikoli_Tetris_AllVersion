#include "widget.h"
#include <QApplication>
#include <QtGui>

using namespace mikoli;

int main(int argc, char *argv[]){

    QApplication a(argc, argv);

        Widget w;
        w.setFixedSize(700, 660);
        w.setWindowTitle(QString("Tetris Mikoli"));
        w.show();
        a.exec();

    return (0);
}


