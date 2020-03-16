#include "entity.h"

stuff::Pools * stuff::Entity::pools[MAX_COMPONENT_TYPE_ID];

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

void stuff::Entity::detach()
{
    id = EmptyID;
}

void stuff::Entity::destroy()
{
    if(id == EmptyID)
        throw std::runtime_error("cannot destroy invalid entity");
    EntityData & data = stuff::Pool< EntityData >::get()[id];
    if(!data.valid)
        throw std::runtime_error("entity data invalid");

    for(unsigned i=0; i<MAX_COMPONENT_TYPE_ID; ++i){
        if(data.components_ids[i] != stuff::EmptyID){
            pools[i]->free(data.components_ids[i]);
        }
    }

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
