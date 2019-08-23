#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include "event.h"
#include "IOStuff/console.h"
#include <vector>
#include <bitset>

/**
	* Reveiver base class 
	* consist of event mask which it 
	* will receive
	*/
class Receiver
{
	size_t mask;
protected:
	template< class E >
	void update_event_mask();
	
public:
	Receiver();
	virtual ~Receiver();
	size_t get_mask();	
	virtual void receive(BaseEvent * ev) =0;
	
	template < class E >
	bool is_type(BaseEvent * ev);
};

class EventManager
{
	std::vector < Receiver * > receivers;
public:
	EventManager();
	~EventManager();
	
	void addReceiver(Receiver * r);
	
	template< class E, class ... Args>
	void emit(Args&&  ... args); 
};

template< class E >
void Receiver::update_event_mask()
{
	mask |= Event<E>::get_id();
	Console::get()<<"receiver mask is "<<mask<<"\n";
}

template < class E >
bool Receiver::is_type(BaseEvent * ev)
{
	return(Event<E>::get_id() == ev->get_id());
}

template<class E, class ... Args>
void EventManager::emit(Args&& ... args)
{
	Console::get() <<"EVENT EMITED\n";
	
	E ev(std::forward<Args>(args) ...);
	
	for(Receiver * p : receivers)
	{
		Console::get()<<"rec msk: "
		<< p->get_mask()
		<<" Ev msk:  "
	   <<Event<E>::get_id()
	   << "  \n";
		if(p->get_mask() | Event<E>::get_id())
		{
			p->receive(&ev);
		}
	}
}
#endif /* EVENTMANAGER_H_ */
