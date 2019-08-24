#ifndef EVENT_H_
#define EVENT_H_

#include <cstdlib>
#include "../IOStuff/console.h"

/**
	* Base Event base class of event
	* assigning next id
	*/
class BaseEvent
{
private:
	static size_t next_id;
	size_t  current_id;
protected:
	/**
		* returning next free id
		* @return free id
		*/
	static size_t assign_next_id();
	
public:
	/**
		* c-tor
		* @param id - id to be assigned to event 
		* type
		*/
	BaseEvent(size_t id);
	virtual ~BaseEvent();
	
	size_t get_id();
};

template< class E >
class Event : public BaseEvent
{
	static size_t id;
public:
	Event();
	Event(const BaseEvent &){};
	virtual ~Event();
	static size_t get_id(); 
	
};

template< class E >
size_t Event<E>::id = 0;

template< class E >
Event<E>::Event()
	: BaseEvent((id)?id:assign_next_id())
{
}

template< class E >
Event<E>::~Event(){}

template <class E>
size_t Event<E>::get_id() 
{
	if(!id) id = assign_next_id();
	return id;
}
#endif /* EVENT_H_ */
