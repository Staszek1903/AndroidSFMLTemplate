#ifndef ENTITY_H_
#define ENTITY_H_

#include "entitymanager.h"
#include <vector>
#include <exception>
#include <sstream>
#include <limits>

class Entity
{
    size_t entity_data_index;

    EntityManager & e_manager;

public:
    Entity(EntityManager & manager);
    Entity(size_t data_index, EntityManager & em);
	virtual ~Entity();
	
    void create();

    template<class C, class ... Args>
    Component<C> assign(Args&& ... args);

    template< class C >
    Component<C> component();
};

template<typename  C, typename ... Args>
Component<C> Entity::assign(Args&& ... args)
{
    size_t mask = Component<C>::get_mask();
    EntityData * data = e_manager.get_entity_data_ptr(entity_data_index);

    if(!data) throw std::runtime_error("inexistent data_index");

    std::stringstream e_id;
    e_id<<data->entity_id;

    if(mask & data->component_mask)
        throw std::runtime_error(std::string("Entity::assign entity <")+ e_id.str() +
                                 "> allredy contains component " + typeid(C).name());
    if(!data->entity_id)
        throw std::runtime_error("cannot assign component to non existent entity");

    data->component_mask |= mask;
    auto component = e_manager.addComponent<C>(data->entity_id);
    C& c = component.getComponent();
    c = C(std::forward<Args>(args) ...);

    return component;
}

template<class C>
Component<C> Entity::component()
{
    return e_manager.getComponent<C>(e_manager.get_entity_data_ptr(entity_data_index)->entity_id);
}

#endif
