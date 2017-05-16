#include "timer.h"

namespace mikoli{

using namespace std;

//  constructeur par défaut
Timer::Timer(){
    _nbSec = 0;
    _tStart = std::chrono::steady_clock::now() - std::chrono::seconds(_nbSec);
    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(MySlot()));

    _timer->stop();
}

//  slot qui informe la vue de mettre à jour... sa vue du temps passé
void Timer::MySlot(){
    Notify();
}

//  envoit à la vue le temps passé via une paire, minutes/secondes
std::pair<int, int> Timer::statutTimeGame(void){
    std::pair<int, int> temp;
    temp.first = this->getMinutes();
    temp.second = this->getSeconds();
    return temp;
}

//  met à jour l'attribut _duration du temps passé depuis le début du jeu
void Timer::updateDuration(){
    std::chrono::steady_clock::time_point tEnd = std::chrono::steady_clock::now();
    _duration = tEnd - _tStart;
}

//  démarre le timer
void Timer::play(){
    _tStart = std::chrono::steady_clock::now() - (std::chrono::seconds(_nbSec));
    _timer->start(500);
}

//  met le timer en pause
void Timer::pause(){
    updateDuration();
    _nbSec = std::chrono::duration_cast<std::chrono::seconds>(_duration).count();
    _timer->stop();
}

//  retourne le temps passé en secondes, minutes, heures
int Timer::getSeconds(){
    updateDuration();
    return std::chrono::duration_cast<std::chrono::seconds>(_duration).count()%60;
}

int Timer::getMinutes(){
    updateDuration();
    return std::chrono::duration_cast<std::chrono::minutes>(_duration).count()%60;
}

int Timer::getHours(){
    updateDuration();
    return std::chrono::duration_cast<std::chrono::hours>(_duration).count()%24;
}

//  retourne le temps total passé, en secondes
int Timer::getTotalTime(){
    return std::chrono::duration_cast<std::chrono::seconds>(_duration).count();
}

//  remet le timer à 0
void Timer::reset(){
    _nbSec = 0;
    _tStart = std::chrono::steady_clock::now() - std::chrono::seconds(_nbSec);
}

}
