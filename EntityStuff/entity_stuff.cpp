#include "entity_stuff.h"

EntityStuff::EntityStuff() = default;

EntityStuff::~EntityStuff()
{
	for(auto * s : systems)
	{
		delete s;
    }
}

int EntityStuff::get_component_id(BaseComponent &comp)
{
    auto name = comp.getClassName();
    if(components_ids.find(name) != components_ids.end())
    {
        last_id <<= 1;
        components_ids.at(name) = last_id;
    }

    return (components_ids.at(name));
}
