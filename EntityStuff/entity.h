#ifndef ENTITY_H_
#define ENTITY_H_

#include "entity_stuff.h"
#include <vector>
#include <exception>
#include <sstream>

class Entity
{
    size_t entity_id;
    size_t component_mask;

public:
	Entity();
	virtual ~Entity();
	
	template<class C>
	Component<C> assign();	
};

template<class C>
Component<C> Entity::assign()
{
    size_t mask = Component<C>::get_mask();

    std::stringstream e_id;
    e_id<<entity_id;

    if(mask & component_mask)
        throw std::runtime_error(std::string("Entity::assign entity <")+ e_id.str() +
                                 "> allredy contains component " + typeid(C).name());
    if(!entity_id)
        throw std::runtime_error("cannot assign component to non existent entity");

    component_mask |= mask;
    EntityStuff::get().addComponent<C>(entity_id);
}

#endif
