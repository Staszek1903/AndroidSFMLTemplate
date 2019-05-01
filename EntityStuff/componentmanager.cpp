#include "componentmanager.h"

ComponentManager::ComponentManager()
{

}

ComponentManager::~ComponentManager()
{
    for(auto p: containers)
        delete p;
}

void ComponentManager::allocate_id_container(size_t id, size_t component_size)
{
    if(containers.size() <= id) containers.resize(id+1);
    containers.at(id) = new ComponentContainer(component_size);
}
