#ifndef OBSERVABLEWIDGET_H
#define OBSERVABLEWIDGET_H


#include "observerwidget.h"
#include "figure.h"
#include <QObject>
#include "threadServer/gamemessage.h"

namespace mikoli{
/*!
 * \brief The Observable class
 * Interface implemented by the classes that have to be observed
 */
class ObservableWidget{

    std::list<ObserverWidget*> m_list;

    typedef std::list<ObserverWidget*>::iterator iterator;
    typedef std::list<ObserverWidget*>::const_iterator const_iterator;

public:
    void AddObsWidget( ObserverWidget* obs);
    void DelObsWidget(ObserverWidget* obs);
    void NotifyWidget(GameMessage);
    virtual ~ObservableWidget();
};

}

#endif // OBSERVABLEWIDGET_H
