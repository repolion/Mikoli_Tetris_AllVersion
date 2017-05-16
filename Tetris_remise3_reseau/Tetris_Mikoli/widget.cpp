#include "widget.h"
#include "ui_widget.h"

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
    _isServerOn = false;
    _linesToSend = 2;

    // sounds
    _deleteTwoLineSound = new SoundPlayer("sounds/twoLines.mp3", false);
    _deleteThreeLineSound = new SoundPlayer("sounds/threeLines.mp3", false);
    _deleteFourLineSound = new SoundPlayer("sounds/fourLines.mp3", false);

    //Add observers
    _game->AddObs(&_viewBoard);
    _game->AddObs(&_sideBoard);
    _game->AddObs(&_choiceBoard);
    _game->AddObs(_timeController);
    _game->AddObsWidget(this);

    //Set background
    QPixmap bkgnd(":/images/image/background.png");
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    //Set Sounds
    _startSound = new SoundPlayer("sounds/start.mp3", false);
    _startSound->setVolume(20);
    _startSound->play();
    _moveSound = new SoundPlayer("sounds/figMove.mp3", false);

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
    case Qt::Key_Backspace:
        if (_godMode && _two_Players) {
            _game->getBoard2().removeLine(1);
            _game->getBoard2().reorganize(1);
            _game->Notify();
        }
        break;
    case Qt::Key_Plus:
        if (_godMode && _two_Players) {
            sendLinesGodMode();
        }
        break;
    case Qt::Key_1:
        if (_godMode && _two_Players) {
            setLinesToSend(2);
        }
        break;
    case Qt::Key_2:
        if (_godMode && _two_Players) {
            setLinesToSend(3);
        }
        break;
    case Qt::Key_3:
        if (_godMode && _two_Players) {
            setLinesToSend(4);
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
        _choiceBoard.getButtonJoin()->setVisible(false);
        _choiceBoard.getButtonQuickGame()->setVisible(false);
        _choiceBoard.getButtonHome()->setVisible(true);
        _choiceBoard.getButtonServerOff()->setVisible(false);
        _choiceBoard.getButtonServerOn()->setVisible(false);
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
        _choiceBoard.getButtonJoin()->setVisible(false);
        _choiceBoard.getButtonServerOff()->setVisible(false);
        _choiceBoard.getButtonServerOn()->setVisible(false);

        if (_isServerOn) {
            _superThread->getServer()->setMode(Gamemode::NONE);
        }

        _thread = new MyThreadClient(_game,&_sideBoard,&_choiceBoard,_port,_ip);
        connect(_thread, SIGNAL(endThread()), this, SLOT(endThread()));
        connect(_thread, SIGNAL(infoServerStatus()), this, SLOT(infoServerStatus()));
    }
}
void Widget::twoPlayers(){

    _buttons.setVisibility(false);

    if(_isServerOn){
        _choiceBoard.getButtonNewGame()->setVisible(true);
        _choiceBoard.getButtonQuickGame()->setVisible(true);
    }else{
        _choiceBoard.getButtonNewGame()->setVisible(false);
        _choiceBoard.getButtonQuickGame()->setVisible(false);
        _choiceBoard.getButtonJoin()->setVisible(true);
        _choiceBoard.getIpDialog()->show();
    }
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
    _choiceBoard.getButtonHome()->setVisible(false);
    _choiceBoard.getButtonJoin()->setVisible(false);
    _choiceBoard.getButtonTwoPlayers()->setVisible(true);
    _choiceBoard.getButtonSinglePlayer()->setVisible(true);
    infoServerStatus();
    _sideBoard.visibleMessage(false);
    _sideBoard.setDisplay();

}

