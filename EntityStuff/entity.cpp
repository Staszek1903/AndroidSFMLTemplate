#include "entity.h"

Entity::Entity(EntityManager &manager)
    :entity_data_index(std::numeric_limits<size_t>::max()), e_manager(manager)
{

}

Entity::Entity(size_t data_index, EntityManager &em)
    :entity_data_index(std::numeric_limits<size_t>::max()), e_manager(em)
{
    entity_data_index = data_index;
}
	
Entity::~Entity()
{}

void Entity::create()
{
    entity_data_index = e_manager.create_entity_data();
}
