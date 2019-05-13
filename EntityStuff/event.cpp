#include "event.h"

size_t BaseEvent::next_id = 1;

BaseEvent::BaseEvent(size_t id )
	: current_id(id) {;}
BaseEvent::~BaseEvent(){;}

size_t BaseEvent::assign_next_id()
{
	size_t temp_id = next_id;
	next_id <<= 1;
	return temp_id;
}

size_t BaseEvent::get_id()
{
	return current_id;
}