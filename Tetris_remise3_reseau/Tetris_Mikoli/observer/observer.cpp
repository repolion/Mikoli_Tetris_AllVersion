#include "observer.h"
#include "observable.h"

namespace mikoli{

Observer::~Observer(){
    //à chaque observable
    //on indique qu'on supprime l'observateur courant
    const_iterator ite=m_list.end();

    for(iterator itb=m_list.begin();itb!=ite;++itb){
        (*itb)->DelObs(this);
    }
}

void Observer::AddObs( Observable* obs){
    m_list.push_back(obs);
}

void Observer::DelObs(Observable* obs){
    //on retire l'observable
    iterator it= std::find(m_list.begin(),m_list.end(),obs);
    if(it != m_list.end())
        m_list.erase(it);
}

}
