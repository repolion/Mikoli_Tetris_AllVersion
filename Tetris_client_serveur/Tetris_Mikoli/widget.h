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
#include "threadServer/mythread.h"
#include "observerwidget.h"
#include "ipwindow.h"
#include <string>

namespace Ui {
class Widget;
}

using namespace mikoli;

class TimeController;


/*!
 * \brief Widget class used to display the Game
 */
class Widget :public QWidget,public ObserverWidget{
    friend class TimeController;
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    TetrisGame* getGame();
    SoundPlayer * _startSound;
    SoundPlayer * _moveSound;
    void UpdateWidget(GameMessage);
    void closeEvent(QCloseEvent *event);

private slots:
    void start();
    void quickGame();
    void twoPlayers();
    void singlePlayer();
    void quit();
    void startMode();
    void setMode();
    void startNewGame();
    void restart();
    void home();
    void confirm();
    void endThread();

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    TetrisGame * _game;
    MyThread * _thread=NULL;
    QBasicTimer _timer;
    QBasicTimer _timerFall;
    ViewBoard _viewBoard;
    SideBoard _sideBoard;
    ChoiceBoard _choiceBoard;
    bool _two_Players;
    Buttons _buttons;
    Gamemode _mode;
    IpWindow *_ipWindow;
    TimeController *_timeController;
    Ui::Widget *ui;
    int _tempCpt = 0;
    ushort _port;
    QString _ip;


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
