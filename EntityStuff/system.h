#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <vector>
#include "component.h"

class BaseSystem
{
protected:
    std::vector<void *> components;
    std::string component_name;
    int component_mask;
public:
    BaseSystem(int component_mask);
    BaseSystem(const BaseSystem &) = delete;
    virtual ~BaseSystem();
    virtual void addComponent(BaseComponent & comp);
    virtual void update() = 0;
    int get_mask() const;
};

template <class C>
class System : public BaseSystem
{
public:
    System();
    System(const System & )  = delete;
    virtual ~System();
    void update();
    
protected:
	virtual void update_elem(Component<C> comp) = 0;
};

template <class C>
System<C>::System()
    :BaseSystem (Component<C>().get_id()){}

template <class C>
System<C>::~System()
{
    for(void * ptr: components)
    {
        Component<C> temp(ptr);
        temp.release();
    }
}

template< class C >
void System<C>::update()
{
	for(void * ptr : components)
	{
		Component<C> temp (ptr);
		update_elem(temp);
	}
}

#endif