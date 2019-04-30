#include "entity_stuff.h"

EntityStuff::EntityStuff() = default;

EntityStuff::~EntityStuff()
{
	for(auto * s : systems)
	{
		delete s;
    }
}

void EntityStuff::update_systems()
{
	Console::get()<<"update systemow\n";
	for(BaseSystem * sys : systems)
	{
		sys->update();
	}
}