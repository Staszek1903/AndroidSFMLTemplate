#include "event.h"

size_t BaseEvent::next_id = 1;

BaseEvent::BaseEvent() {;}
BaseEvent::~BaseEvent(){;}

size_t BaseEvent::assign_next_id()
{
	current_id = next_id;
	next_id <<= 1;
	return current_id;
}

size_t BaseEvent::get_id()
{
	return current_id;
}
