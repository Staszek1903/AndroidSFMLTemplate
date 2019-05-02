#include "entity_stuff.h"

EntityStuff::EntityStuff()
    :  next_entity_id(1) {}

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
    for(System * sys : systems)
	{
		sys->update();
    }
}

size_t EntityStuff::newEntityId()
{
    size_t temp = next_entity_id;
    ++next_entity_id;
    if(!next_entity_id)
        throw std::runtime_error
            (std::string("run out of ids for entities ")+ __FILE__ + __FUNCTION__);

    return temp;
}

ComponentManager &EntityStuff::get_component_menager()
{
    return component_manager;
}
