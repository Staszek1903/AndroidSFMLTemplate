#include "system.h"

System::System()
    :component_mask(0){;}

System::~System(){;}

size_t System::get_mask() const
{
    return component_mask;
}

bool System::has_component_set(size_t mask)
{
    return ((component_mask & mask) == mask);
}
