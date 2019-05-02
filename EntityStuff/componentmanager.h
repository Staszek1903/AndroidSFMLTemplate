#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <vector>
#include "componentcontainer.h"

class ComponentManager
{
    std::vector <ComponentContainer *> containers;
public:
    ComponentManager();
    virtual ~ComponentManager();

    /**
     * @brief allocate_id_container
     *  alocates Container for specific component type. Containers index is id of that component
     * @param component_id
     * @param component_size size of data for single component
     */
    void allocate_id_container(size_t component_id, size_t component_size);


    /**
     * @brief allocate_new_component alocates dada for new component instance
     * @param entity_id id for component to be assaned to
     * @param component_id specifies component type
     * @return pointer to allocate component
     */
    void * allocate_new_component(size_t entity_id, size_t component_id);


    /**
     * @brief get_compoenet_ptr
     * @param entity_id entity which component is assignet to
     * @param component_id specifies component type
     * @return pointer to specific component
     */
    void * get_compoenet_ptr(size_t entity_id, size_t component_id);
};

#endif // COMPONENTMANAGER_H
