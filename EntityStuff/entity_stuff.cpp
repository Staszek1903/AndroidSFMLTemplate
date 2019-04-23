#include "entity_stuff.h"

EntityStuff::EntityStuff() = default;

EntityStuff::~EntityStuff()
{
	for(auto * s : systems)
	{
		delete s;
    }
}

int EntityStuff::get_component_id(const std::string & name)
{
    if(components_ids.find(name) != components_ids.end())
    {
        components_ids[name]= next_id;
        next_id <<=1;
    }

    return (components_ids[name]);
}