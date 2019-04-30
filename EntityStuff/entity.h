#ifndef ENTITY_H_
#define ENTITY_H_

#include "entity_stuff.h"
#include <vector>

class Entity
{
    size_t entity_id;
	int component_mask;
    std::vector <void*> components;
	
public:
	Entity();
	virtual ~Entity();
	
	template<class C>
	Component<C> assign();	
};

template<class C>
Component<C> Entity::assign()
{
    auto c = EntityStuff::get().addComponent<C>();
    component_mask |= Component<C>::get_id();
    components.push_back( c.getDataPointer() );
}

#endif
