#ifndef ENTITY_H_
#define ENTITY_H_

#include "component.h"
#include "pool.hpp"
#include <vector>
#include <exception>
#include <sstream>
#include <limits>
#include <functional>

namespace stuff {

    /**
     * @brief The EntityData class - contains component ids data and components mask,
     * used by Entity interface, should not by instantiated explicitly
     */
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

    /**
     * @brief The Entity class unique number binding entity components, interface for component manipulations
     */
    class Entity{
        RawID id{EmptyID};

        static Pools * pools[MAX_COMPONENT_TYPE_ID];

    public:
        Entity();
        Entity(RawID id);
        Entity(const Entity & en);
        Entity& operator=(const Entity & en);

        /**
         * @brief create - allocates memory for new entity and assigns new entity id
         * cannot call create() on existing id, should detach explicitly first
         */
        void create();

        /**
         * @brief detach - unbinds Entity from existing id;
         */
        void detach();

        /**
         * @brief destroy - deallocates entity data and all its components, frees and detaches id
         * @todo free coresponding component data
         */
        void destroy();

        /**
         * @brief isValid checks if entity id coresponds to existing data
         * @return
         */
        bool isValid();

        RawID getRawID();

        /**
         * @brief create component of type T and bind it to entity
         * @tparam T - component type
         * @tparam Args - components constructor argument types
         * @param args - components constructor arguments
         */
        template<class T, class ... Args>
        T& assign(Args&& ... args);

        /**
         *  @brief destroy and unbind component of en entity
         *  @tparam T - components type
         */
        template<class T>
        void unassign();

        /**
         * @brief chech if entity is binded to component if that type
         * @tparam T - component type
         * @return true if is binded, false otherwise
         */
        template<class T>
        bool hasComponent();

        /**
         *  @brief same as hasComponet but for multiple components
         *  @tparam Args - template parameter pack of component types;
         */
        template <class ... Args>
        bool hasComponents();

        /**
         * @brief component access methode
         * @tparam T - component type
         * @return reference to component of entity of given type
         */
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
        pools[t_id] = &(Pool<T>::get());

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
        if(id == stuff::EmptyID)
            throw std::runtime_error("entity non existent");

        stuff::TypeMask mask = Component<T>::getTypeMask();
        EntityData & data = stuff::Pool< EntityData >::get()[id];
        if(!data.valid)
            throw std::runtime_error("entity data invalid");
        return (mask & data.components_mask);
    }

    template <class ... Args>
    inline bool Entity::hasComponents()
    {
        if(id == stuff::EmptyID)
            throw std::runtime_error("entity non existent");

        stuff::TypeMask mask = getComponentsTypeMask<Args...>();
        EntityData & data = stuff::Pool< EntityData >::get()[id];
        if(!data.valid)
            throw std::runtime_error("entity data invalid");
        return ((data.components_mask & mask) == mask);
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
        stuff::Pool<EntityData>::ID it = stuff::Pool<EntityData>::get().begin();
        stuff::Pool<EntityData>::ID it_end = stuff::Pool<EntityData>::get().end();
        for(; it != it_end; ++it ){
            stuff::Entity en(it.getRaw());
            if(en.isValid() && en.hasComponents<Args...>()) //(it->components_mask & mask)==mask))
                func(en);
        }
    }
}

#endif
