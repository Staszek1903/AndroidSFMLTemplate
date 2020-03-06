//#ifndef ENTITYMANAGER_H
//#define ENTITYMANAGER_H

//#include "componentmanager.h"
//#include <vector>
//#include <utility>
//#include <exception>
//#include "component.h"

///**
// * @brief EntityData contains inormation of an entity
// * first - entity_id
// * second - component_mask
// */

//#define entity_id first
//#define component_mask second
//typedef std::pair<size_t,size_t> EntityData;

//class EntityManager
//{
//    ComponentManager & c_manager;
//    std::vector <EntityData> entities;
//    size_t next_entity_id;

//public:
//    EntityManager(ComponentManager & manager);

//    /**
//     * @brief get_entities chooses entities containing all components from mask
//     * @param mask component mask
//     * @return chosen entities;
//     */
//    std::vector<size_t> get_entities(size_t mask);
	
//	/**
//		* creates ne entity_entry
//		* @return entity data index
//		*/
//    size_t create_entity_data();
    
//    /**
//    	* return pointer to entity data entry at coresponding index
//    	* @param idex - entity data index
//    	*/
//    EntityData * get_entity_data_ptr(size_t index);
	
//	/**
//		* deletes entity data entry and releases all of its components
//		* @param data_index - entity_data index
//		*/
//	void realeaseEntity(size_t data_index);
	
//	/**
//		* alocates new component bound to entity
//		* @param entity_id
//		* @return component wraper
//		*/
//    template< class C >
//    Component<C> addComponent(size_t entity_id);
	
//	/**
//		* releases component
//		* @param entity_data - entity data index
//		*/
//    template< class C>
//    void releaseComponent(size_t entity_data);
	
//	/**
//		* @param entity_id
//		* @return Component wraper
//		*/
//    template< class C >
//    Component<C> getComponent(size_t entity_id);
//};

//template<class C>
//Component<C> EntityManager::addComponent(size_t entity_id)
//{
//    Component<C> temp;
//    temp.allocate(c_manager, entity_id, Component<C>::get_id());
//    return temp;
//}

//template< class C>
//void EntityManager::releaseComponent(size_t entity_id)
//{
//	c_manager.release_component(entity_id, Component<C>::get_id());
//}
  

//template<class C>
//Component<C> EntityManager::getComponent(size_t entity_id)
//{
//    void * ptr = c_manager.get_compoenet_ptr(entity_id,Component<C>::get_id());
//    Component<C> temp(ptr);
//    return temp;
//}

//#endif // ENTITYMANAGER_H
