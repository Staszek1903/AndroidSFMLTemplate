#include "eventmanager.h"

Receiver::Receiver()
	:mask(0){;}
Receiver::~Receiver(){;}

size_t Receiver::get_mask()
{
	return mask;
}

EventManager::EventManager(){;}
EventManager::~EventManager()
{
	for(Receiver * p: receivers)
		delete p;
}

void EventManager::addReceiver(Receiver * r)
{
	receivers.push_back(r);
}