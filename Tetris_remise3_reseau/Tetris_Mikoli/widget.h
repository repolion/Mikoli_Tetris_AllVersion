#ifndef WIDGET_H
#define WIDGET_H

#include <string>
#include <iostream>
#include <QKeyEvent>
#include <QWidget>
#include <QMainWindow>
#include <QTimerEvent>
#include <QBasicTimer>

#include "view/sideboard.h"
#include "sounds/soundplayer.h"
#include "view/buttons.h"
#include "view/choiceboard.h"
#include "view/viewboard.h"
#include "net/mythreadClient.h"
#include "observer/observerwidget.h"
#include "model/tetrisgame.h"
#include "net/mysuperthread.h"
#include "view/sideboard.h"

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
    void homeWithOutGameReinit();
    void sendLinesGodMode();
    void setLinesToSend(int);

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
    void serverOff();
    void serverOn();
    void infoServerStatus();
    void godMode();

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    TetrisGame * _game;
    MyThreadClient * _thread=NULL;
    MySuperThread * _superThread=NULL;
    QBasicTimer _timer;
    QBasicTimer _timerFall;
    ViewBoard _viewBoard;
    SideBoard _sideBoard;
    ChoiceBoard _choiceBoard;
    bool _two_Players;
    Buttons _buttons;
    Gamemode _mode;
    TimeController *_timeController;
    Ui::Widget *ui;
    int _tempCpt = 0;
    ushort _port;
    QString _ip;
    bool _isServerOn;
    bool _godMode;
    int _linesToSend;
    SoundPlayer* _deleteTwoLineSound;
    SoundPlayer* _deleteThreeLineSound;
    SoundPlayer* _deleteFourLineSound;

    void keyPressEvent(QKeyEvent * event) override;
    void setTimer(bool isFalling);
    void setTimerConstant(int speed);
    void connectionIp(QString);
    void connectionPort(QString);

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
