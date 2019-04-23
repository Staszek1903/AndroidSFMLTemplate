#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <vector>
#include "component.h"

class BaseSystem
{
protected:
    std::vector<void *> components;
    std::string component_name;
    int id;
public:
    BaseSystem(std::string comp_name);
    virtual ~BaseSystem();
    virtual void addComponent(BaseComponent & comp);
    virtual void update() = 0;
    virtual std::string getComponentName();
    int getId() const;
    void setId(int value);
};

template <class C>
class System : public BaseSystem
{
public:
    System();
    virtual ~System();
    virtual void update() = 0;
};

template <class C>
System<C>::System()
    :BaseSystem (typeid (C).name()){}

template <class C>
System<C>::~System()
{
    for(void * ptr: components)
    {
        Component<C> temp(ptr);
        temp.release();
    }

}

#endif
