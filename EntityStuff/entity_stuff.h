#ifndef ENTITYSTUFF_H_
#define ENTITYSTUFF_H_

#include <vector>

#include "IOStuff/singleton.hpp"
#include "IOStuff/console.h"
#include "systemmanager.h"
#include "componentmanager.h"
#include "entitymanager.h"
#include "eventmanager.h"
#include <exception>
#include <stdlib.h>

#include <map>



/**
 * @brief The EntityStuff class
 */
class EntityStuff
{

private:
	EventManager event_manager;
    ComponentManager component_manager;
    EntityManager entity_manager;
    SystemManager system_manager;
	
public:
    EntityStuff();
    ~EntityStuff();
	
	template < class S, class ... Args >
    void addSystem(Args && ... args);
    
    void update_systems(double dt);

    ComponentManager & get_component_menager();
    EntityManager & get_entity_manager();
    SystemManager & get_system_manager();
    EventManager & get_event_manager();
};

template < class S, class ... Args >
void EntityStuff::addSystem(Args && ... args)
{
    auto * s = new S(std::forward<Args>(args) ... );
    system_manager.addSystem(s);
}
#endif
