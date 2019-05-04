#include "entity.h"

Entity::Entity(EntityManager &manager)
    :data(nullptr), e_manager(manager)
{
}

Entity::Entity(EntityData &data, EntityManager &em)
    :data(nullptr), e_manager(em)
{
    this->data = &data;
}
	
Entity::~Entity()
{}

void Entity::create()
{
    data = &e_manager.create_entity_data();
}
