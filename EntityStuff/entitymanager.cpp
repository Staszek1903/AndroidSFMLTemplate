#include "entitymanager.h"

EntityManager::EntityManager(ComponentManager &manager)
    : c_manager(manager), next_entity_id(1)
{
    entities.resize(100);
}

std::vector<EntityData> EntityManager::get_entities(size_t mask)
{
    std::vector <EntityData> ret;
    for(auto e : entities)
        if( ( e.second & mask ) == mask )
            ret.push_back(e);

    return ret;
}

EntityData & EntityManager::create_entity_data()
{
    size_t id = next_entity_id;
    ++next_entity_id;
    if(!next_entity_id)
        throw std::runtime_error
            (std::string("run out of ids for entities ")+ __FILE__ + __FUNCTION__);

    entities.push_back(EntityData());
    EntityData & data = entities.at(entities.size()-1);
    data.entity_id = id;
    data.component_mask = 0;
    return data;
}
