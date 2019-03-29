#include "touchbuffer.h"

TouchBuffer * TouchBuffer::instance = nullptr;

TouchBuffer::TouchBuffer()
{

}

void TouchBuffer::emit(const TouchEvent &ev)
{
    current = ev;
    
    for(auto * h : t_handlers)
    	h->handle(ev);
}

void TouchBuffer::emit(const KeyboardEvent & ev)
{
	for(auto * h: k_handlers)
		h->handle(ev);
}

void TouchBuffer::addHandler( TouchHandler & h)
{
	TouchHandler *  ptr = &h; 
	t_handlers.push_back(ptr);
}

void TouchBuffer::addHandler( KeyboardHandler & h)
{
	KeyboardHandler * ptr = &h; 
	k_handlers.push_back(ptr);
}

TouchEvent TouchBuffer::getCurrent()
{
    return current;
}

TouchBuffer &TouchBuffer::get()
{
    if(!instance)
        instance = new TouchBuffer();
    return *instance;
}

void TouchBuffer::release()
{
    if(instance)
    {
        delete instance;
        instance = nullptr;
    }
}

TouchEvent::TouchEvent(int x, int y, int finger, State state)
    :x(x), y(y), finger(finger), state(state)
{}

TouchEvent::TouchEvent()
    :x(0),y(0), finger(0), state(NO_EVENT)
{}