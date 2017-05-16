#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMainWindow>
#include "tetrisgame.h"
#include <QTimerEvent>
#include <QBasicTimer>
#include <sideboard.h>
#include "soundplayer.h"
#include "buttons.h"
#include "choiceboard.h"
#include "viewboard.h"

namespace Ui {
class Widget;
}

using namespace mikoli;

class TimeController;


/*!
 * \brief Widget class used to display the Game
 */
class Widget :public QWidget{
    friend class TimeController;
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    TetrisGame& getGame();
    SoundPlayer * _startSound;
    SoundPlayer * _moveSound;
private slots:
    void start();
    void quickGame();
    void startMode();
    void setMode();
    void startNewGame();
    void restart();

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    TetrisGame _game;
    QBasicTimer _timer;
    QBasicTimer _timerFall;
    ViewBoard _viewBoard;
    SideBoard _sideBoard;
    ChoiceBoard _choiceBoard;
    Buttons _buttons;
    Gamemode _mode;
    TimeController *_timeController;
    Ui::Widget *ui;
    int _tempCpt = 0;

    void keyPressEvent(QKeyEvent * event) override;
    void setTimer(bool isFalling);
    void setTimerConstant(int speed);

};

class TimeController: public Observer{
    friend class Widget;
private:
    Widget *_w;
    int _speed;
public:
    TimeController();
    TimeController(Widget & w);
    void Update();

};
#endif // WIDGET_H
