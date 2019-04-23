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
    int last_id = 0;
    std::map<std::string, int> components_ids;
    std::vector <void *> components;
    std::vector <BaseSystem *> systems;
	
public:
	
	template < class S >
	void addSystem();

    template< class C>
    Component<C> addComponent();

private:
    int get_component_id(BaseComponent& comp);
};

template<class C>
Component<C> EntityStuff::addComponent()
{
    Component<C> temp;
    int id = get_component_id(temp);
    components.push_back(temp.getDataPtr());
    for(auto s: systems)
    {
        if(s->getId() == id)
            s->addComponent(temp);
    }
}

template < class S >
void EntityStuff::addSystem()
{
    auto * s = new S();

    //int id = get_component_id();
    //s->setId(id);
    systems.push_back(s);
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


