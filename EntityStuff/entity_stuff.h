#ifndef ENTITYSTUFF_H_
#define ENTITYSTUFF_H_

#include <vector>

#include "../singleton.hpp"
#include "../console.h"
#include "component.h"
#include "system.h"

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
    std::vector <void *> components;
    std::vector <BaseSystem *> systems;
	
public:
	
	template < class S >
	void addSystem();

    template< class C>
    Component<C> addComponent();
    
    void update_systems();
    int get_component_id(BaseComponent & c);

private:
    int get_component_id(const std::string & name);
};

template<class C>
Component<C> EntityStuff::addComponent()
{
    Component<C> temp;
    int id = Component<C>::get_id();
    components.push_back(temp.getDataPtr());
    for(auto s: systems)
    {
        if(s->get_mask() & id)
        {
            s->addComponent(temp);
            break;
        }
    }
    
    Console::get()<<"component  id: " << id <<"\n";
    
    return temp;
}

template < class S >
void EntityStuff::addSystem()
{
    auto * s = new S();
    systems.push_back(s);
    
    
    Console::get()<<"system id: " << s->get_mask() <<"\n";
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