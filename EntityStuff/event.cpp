#include "event.hpp"

std::vector< stuff::Event* >  stuff::Event::instances_ptr;

void stuff::Event::resetHandlers()
{
    for(Event * ptr : instances_ptr)
        ptr->reset();
}
