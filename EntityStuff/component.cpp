#include "component.h"

stuff::TypeID stuff::getNewComponentTypeID()
{
    static stuff:: TypeID idCounter = 0;
    if(idCounter > stuff::MAX_COMPONENT_TYPE_ID)
        throw std::runtime_error("component type counts exceed MAX_COMPONENT_TYPE_ID<"
                                 +std::to_string(stuff::MAX_COMPONENT_TYPE_ID));
    return idCounter++;
}
