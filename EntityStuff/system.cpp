#include "system.h"

System::System()
    :component_mask(0){;}

System::~System(){;}

void System::add_entity_id(size_t id)
{
    entity_ids.push_back(id);
}

size_t System::get_mask() const
{
    return component_mask;
}

bool System::has_component_set(size_t mask)
{
    return ((component_mask & mask) == mask);
}
