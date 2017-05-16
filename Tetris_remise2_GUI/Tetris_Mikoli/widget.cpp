#include "widget.h"
#include "ui_widget.h"
#include <iostream>
#include <QKeyEvent>
#include "tetrisgame.h"

using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget){
    ui->setupUi(this);

    //Attributes
    _game = TetrisGame(10,20);
    _mode = Gamemode::NONE;
    _viewBoard = ViewBoard(*this,_game);
    _sideBoard =  SideBoard(*this,_game);
    _choiceBoard = ChoiceBoard(*this,_game);
    _timeController = new TimeController(*this);
    _buttons = Buttons(*this);

    //Add observers
    _game.AddObs(&_viewBoard);
    _game.AddObs(&_sideBoard);
    _game.AddObs(&_choiceBoard);
    _game.AddObs(_timeController);

    //Set background
    QPixmap bkgnd(":/images/tryBG.png");
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    //Set Sounds
    _startSound = new SoundPlayer("start.mp3", false);
    _startSound->setVolume(20);
    _startSound->play();
    _moveSound = new SoundPlayer("figMove.mp3", false);

    //Set timer
    _timer.start(1000,this);
}

Widget::~Widget(){
    delete ui;
}

void Widget::setTimer(bool isFalling){

    if(isFalling){
        _timerFall.start(5,this);
    } else {
        _timerFall.stop();
    }
}

void Widget::setTimerConstant(int speed){
    _timer.start(speed, this);
}

void Widget::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_Down:
        if(!_game.isPaused()){
            _moveSound->play();
        }
        _game.move(Direction::DOWN);
        break;
    case Qt::Key_Right:
        if(!_game.isPaused()){
            _moveSound->play();
        }
        _game.move(Direction::RIGHT);
        break;
    case Qt::Key_Left:
        if(!_game.isPaused()){
            _moveSound->play();
        }
        _game.move(Direction::LEFT);
        break;
    case Qt::Key_W:
        _game.rotate(Direction::LEFT);
        break;
    case Qt::Key_X:
        _game.rotate(Direction::RIGHT);
        break;
    case Qt::Key_Space:
        if(_game.isBegin() && !_game.isPaused() && !_game.isGameOver()){
            _game.fallSlow();
        }
        break;
    case Qt::Key_P:
        if(!_game.isGameOver() && _game.isBegin()){
            _game.switchPause();
        }
        break;
    }
}

TetrisGame& Widget::getGame(){
    return _game;
}

void Widget::timerEvent(QTimerEvent *event){
    event->accept();
    if(_game.checkIfIsBlocked() && _tempCpt ==1 ){
        _game.setAutoDown(true);
        _tempCpt=0;
    }else if(_game.checkIfIsBlocked()){
        _game.move(Direction::DOWN);
        ++_tempCpt;}
    else _game.move(Direction::DOWN);
}

void Widget::start(){
    _choiceBoard.hide();
    _game.start();
    _buttons.setVisibility(false);
    _choiceBoard.getButtonRestart()->setVisible(true);
    _choiceBoard.getButtonNewGame()->setVisible(true);
    _choiceBoard.getButtonQuickGame()->setVisible(false);
}

void Widget::quickGame(){
    _choiceBoard.hide();
    _game.startWithMode(Gamemode::NONE,0);
    _buttons.setVisibility(false);
    _choiceBoard.getButtonRestart()->setVisible(true);
    _choiceBoard.getButtonNewGame()->setVisible(true);
    _choiceBoard.getButtonQuickGame()->setVisible(false);
}

void Widget::startMode(){
    if(_mode!=Gamemode::NONE){
        _choiceBoard.getButtonRestart()->setVisible(true);
        _choiceBoard.getButtonNewGame()->setVisible(true);
        _choiceBoard.getButtonQuickGame()->setVisible(false);
        _choiceBoard.hide();
        _buttons.setVisibility(false);
        if(_mode==Gamemode::NBLINES){
            _game.startWithMode(_mode,_choiceBoard.getModeValue(Gamemode::NBLINES));
        }
        if(_mode==Gamemode::SCORE){
            _game.startWithMode(_mode,_choiceBoard.getModeValue(Gamemode::SCORE));
        }
        if(_mode==Gamemode::TIME){
            _game.startWithMode(_mode,_choiceBoard.getModeValue(Gamemode::TIME));
        }
    }
}

void Widget::startNewGame(){
    if(!_game.isPaused() && !_game.isGameOver()){
        _game.switchPause();
    }
    _choiceBoard.getButtonQuickGame()->setVisible(true);
    _choiceBoard.getButtonRestart()->setVisible(false);
    _choiceBoard.getButtonNewGame()->setVisible(false);
    _choiceBoard.showChooseMenu();
}

void Widget::restart(){
    _choiceBoard.getButtonQuickGame()->setVisible(false);
    if(_game.isPaused())_game.switchPause();
    _game.restart();
}

void Widget::setMode(){
    _mode = _choiceBoard.getMode();
}

TimeController::TimeController(Widget & w){
    _w = &w;
}
TimeController::TimeController(){}

void TimeController::Update(){

    _w->setTimer(_w->getGame().getIsFalling());
    if(_w->getGame().getSpeed() != _speed){
        _speed = _w->getGame().getSpeed();
        _w->setTimerConstant(_w->getGame().getSpeed());
    }

}





