#include "system.h"

BaseSystem::BaseSystem(std::string comp_name)
    :component_name(comp_name){;}

BaseSystem::~BaseSystem(){;}

void BaseSystem::addComponent(BaseComponent &comp)
{
    components.push_back(comp.getDataPtr());
}

std::string BaseSystem::getComponentName()
{
    return component_name;
}

int BaseSystem::getId() const
{
    return id;
}

void BaseSystem::setId(int value)
{
    id = value;
}