#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include "system.h"
#include "entitymanager.h"
#include <vector>

class SystemManager
{
    std::vector <System *> systems;
    EntityManager & e_manager;
public:
    SystemManager(EntityManager &manager);

    void addSystem(System * s);
    void update();
    void release();
};

#endif // SYSTEMMANAGER_H
