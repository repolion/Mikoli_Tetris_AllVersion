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
    _game = new TetrisGame(10,20);
    _mode = Gamemode::NONE;
    _viewBoard = ViewBoard(*this,_game);
    _sideBoard =  SideBoard(*this,_game);
    _choiceBoard = ChoiceBoard(*this,_game);
    _timeController = new TimeController(*this);
    _buttons = Buttons(*this);
    _buttons.setVisibility(false);

    //Add observers
    _game->AddObs(&_viewBoard);
    _game->AddObs(&_sideBoard);
    _game->AddObs(&_choiceBoard);
    _game->AddObs(_timeController);
    _game->AddObsWidget(this);

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
        if(!_game->isPaused()){
            _moveSound->play();
        }
        _game->move(Direction::DOWN);
        break;
    case Qt::Key_Right:
        if(!_game->isPaused()){
            _moveSound->play();
        }
        _game->move(Direction::RIGHT);
        break;
    case Qt::Key_Left:
        if(!_game->isPaused()){
            _moveSound->play();
        }
        _game->move(Direction::LEFT);
        break;
    case Qt::Key_W:
        _game->rotate(Direction::LEFT);
        break;
    case Qt::Key_X:
        _game->rotate(Direction::RIGHT);
        break;
    case Qt::Key_Space:
        if(_game->isBegin() && !_game->isPaused() && !_game->isGameOver()){
            _game->fallSlow();
        }
        break;
    case Qt::Key_P:
        if(!_game->isGameOver() && _game->isBegin() && _game->isSinglePlayer()
                ){
            _game->switchPause();
        }
        break;
    }
}

TetrisGame* Widget::getGame(){
    return _game;
}

void Widget::timerEvent(QTimerEvent *event){
    event->accept();
    if(_game->checkIfIsBlocked() && _tempCpt ==1 ){
        _game->setAutoDown(true);
        _tempCpt=0;
    }else if(_game->checkIfIsBlocked()){
        _game->move(Direction::DOWN);
        ++_tempCpt;}
    else _game->move(Direction::DOWN);
}

void Widget::start(){
    _choiceBoard.hide();
    _game->start();
    _buttons.setVisibility(false);
    _choiceBoard.getButtonRestart()->setVisible(true);
    _choiceBoard.getButtonNewGame()->setVisible(false);
    _choiceBoard.getButtonHome()->setVisible(true);
    _choiceBoard.getButtonQuickGame()->setVisible(false);
    if(!_two_Players){
        _choiceBoard.getButtonQuit()->setVisible(false);
    }

}

void Widget::quickGame(){
    if(!_two_Players){

        _choiceBoard.hide();
        _game->startWithMode(Gamemode::NONE,0,true);
        _buttons.setVisibility(false);
        _choiceBoard.getButtonRestart()->setVisible(true);
        _choiceBoard.getButtonNewGame()->setVisible(false);

        _choiceBoard.getButtonQuickGame()->setVisible(false);
        _choiceBoard.getButtonHome()->setVisible(true);
    }
    else{
        _choiceBoard.hide();
        _sideBoard.setMessage("Waiting for a player");
        _sideBoard.visibleMessage(true);
        _sideBoard.setDisplay();
        _choiceBoard.getButtonRestart()->setVisible(false);
        _choiceBoard.getButtonQuit()->setVisible(true);
        _choiceBoard.getButtonNewGame()->setVisible(false);
        _choiceBoard.getButtonHome()->setVisible(false);

        _thread = new MyThread(_game,&_sideBoard,&_choiceBoard,_port,_ip);
        connect(_thread, SIGNAL(endThread()), this, SLOT(endThread()));
    }
}
void Widget::twoPlayers(){


    _buttons.setVisibility(false);

    _choiceBoard.getButtonNewGame()->setVisible(true);
    _choiceBoard.getButtonQuickGame()->setVisible(true);

    _choiceBoard.getButtonTwoPlayers()->setVisible(false);
    _choiceBoard.getButtonSinglePlayer()->setVisible(false);
    _two_Players = true;
    _choiceBoard.getButtonHome()->setVisible(true);
}

void Widget::singlePlayer(){
    _two_Players = false;
    _choiceBoard.getButtonQuickGame()->setVisible(true);
    _choiceBoard.getButtonNewGame()->setVisible(true);
    _choiceBoard.getButtonSinglePlayer()->setVisible(false);
    _choiceBoard.getButtonTwoPlayers()->setVisible(false);
    _choiceBoard.getButtonHome()->setVisible(true);

}

