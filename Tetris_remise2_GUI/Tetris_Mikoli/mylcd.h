#ifndef MYLCD_H
#define MYLCD_H

#include <QLCDNumber>

class MyLcd:public QLCDNumber
{
public:
    MyLcd();
    MyLcd(int value);

    void setValue(int value);

private:
   int _i =1;
};

#endif // MYLCD_H
