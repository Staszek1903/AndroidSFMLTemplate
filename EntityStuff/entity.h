#ifndef ENTITY_H_
#define ENTITY_H_

#include "entitymanager.h"
#include <vector>
#include <exception>
#include <sstream>

class Entity
{
    //size_t entity_id;
    //size_t component_mask;
    EntityData * data;

    EntityManager & e_manager;

public:
    Entity(EntityManager & manager);
    Entity(EntityData & data, EntityManager & em);
	virtual ~Entity();
	
    void create();

	template<class C>
    Component<C> assign();

    template< class C >
    Component<C> component();
};

template<class C>
Component<C> Entity::assign()
{
    size_t mask = Component<C>::get_mask();

    std::stringstream e_id;
    e_id<<data->entity_id;

    if(mask & data->component_mask)
        throw std::runtime_error(std::string("Entity::assign entity <")+ e_id.str() +
                                 "> allredy contains component " + typeid(C).name());
    if(!data->entity_id)
        throw std::runtime_error("cannot assign component to non existent entity");

    data->component_mask |= mask;
    return e_manager.addComponent<C>(data->entity_id);
}

template<class C>
Component<C> Entity::component()
{
    return e_manager.getComponent<C>(data->entity_id);
}

#endif
