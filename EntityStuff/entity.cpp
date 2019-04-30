#include "entity.h"

Entity::Entity()
	:component_mask(0)
{
    entity_id = EntityStuff::get().newEntityId();
}
	
Entity::~Entity()
{}
