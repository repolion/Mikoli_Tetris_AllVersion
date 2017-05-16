#include "choiceboard.h"
#include "QVBoxLayout"
#include <QPainter>
#include <QGroupBox>
#include "buttons.h"

namespace mikoli {

ChoiceBoard::ChoiceBoard(){}

ChoiceBoard::ChoiceBoard(QWidget & fenetre, TetrisGame & game){

    _game = &game;

    //QPalette blanche utilisée pour l'affichage dans les menus lattéraux
    QPalette* palette = new QPalette();
    palette->setColor(QPalette::Foreground,Qt::white);

    //Groupbox contenant les "QradioButtons" pour le choix des modes de jeux
    _groupbox = new QGroupBox("Playing modes",&fenetre);
    _groupbox->setPalette(*palette);

    //Radios buttons
    _radio1 = new QRadioButton("Score to Reach");
    _radio2 = new QRadioButton("Number of Lines");
    _radio3 = new QRadioButton("Survival time");

    //Affecte la paleette au QRadioButtons
    _radio1->setPalette(*palette);
    _radio2->setPalette(*palette);
    _radio3->setPalette(*palette);

    //Connexion des boutons radios à la méthode qui set le mode choisit
    QObject::connect(_radio1,SIGNAL(clicked()),&fenetre,SLOT(setMode()));
    QObject::connect(_radio2,SIGNAL(clicked()),&fenetre,SLOT(setMode()));
    QObject::connect(_radio3,SIGNAL(clicked()),&fenetre,SLOT(setMode()));

    //Spin boxes (choix de la valeur de l'attribut goal)
    _scoreToReach = new QSpinBox;
    _scoreToReach->setRange(10000, 100000);
    _scoreToReach->setSingleStep(1);
    _scoreToReach->setPrefix("Pts ");
    _scoreToReach->setValue(5000);

    _nbLines = new QSpinBox;
    _nbLines->setRange(10, 250);
    _nbLines->setSingleStep(1);
    _nbLines->setPrefix("Lines ");
    _nbLines->setValue(75);

    _timeUp = new QSpinBox;
    _timeUp->setRange(1,20);
    _timeUp->setSingleStep(1);
    _timeUp->setPrefix("Min ");
    _timeUp->setValue(3);

    //Ajout des QRadioButtons et spinboxes à une VBox
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(_radio1);
    vbox->addWidget(_scoreToReach);
    vbox->addWidget(_radio2);
    vbox->addWidget(_nbLines);
    vbox->addWidget(_radio3);
    vbox->addWidget(_timeUp);

    _groupbox->setLayout(vbox);
    _groupbox->move(QPoint(365,350));

    //Création d'Objets Buttons contenant un bouton configuré
    Buttons butStart = Buttons(fenetre,526,475,100,50,QString("Start"));
    Buttons butRestart = Buttons(fenetre,376,300,100,50,QString("Restart"));
    Buttons butNewGame = Buttons(fenetre,485,300,170,50,QString("New Game"));
    Buttons butQuickGame = Buttons(fenetre,485,300,170,50,QString("Quick Game"));

    //Initialisation des boutons
    _buttonStart = butStart.getButton();
    _buttonRestart = butRestart.getButton();
    _buttonNewGame = butNewGame.getButton();
    _buttonQuickGame = butQuickGame.getButton();

    //Set la visibilité requise des boutons
    butRestart.setVisibility(false);
    butNewGame.setVisibility(false);
    butQuickGame.setVisibility(false);

    //Connexion des boutons au slots
    QObject::connect(_buttonStart,SIGNAL(clicked()),&fenetre,SLOT(startMode()));
    QObject::connect(_buttonRestart,SIGNAL(clicked()),&fenetre,SLOT(restart()));
    QObject::connect(_buttonNewGame,SIGNAL(clicked()),&fenetre,SLOT(startNewGame()));
    QObject::connect(_buttonQuickGame,SIGNAL(clicked()),&fenetre,SLOT(quickGame()));

}

//cache le menu de droite avec les choix de nouveaux jeux
void ChoiceBoard::hide(){
    _scoreToReach->clearFocus();
    _nbLines->clearFocus();
    _timeUp->clearFocus();
    _radio1->clearFocus();
    _radio2->clearFocus();
    _radio3->clearFocus();
    _buttonStart->setVisible(false);
    _groupbox->clearFocus();
    _groupbox->setVisible(false);
    _buttonQuickGame->setVisible(false);
}

//montre le menu de droite avec les choix de nouveaux jeux
void ChoiceBoard::show(){
    _buttonQuickGame->setVisible(false);
    _buttonRestart->setVisible(false);
    _buttonNewGame->setVisible(false);
    showChooseMenu();
}

//montre le menu de droite
void ChoiceBoard::showChooseMenu(){
    _buttonStart->setVisible(true);
    _groupbox->setVisible(true);
}

//permet de récupérer le mode de jeu des "choices box"
Gamemode ChoiceBoard::getMode(){
    if(_radio1->isChecked())return Gamemode::SCORE;
    else if(_radio2->isChecked())return Gamemode::NBLINES;
    else if (_radio3->isChecked())return Gamemode::TIME;
    else return Gamemode::NONE;
}

//permet de récupérer la valeur de l'attibuts des "spin boxes"
int ChoiceBoard::getModeValue(Gamemode mode){
    if(mode==Gamemode::SCORE)return _scoreToReach->value();
    if(mode==Gamemode::NBLINES)return _nbLines->value();
    if(mode==Gamemode::TIME)return _timeUp->value();
    else return 0;
}

QPushButton *ChoiceBoard::getButtonRestart(){
    return _buttonRestart;
}

QPushButton *ChoiceBoard::getButtonNewGame(){
    return _buttonNewGame;
}

QPushButton *ChoiceBoard::getButtonQuickGame(){
    return _buttonQuickGame;
}

//lorsque le jeu est en pause affiche les boutons "restart" et "new game"
void ChoiceBoard::Update(){
    if(!_game->isPaused()){
        _buttonRestart->setVisible(true);
        _buttonNewGame->setVisible(true);
        hide();
    }
}

}


