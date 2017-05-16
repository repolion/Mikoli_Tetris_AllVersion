#include "mylcd.h"

MyLcd::MyLcd(){}
MyLcd::MyLcd(int value){
  this->setSegmentStyle(QLCDNumber::Filled);
   this->setFrameStyle(QFrame::NoFrame);

    //  _timeLcd->setNumDigits(8);
    this->setStyleSheet("* { background-color:rgb(0,10,200);}");

    this->setSegmentStyle(QLCDNumber::Filled);
    this->display(value);
}

void MyLcd::setValue(int value){
    display(value);
    repaint();
}
