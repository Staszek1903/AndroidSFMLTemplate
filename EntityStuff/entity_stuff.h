#ifndef ENTITYSTUFF_H_
#define ENTITYSTUFF_H_

#include <vector>

#include "../singleton.hpp"
#include "../console.h"
#include "component.h"
#include "system.h"
#include "componentmanager.h"
#include <exception>
#include <stdlib.h>

#include <map>

/**
 * @brief The EntityStuff class
 */
class EntityStuff : public Singleton<EntityStuff>
{
protected:
	EntityStuff();
	~EntityStuff();
	friend class Singleton<EntityStuff>;

private:

    /**
     * !!!!!!!!!!!!!!!
     * @brief components - zamiast tego
     * robimy vector component geterów
     * każdy komponent getter przychowuje jeden typ komponentu
     * i znajduje sie w wektorze na indeksie rownym Component<T>::get_id()
     * ComponentGetter sam wie jak wybrac component gdy ma podane ID encji;
     */
    ComponentManager component_manager;
    std::vector <void *> components;
    std::vector <BaseSystem *> systems;
    size_t next_entity_id;
	
public:
	
	template < class S >
	void addSystem();

    template< class C>
    Component<C> addComponent(size_t ent_id);
    
    void update_systems();

    size_t newEntityId();

    ComponentManager & get_component_menager();
};

template<class C>
Component<C> EntityStuff::addComponent(size_t ent_id)
{
    Component<C> temp(component_manager);
    size_t comp_id = temp.get_id();

    /*while(comp_id >= containers.size()) containers.push_back(new ComponentGetter<C>());

    auto container = containers.at(comp_id);
    ComponentGetter<C> * getter = static_cast <ComponentGetter<C>*>(container);
    getter->addComponent(temp, ent_id);

    Console::get()<<"component added id: " << comp_id <<"\n";
    */
    temp.release();
    return temp;
}

template < class S >
void EntityStuff::addSystem()
{
    auto * s = new S();
    systems.push_back(s);
    Console::get()<<"system mask: " << s->get_mask() <<"\n";
}

/*
 * clrating entity:
 * struct Entity
 *  c-tor:
 *      ID id = EntityStuff::getID();
 *      EntityStuff::addComponent(C, id),...,...;
 *
 */
#endif
