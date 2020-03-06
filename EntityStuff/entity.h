#ifndef ENTITY_H_
#define ENTITY_H_

#include "component.h"
#include "pool.hpp"
#include "entitymanager.h"
#include <vector>
#include <exception>
#include <sstream>
#include <limits>
#include <functional>


//TODO assign, unasign exceptions

namespace stuff {

    class EntityData{
    public:
        EntityData();
        EntityData(bool valid);
        ~EntityData();

        EntityData & operator=(const EntityData&) = delete;

        void initIds();

        bool valid{false};
        RawID components_ids[MAX_COMPONENT_TYPE_ID];
        unsigned int components_mask{0};
    };

    class Entity{
        RawID id{EmptyID};

    public:
        void create();

        void destroy();

        bool isValid();

        template<class T, class ... Args>
        T& assign(Args&& ... args);

        template<class T>
        void unassign();

        template<class T>
        bool hasComponent();

        bool hasComponents(TypeMask mask);

        template<class T>
        T& component();
    };

    template<class T, class ... Args>
    T &Entity::assign(Args&& ... args){
        if(id == stuff::EmptyID)
            throw std::runtime_error("entity non existent");

        EntityData & data = stuff::Pool< EntityData >::get()[id];

        if(!data.valid)
            throw std::runtime_error("entity data invalid");

        auto mask = Component<T>::getTypeMask();
        if(mask & data.components_mask)
            throw std::runtime_error("cannot assign same component twice");
        data.components_mask |= mask;

        TypeID t_id = Component<T>::getTypeID();
        RawID c_id = Pool<T>::get().allocate(std::forward<Args>(args) ... ).getRaw();
        data.components_ids[t_id] = c_id;
        return Pool<T>::get()[c_id];
    }

    template<class T>
    void Entity::unassign()
    {
        if(id == stuff::EmptyID)
            throw std::runtime_error("entity non existent");

        EntityData & data = stuff::Pool< EntityData >::get()[id];

        if(!data.valid)
            throw std::runtime_error("entity data invalid");

        auto mask = Component<T>::getTypeMask();
        if(!(mask & data.components_mask))
            throw std::runtime_error("cannot unassign nonexisting component");
        data.components_mask &= ~mask;

        TypeID t_id = Component<T>::getTypeID();
        RawID c_id = data.components_ids[t_id];
        Pool<T>::get().free(c_id);
    }

    template<class T>
    inline bool Entity::hasComponent()
    {
        EntityData & data = stuff::Pool< EntityData >::get()[id];
        if(!data.valid)
            throw std::runtime_error("entity data invalid");
        return (Component<T>::getTypeMask() | data.components_mask);
    }

    template<class T>
    T &stuff::Entity::component()
    {
        if(id == stuff::EmptyID)
            throw std::runtime_error("entity non existent");

        EntityData & data = stuff::Pool< EntityData >::get()[id];

        if(!data.valid)
            throw std::runtime_error("entity data invalid");

        auto mask = Component<T>::getTypeMask();
        if(!(mask & data.components_mask))
            throw std::runtime_error("entity doesnt have this component");

        T& component = Pool<T>::get()[data.components_ids[Component<T>::getTypeID()]];
        return component;
    }

    template <class ... Args >
    void forEntitiesWithComponents(const std::function<void(Entity)> &func){
        TypeMask mask = getComponentsTypeMask<Args...>();
        for(auto & data : Pool<EntityData>::get() ){
            //if(data.valid && (data.components_mask & mask))
             //   func();
        }
    }
}

///**
//	* Wraper for entity data from EntityManager
//	*/
//class Entity
//{
//    size_t entity_data_index;

//    EntityManager & e_manager;

//public:
//	/**
//		* Creates empty object
//		* @param manager - entity manager
//		*/
//    Entity(EntityManager & manager);
//   /**
//   	* Creaates object bound to entity
//   	* @param data_index - index of entity data in entity manager
//   	* @param em - entity manager
//   	*/
//    Entity(size_t data_index, EntityManager & em);
//	virtual ~Entity();
	
//	/**
//		* creates new id for entity within this object
//		*/
//    void create();
	
//	/**
//		* alocates new component of type C and assidns it to this entity
//		* @param args - Component arguments/
//		*/
//       template<class C, class ... Args>
//    Component<C> assign(Args&& ... args);
	
//	/**
//		* unassigns and releases component
//		*/
//	template <class C>
//	void unassign();
	
//	/**
//		* releases entity id and all of its components
//		*/
//	void release();
	
//	/**
//		* @return component wraper for component assigned to this entity
//		*/
//    template< class C >
//    Component<C> component();
//};

//template<typename  C, typename ... Args>
//Component<C> Entity::assign(Args&& ... args)
//{
//    size_t mask = Component<C>::get_mask();
//    EntityData * data = e_manager.get_entity_data_ptr(entity_data_index);

//    if(!data) throw std::runtime_error("inexistent data_index");

//    std::stringstream e_id;
//    e_id<<data->entity_id;

//    if(mask & data->component_mask)
//        throw std::runtime_error(std::string("Entity::assign entity <")+ e_id.str() +
//                                 "> allredy contains component " + typeid(C).name());
//    if(!data->entity_id)
//        throw std::runtime_error("cannot assign component to non existent entity");

//    data->component_mask |= mask;
//    auto component = e_manager.addComponent<C>(data->entity_id);
//    C& c = component.getComponent();
//    c = C(std::forward<Args>(args) ...);

//    return component;
//}

//template <class C>
//void Entity::unassign()
//{
//	size_t mask = Component<C>::get_mask();
//    EntityData * data = e_manager.get_entity_data_ptr(entity_data_index);

//    if(!data) throw std::runtime_error("inexistent data_index");

//    std::stringstream e_id;
//    e_id<<data->entity_id;

//    if(!(mask & data->component_mask))
//        throw std::runtime_error(std::string("Entity::assign entity <")+ e_id.str() +
//                                 "> does not contain  component " + typeid(C).name());
//    if(!data->entity_id)
//        throw std::runtime_error("cannot unassign component from non existent entity");
        
//    e_manager.releaseComponent<C>(data->entity_id);
//    data->component_mask &= ~mask;
//}

//template<class C>
//Component<C> Entity::component()
//{
//    return e_manager.getComponent<C>(e_manager.get_entity_data_ptr(entity_data_index)->entity_id);
//}

#endif
