#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "componentmanager.h"
#include <vector>
#include <utility>
#include <exception>
#include "component.h"

/**
 * @brief EntityData contains inormation of an entity
 * first - entity_id
 * second - component_mask
 */

#define entity_id first
#define component_mask second
typedef std::pair<size_t,size_t> EntityData;

class EntityManager
{
    ComponentManager & c_manager;
    std::vector <EntityData> entities;
    size_t next_entity_id;

public:
    EntityManager(ComponentManager & manager);

    /**
     * @brief get_entities chooses entities containing all components from mask
     * @param mask component mask
     * @return chosen entities;
     */
    std::vector<size_t> get_entities(size_t mask);

    size_t create_entity_data();
    EntityData * get_entity_data_ptr(size_t index);

    template< class C >
    Component<C> addComponent(size_t entity_id);

    template< class C >
    Component<C> getComponent(size_t entity_id);
};

template<class C>
Component<C> EntityManager::addComponent(size_t entity_id)
{
    Component<C> temp;
    temp.allocate(c_manager, entity_id, Component<C>::get_id());
    return temp;
}

template<class C>
Component<C> EntityManager::getComponent(size_t entity_id)
{
    void * ptr = c_manager.get_compoenet_ptr(entity_id,Component<C>::get_id());
    Component<C> temp(ptr);
    return temp;
}

#endif // ENTITYMANAGER_H
