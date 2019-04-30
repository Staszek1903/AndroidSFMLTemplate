#include "system.h"

BaseSystem::BaseSystem(int component_mask)
    :component_mask(component_mask){;}

BaseSystem::~BaseSystem(){;}

void BaseSystem::addComponent(BaseComponent &comp)
{
    components.push_back(comp.getDataPtr());
}

int BaseSystem::get_mask() const
{
    return component_mask;
}