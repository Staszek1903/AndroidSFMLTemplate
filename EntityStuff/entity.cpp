#include "entity.h"

//Entity::Entity(EntityManager &manager)
//    :entity_data_index(std::numeric_limits<size_t>::max()), e_manager(manager)
//{

//}

//Entity::Entity(size_t data_index, EntityManager &em)
//    :entity_data_index(std::numeric_limits<size_t>::max()), e_manager(em)
//{
//    entity_data_index = data_index;
//}
	
//Entity::~Entity()
//{}

//void Entity::create()
//{
//    entity_data_index = e_manager.create_entity_data();
//}

//void Entity::release()
//{
//    e_manager.realeaseEntity(entity_data_index);
//}

stuff::Entity::Entity(){}

stuff::Entity::Entity(stuff::RawID id)
    :id(id)
{}

stuff::Entity::Entity(const stuff::Entity &en)
    :id(en.id)
{}

void stuff::Entity::create()
{
    if(id != EmptyID)
        throw std::runtime_error("cannot create entity twice");
    id = stuff::Pool< stuff::EntityData >::get().allocate(true).getRaw();
}

void stuff::Entity::destroy()
{
    if(id == EmptyID)
        throw std::runtime_error("cannot destroy invalid entity");
    stuff::Pool< stuff::EntityData >::get().free(id);
}

bool stuff::Entity::isValid()
{
    if(id == stuff::EmptyID)
        throw std::runtime_error("entity non existent");
    EntityData & data = stuff::Pool< EntityData >::get()[id];
    return data.valid;
}

stuff::RawID stuff::Entity::getRawID()
{
    return id;
}

stuff::EntityData::EntityData()
{
    initIds();
}

stuff::EntityData::EntityData(bool valid)
    :valid(valid)
{
    initIds();
}

stuff::EntityData::~EntityData()
{
    valid = false;
    components_mask = 0;
}

void stuff::EntityData::initIds()
{
    for(unsigned i=0; i< stuff::MAX_COMPONENT_TYPE_ID; ++i)
        components_ids[i] = stuff::EmptyID;
}
