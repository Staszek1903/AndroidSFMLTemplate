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
    if(components_ids.find(name) == components_ids.end())
    {
    	Console::get()<<"next_id: "<<next_id<<"\n";
        components_ids[name]= next_id;
        next_id <<=1;
    }

    return (components_ids.at(name));
}

void EntityStuff::update_systems()
{
	Console::get()<<"update systemow\n";
	for(BaseSystem * sys : systems)
	{
		sys->update();
	}
}

int EntityStuff::get_component_id(BaseComponent & c)
{
	std::string name = c.getClassName();
	if(components_ids.find(name) == components_ids.end()) return 0;
	return components_ids.at(name);
}