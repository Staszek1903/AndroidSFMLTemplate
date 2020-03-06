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

bool stuff::Entity::hasComponents(stuff::TypeMask mask)
{
    if(id == stuff::EmptyID)
        throw std::runtime_error("entity non existent");
    EntityData & data = stuff::Pool< EntityData >::get()[id];
    if(!data.valid)
        throw std::runtime_error("entity data invalid");
    return ((data.components_mask & mask) == mask);
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
