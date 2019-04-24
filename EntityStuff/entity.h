#ifndef ENTITY_H_
#define ENTITY_H_

#include "entity_stuff.h"

class Entity
{
	int component_mask;
	
public:
	Entity(){}
	virtual ~Entity(){}
	
	template<class C>
	Component<C> assign();	
};

template<class C>
Component<C> Entity::assign()
{
	EntityStuff::get().addComponent<C>();
	//Adding bit to component mask;
}

#endif