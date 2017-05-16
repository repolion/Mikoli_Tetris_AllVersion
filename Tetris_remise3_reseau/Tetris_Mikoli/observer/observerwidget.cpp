#include "observerwidget.h"
#include "observablewidget.h"

namespace mikoli{

ObserverWidget::~ObserverWidget(){
    //à chaque observable
    //on indique qu'on supprime l'observateur courant
    const_iterator ite=m_list.end();

    for(iterator itb=m_list.begin();itb!=ite;++itb){
        (*itb)->DelObsWidget(this);
    }
}

void ObserverWidget::AddObsWidget( ObservableWidget* obs){
    m_list.push_back(obs);
}

void ObserverWidget::DelObsWidget(ObservableWidget* obs){
    //on retire l'observable
    iterator it= std::find(m_list.begin(),m_list.end(),obs);
    if(it != m_list.end())
        m_list.erase(it);
}

}
