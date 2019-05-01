#ifndef ENTITYSTUFF_H_
#define ENTITYSTUFF_H_

#include <vector>

#include "../singleton.hpp"
#include "../console.h"
#include "component.h"
#include "system.h"
#include "componentcontainer.h"
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
    std::vector < ComponentContainer > containers;
    std::vector <void *> components;
    std::vector <BaseSystem *> systems;
    size_t next_entity_id;
	
public:
	
	template < class S >
	void addSystem();

    template< class C>
    Component<C> addComponent();
    
    void update_systems();

    size_t newEntityId();
};

template<class C>
Component<C> EntityStuff::addComponent()
{
    Component<C> temp;
    size_t id = Component<C>::get_id();
    
    while(id <= containers.size()) containers.push_back(ComponentContainer( sizeof(C) ));
    
    
    
    Console::get()<<"component added id: " << id <<"\n";
    
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