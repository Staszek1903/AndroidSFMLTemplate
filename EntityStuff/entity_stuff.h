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
class EntityStuff : public Singleton<EntityStuff>
{
protected:
	EntityStuff();
	~EntityStuff();
	friend class Singleton<EntityStuff>;

private:
    ComponentManager component_manager;
    EntityManager entity_manager;
    SystemManager system_manager;
	
public:
	
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
    Console::get()<<"system mask: " << s->get_mask() <<"\n";
}

/*
 * OGARNAAAC SYSTEMYYYYYYY
 * clrating entity:
 * struct Entity
 *  c-tor:
 *      ID id = EntityStuff::getID();
 *      EntityStuff::addComponent(C, id),...,...;
 *
 */
#endif