void Widget::home(){
    infoServerStatus();
    _game->startWithMode(Gamemode::NONE,0,true);
    _game->switchPause();
    _game->setIsBegin(false);
    _choiceBoard.getButtonSinglePlayer()->setVisible(true);
    _choiceBoard.getButtonTwoPlayers()->setVisible(true);
    _choiceBoard.getButtonQuickGame()->setVisible(false);
    _choiceBoard.getButtonNewGame()->setVisible(false);
    _choiceBoard.getButtonRestart()->setVisible(false);
    _choiceBoard.getButtonJoin()->setVisible(false);
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
            _choiceBoard.getButtonServerOff()->setVisible(false);
            _choiceBoard.getButtonServerOn()->setVisible(false);
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
            _thread = new MyThreadClient(_game,&_sideBoard,&_choiceBoard,_mode,_choiceBoard.getModeValue(_mode),_port,_ip);
            _choiceBoard.getButtonServerOn()->setVisible(false);
            connect(_thread, SIGNAL(endThread()), this, SLOT(endThread()));
            connect(_thread, SIGNAL(infoServerStatus()), this, SLOT(infoServerStatus()));
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

void Widget::serverOff(){
    homeWithOutGameReinit();
    _isServerOn = true;
    _superThread = new MySuperThread(this);
    _ip="127.0.0.1";
    _port=_superThread->getPort();
    connectionIp("IP: "+_superThread->getIP());
    connectionPort("PORT: "+QString::number(_port));
    _choiceBoard.getButtonServerOn()->setVisible(true);
    _choiceBoard.getButtonServerOff()->setVisible(false);
}

void Widget::serverOn(){
    _superThread->getServer()->sendToAllTread(GameMessage(TypeMessage::QUIT));
    homeWithOutGameReinit();
    _isServerOn = false;
    _superThread->getServer()->close();
    _superThread->exit();
    _superThread = NULL;
    connectionIp("");
    connectionPort("");
    _choiceBoard.getButtonServerOff()->setVisible(true);
    _choiceBoard.getButtonServerOn()->setVisible(false);
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
    if(_isServerOn){
        _superThread->getServer()->sendToAllTread(GameMessage(TypeMessage::QUIT));
    }
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

void Widget::homeWithOutGameReinit(){
    _choiceBoard.getButtonSinglePlayer()->setVisible(true);
    _choiceBoard.getButtonTwoPlayers()->setVisible(true);
    _choiceBoard.getButtonQuickGame()->setVisible(false);
    _choiceBoard.getButtonNewGame()->setVisible(false);
    _choiceBoard.getButtonRestart()->setVisible(false);
    _choiceBoard.getButtonJoin()->setVisible(false);
    _choiceBoard.hide();
    _choiceBoard.getButtonHome()->setVisible(false);
    _sideBoard.visibleMessage(false);
    _sideBoard.setDisplay();
}

void Widget::infoServerStatus(){
    if(_isServerOn){
        _choiceBoard.getButtonServerOn()->setVisible(true);
    }else{
        _choiceBoard.getButtonServerOff()->setVisible(true);
    }
}

void Widget::godMode(){
    _choiceBoard.getButtonGodMode()->setVisible(false);
    QPixmap bkgnd(":/images/image/backgroundi.png");
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    _godMode = true;
}

void Widget::connectionIp(QString ip){
    _sideBoard.setIp(ip);
    _sideBoard.setDisplay();

}
void Widget::connectionPort(QString ip){
    _sideBoard.setPort(ip);
    _sideBoard.setDisplay();
}

void Widget::sendLinesGodMode() {
    srand((int)time(0));
    int randomNumber = (rand() % _game->getBoard().getBoardSize().first + 1);
    std::vector<std::vector<int>> lines;

    for (int i=1; i<=_linesToSend; ++i) {
        std::vector<int> l;
        l.push_back(randomNumber);
        lines.push_back(l);
    }

    switch(_linesToSend){
    case 2: _deleteTwoLineSound->play();
        break;
    case 3: _deleteThreeLineSound->play();
        break;
    case 4: _deleteFourLineSound->play();
        break;
    }

    _thread->sendMessage(GameMessage(TypeMessage::PARAM, lines));
}

void Widget::setLinesToSend(int nb) {
    _linesToSend = nb;
}