void Widget::quit(){
    _choiceBoard.hide();
    _game->startWithMode(Gamemode::NONE,0,true);
    _game->switchPause();
    _game->setIsBegin(false);

    //stop threadServer
    _thread->sendMessage(GameMessage(TypeMessage::QUIT));
    endThread();

    _choiceBoard.getButtonQuit()->setVisible(false);
    _choiceBoard.getButtonQuickGame()->setVisible(false);
    _choiceBoard.getButtonRestart()->setVisible(false);
    _choiceBoard.getButtonNewGame()->setVisible(false);
    _choiceBoard.getButtonHome()->setVisible(false
                                             );
    _choiceBoard.getButtonTwoPlayers()->setVisible(true);
    _choiceBoard.getButtonSinglePlayer()->setVisible(true);

    _sideBoard.visibleMessage(false);
    _sideBoard.setDisplay();

}

void Widget::home(){
    _game->startWithMode(Gamemode::NONE,0,true);
    _game->switchPause();
    _game->setIsBegin(false);
    _choiceBoard.getButtonSinglePlayer()->setVisible(true);
    _choiceBoard.getButtonTwoPlayers()->setVisible(true);
    _choiceBoard.getButtonQuickGame()->setVisible(false);
    _choiceBoard.getButtonNewGame()->setVisible(false);
    _choiceBoard.getButtonRestart()->setVisible(false);
    _choiceBoard.hide();
    _choiceBoard.getButtonHome()->setVisible(false);
    _sideBoard.visibleMessage(false);
    _sideBoard.setDisplay();
}

void Widget::startMode(){
    if(_mode!=Gamemode::NONE){
        _choiceBoard.getButtonHome()->setVisible(false);
        _choiceBoard.getButtonRestart()->setVisible(true);
        _choiceBoard.getButtonNewGame()->setVisible(false);
        _choiceBoard.getButtonQuickGame()->setVisible(false);
        if(_two_Players){
            _choiceBoard.getButtonQuit()->setVisible(true);
            _choiceBoard.getButtonRestart()->setVisible(false);
            _sideBoard.setMessage("Waiting for a player");
            _sideBoard.visibleMessage(true);
            _sideBoard.setDisplay();
        }
        _choiceBoard.hide();
        _buttons.setVisibility(false);
        if(!_two_Players){
            if(_mode==Gamemode::NBLINES){
                _game->startWithMode(_mode,_choiceBoard.getModeValue(Gamemode::NBLINES),true);
            }
            if(_mode==Gamemode::SCORE){
                _game->startWithMode(_mode,_choiceBoard.getModeValue(Gamemode::SCORE),true);
            }
            if(_mode==Gamemode::TIME){
                _game->startWithMode(_mode,_choiceBoard.getModeValue(Gamemode::TIME),true);
            }
        }else{
            _thread = new MyThread(_game,&_sideBoard,&_choiceBoard,_mode,_choiceBoard.getModeValue(_mode),_port,_ip);
             connect(_thread, SIGNAL(endThread()), this, SLOT(endThread()));
        }
    }
}

void Widget::startNewGame(){
    if(!_game->isPaused() && !_game->isGameOver()){
        _game->switchPause();
    }
    _choiceBoard.getButtonQuickGame()->setVisible(false);
    _choiceBoard.getButtonRestart()->setVisible(false);
    _choiceBoard.getButtonNewGame()->setVisible(false);
    _choiceBoard.showChooseMenu();
    _choiceBoard.getButtonTwoPlayers()->setVisible(false);
}

void Widget::restart(){
    if(!_game->isSinglePlayer()){
        _thread->sendMessage(GameMessage(TypeMessage::RESTART));
        _choiceBoard.getButtonRestart()->setVisible(false);
    }
    _choiceBoard.getButtonQuickGame()->setVisible(false);
    if(_game->isPaused())_game->switchPause();
    _game->restart();
}

void Widget::setMode(){
    _mode = _choiceBoard.getMode();
}

TimeController::TimeController(Widget & w){
    _w = &w;
}
TimeController::TimeController(){}

void TimeController::Update(){

    _w->setTimer(_w->getGame()->getIsFalling());
    if(_w->getGame()->getSpeed() != _speed){
        _speed = _w->getGame()->getSpeed();
        _w->setTimerConstant(_w->getGame()->getSpeed());
    }

}

void Widget::UpdateWidget(GameMessage message){
    _thread->sendMessage(message);
}

void Widget::closeEvent(QCloseEvent *event){
    std::cout<<"do something when closing"<<std::endl;
    if(_thread!=NULL){
        _thread->sendMessage(GameMessage(TypeMessage::QUIT));
    }
}

void Widget::confirm(){
    _port=_choiceBoard.getIpDialog()->getPort().toUShort();
    _ip=_choiceBoard.getIpDialog()->getIp();
    _choiceBoard.getIpDialog()->hide();
}

void Widget::endThread(){
    _thread->getSocket()->close();
    _thread->exit();
    _thread=NULL;
}





