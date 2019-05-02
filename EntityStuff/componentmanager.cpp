#include "componentmanager.h"

ComponentManager::ComponentManager()
{

}

ComponentManager::~ComponentManager()
{
    for(auto p: containers)
        delete p;
}

void ComponentManager::allocate_id_container(size_t component_id, size_t component_size)
{
    if(containers.size() <= component_id)
    {
        containers.resize(component_id+1);
        containers.at(component_id) = new ComponentContainer(component_size);
    }
}

void * ComponentManager::allocate_new_component(size_t entity_id, size_t component_id)
{
    auto & container = containers.at(component_id);
    return container->addComponent(entity_id);
}

void * ComponentManager::get_compoenet_ptr(size_t entity_id, size_t component_id)
{
    auto & container = containers.at(component_id);
    return container->getComponent(entity_id);
}
