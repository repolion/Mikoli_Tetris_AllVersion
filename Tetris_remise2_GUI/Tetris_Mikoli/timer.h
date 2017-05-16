#ifndef TIMER_H
#define TIMER_H
#include <chrono>
#include <QtCore>
#include "observable.h"
#include <QObject>
#include <QTimer>
#include <iostream>

namespace mikoli{

class Timer : public QObject, public Observable {
    Q_OBJECT

private:
    /*!
     * \brief _tStart
     * Start point.
     */
    std::chrono::steady_clock::time_point _tStart;

    /*!
     * \brief _duration
     * Time between the start point and now.
     */
    std::chrono::steady_clock::duration _duration;

    /*!
     * \brief _nbSec
     * A copy of the duration until the pause moment.
     */
    int _nbSec;

public:
    /*!
     * \brief Timer
     * Constructor by default.
     */
    Timer();

    /*!
     * \brief _timer
     * Timer that every second, inform the game to update it's view of the
     * time elapsed.
     */
    QTimer * _timer;

    /*!
     * \brief statutTimeGame
     * \return A pair with the minutes and seconds elapsed since the start
     * of the game.
     */
    std::pair<int, int> statutTimeGame(void);

    /*!
     * \brief getSeconds
     * \return The number of seconds elapsed.
     */
    int getSeconds();

    /*!
     * \brief getMinutes
     * \return The number of minutes elapsed.
     */
    int getMinutes();

    /*!
     * \brief getHours
     * \return The number of hours elapsed.
     */
    int getHours();

    /*!
     * \brief getTotalTime
     * \return The total time elapsed in seconds.
     */
    int getTotalTime();

    /*!
     * \brief play
     * Start the timer.
     */
    void play();

    /*!
     * \brief pause
     * Pause the timer.
     */
    void pause();

    /*!
     * \brief updateDuration
     *  Update the duration attribute
     */
    void updateDuration();

    /*!
     * \brief reset
     * Reset the timer.
     */
    void reset();

public slots:

    /*!
     * \brief MySlot
     * Inform the view to update the time elapsed view.
     */
    void MySlot();
};

}
#endif // TIMER_H
