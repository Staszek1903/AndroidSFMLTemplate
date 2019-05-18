#include "entitymanager.h"

EntityManager::EntityManager(ComponentManager &manager)
    : c_manager(manager), next_entity_id(1)
{
    entities.resize(100);
}

std::vector<size_t> EntityManager::get_entities(size_t mask)
{
    std::vector <size_t> ret;
    for(size_t i=0; i<entities.size(); ++i)
        if( ( entities.at(i).second & mask ) == mask )
            ret.push_back(i);

    return ret;
}

size_t EntityManager::create_entity_data()
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
    return entities.size()-1;
}

EntityData *EntityManager::get_entity_data_ptr(size_t index)
{
    return &(entities.at(index));
}

void EntityManager::realeaseEntity(size_t data_index)
{
	EntityData * data = get_entity_data_ptr(data_index);

    if(!data) throw std::runtime_error("inexistent data_index");

    std::stringstream e_id;
    e_id<<data->entity_id;

    if(!data->entity_id)
        throw std::runtime_error("cannot release non existent entity");

	for(int i=0; i<sizeof(size_t)*8; ++i)
	{
		if(data->component_mask & (1<<i))
			c_manager.release_component(data->entity_id, i);
	}
	
	auto it = entities.begin() + data_index;
	entities.erase(it);
}
	