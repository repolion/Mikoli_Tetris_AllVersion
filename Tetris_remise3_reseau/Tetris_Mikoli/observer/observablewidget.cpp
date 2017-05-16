#include "observablewidget.h"
#include "observerwidget.h"

namespace mikoli{

void ObservableWidget::AddObsWidget( ObserverWidget* obs){
    //on ajoute l'observateur à notre liste
    m_list.push_back(obs);

    //et on lui donne un nouvel objet observé.
    obs->AddObsWidget(this);
}

void ObservableWidget::DelObsWidget(ObserverWidget* obs){
    //même chose que dans Observateur::DelObs
    iterator it= find(m_list.begin(),m_list.end(),obs);
    if(it != m_list.end())
        m_list.erase(it);
}

ObservableWidget::~ObservableWidget(){
    //même chose qu'avec Observateur::~Observateur
    iterator itb=m_list.begin();
    const_iterator ite=m_list.end();

    for(;itb!=ite;++itb){
        (*itb)->DelObsWidget(this);
    }
}

void ObservableWidget::NotifyWidget(GameMessage message){
    //on prévient chaque observateur que l'on change de valeur
    iterator itb=m_list.begin();
    const_iterator ite=m_list.end();

    for(;itb!=ite;++itb){
        (*itb)->UpdateWidget(message);
    }
}

}
