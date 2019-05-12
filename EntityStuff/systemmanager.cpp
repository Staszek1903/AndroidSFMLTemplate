#include "systemmanager.h"

SystemManager::SystemManager(EntityManager &manager , EventManager & vm)
    : e_manager(manager), ev_manager(vm)
{

}

void SystemManager::addSystem(System * s)
{
    systems.push_back(s);
}

void SystemManager::update(double dt)
{
    for(auto * s: systems)
    {
        s->update(e_manager, ev_manager, dt);
    }
}

void SystemManager::release()
{
    for( auto * s : systems)
    {
        delete s;
    }
}