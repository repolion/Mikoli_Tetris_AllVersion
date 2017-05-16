#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "observer.h"
#include "figure.h"
#include <QObject>

namespace mikoli{
/*!
 * \brief The Observable class
 * Interface implemented by the classes that have to be observed
 */
class Observable{

    std::list<Observer*> m_list;

    typedef std::list<Observer*>::iterator iterator;
    typedef std::list<Observer*>::const_iterator const_iterator;

public:
    void AddObs( Observer* obs);
    void DelObs(Observer* obs);
    void Notify(void);
    virtual ~Observable();
};

}
#endif // OBSERVABLE_H
