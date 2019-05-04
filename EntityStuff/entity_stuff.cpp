#include "entity_stuff.h"

EntityStuff::EntityStuff()
    :entity_manager(component_manager), system_manager(entity_manager){}

EntityStuff::~EntityStuff()
{
    system_manager.release();
}

void EntityStuff::update_systems()
{
    Console::get()<<"update systemow\n";
    system_manager.update();
}

ComponentManager &EntityStuff::get_component_menager()
{
    return component_manager;
}

SystemManager & EntityStuff::get_system_manager()
{
    return system_manager;
}

EntityManager & EntityStuff::get_entity_manager()
{
    return entity_manager;
}
