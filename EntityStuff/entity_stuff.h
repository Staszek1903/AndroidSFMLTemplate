#ifndef ENTITYSTUFF_H_
#define ENTITYSTUFF_H_

#include <vector>

#include "../singleton.hpp"
#include "../console.h"
#include "systemmanager.h"
#include "componentmanager.h"
#include "entitymanager.h"
#include <exception>
#include <stdlib.h>

#include <map>



/**
 * @brief The EntityStuff class
 */
class EntityStuff
{

private:
    ComponentManager component_manager;
    EntityManager entity_manager;
    SystemManager system_manager;
	
public:
    EntityStuff();
    ~EntityStuff();
	
	template < class S >
    void addSystem();
    
    void update_systems();

    ComponentManager & get_component_menager();
    EntityManager & get_entity_manager();
    SystemManager & get_system_manager();
};

template < class S >
void EntityStuff::addSystem()
{
    auto * s = new S();
    system_manager.addSystem(s);
}
#endif
