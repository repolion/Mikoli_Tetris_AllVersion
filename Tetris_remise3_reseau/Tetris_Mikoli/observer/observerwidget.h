#ifndef OBSERVERWIDGET_H
#define OBSERVERWIDGET_H

#include <iostream>
#include <list>
#include <iterator>
#include <vector>
#include <algorithm>

#include "model/block.h"
#include "net/gamemessage.h"

namespace mikoli{

typedef std::list<Block> listBlocks;

class ObservableWidget;

/*!
 * \brief The Observer class
 * Implemented by the class that have to Observe another class(observable)
 */
class ObserverWidget{

protected:
    std::list<ObservableWidget*> m_list;
    typedef std::list<ObservableWidget*>::iterator iterator;
    typedef std::list<ObservableWidget*>::const_iterator const_iterator;
    virtual ~ObserverWidget() = 0;

public:
    virtual void UpdateWidget(GameMessage)=0;

    void AddObsWidget(ObservableWidget* obs);
    void DelObsWidget(ObservableWidget* obs);
};

}

#endif // OBSERVERWIDGET_H
