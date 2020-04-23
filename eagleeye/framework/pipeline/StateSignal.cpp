#include "eagleeye/framework/pipeline/StateSignal.h"

namespace eagleeye
{
StateSignal::StateSignal(int ini_state){
    this->m_ini_state = ini_state;
    this->m_state = this->m_ini_state;

    this->m_release_count = 1;
}   

StateSignal::~StateSignal(){
    
}

void StateSignal::setInit(int ini_state){
    this->m_ini_state = ini_state;
}

void StateSignal::copyInfo(AnySignal* sig){
    Superclass::copyInfo(sig);
}

void StateSignal::printUnit(){
    Superclass::printUnit();
}

StateSignal::DataType StateSignal::getData(){
    return this->m_state;
}

void StateSignal::setData(DataType data){
    this->m_state = data;
    modified();
}

void StateSignal::makeempty(bool auto_empty){
    if(auto_empty){
		if(this->m_release_count % this->getOutDegree() != 0){
			this->m_release_count += 1;
			return;
		}
	}

    this->m_state = this->m_ini_state;

    if(auto_empty){
		this->m_release_count = 1;
	}
    modified();
}

bool StateSignal::isempty(){
    return false;
}

void StateSignal::copy(AnySignal* sig){
	if(sig->getSignalCategory() == SIGNAL_CATEGORY_STATE){
		StateSignal* state_sig = (StateSignal*)sig;
		this->setData(state_sig->getData());
	}
}
} // namespace eagleeye