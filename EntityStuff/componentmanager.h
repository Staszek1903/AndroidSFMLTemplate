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

    void allocate_id_container(size_t id, size_t component_size);
};

#endif // COMPONENTMANAGER_H
