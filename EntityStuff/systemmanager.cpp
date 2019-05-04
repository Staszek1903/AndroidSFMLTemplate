#include "systemmanager.h"

SystemManager::SystemManager(EntityManager &manager)
    : e_manager(manager)
{

}

void SystemManager::addSystem(System * s)
{
    systems.push_back(s);
}

void SystemManager::update()
{
    for(auto * s: systems)
    {
        s->update(e_manager);
    }
}

void SystemManager::release()
{
    for( auto * s : systems)
    {
        delete s;
    }
}
