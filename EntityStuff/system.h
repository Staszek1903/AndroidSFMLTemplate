#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <vector>
#include "component.h"

class System
{
private:

    size_t component_mask;
    std::vector <size_t> entity_ids;

public:
    System();
    System(const System &) = delete;
    virtual ~System();
    virtual void add_entity_id(size_t id);
    virtual void update() = 0;

    size_t get_mask() const;
    bool has_component_set(size_t mask);

protected:
    template<class C>
    void update_mask();
};

template<class C>
void System::update_mask()
{
    component_mask |= Component<C>::get_mask();
}

/*

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
    :BaseSystem (0){}//Component<C>().get_id()){}

template <class C>
System<C>::~System()
{
    for(void * ptr: components)
    {
        Component<C> temp(ptr, EntityStuff::get);
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
*/
#endif
