#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <stdint.h>
#include <string>

#include "../console.h"
#include <exception>
#include "componentmanager.h"

#define MAX_COMPONENT_ID 31

class BaseComponent
{
protected:
    static size_t base_id;
	
protected:
    uint8_t * data;
    int size;

public:
    BaseComponent();
    BaseComponent(const BaseComponent &);
    BaseComponent & operator= (const BaseComponent &);

    BaseComponent(uint8_t *data, int size);
    virtual ~BaseComponent();
    virtual void * getDataPtr() const;
    virtual int getDataSize() const;
    virtual void release();
};


template <class T>
class Component : public BaseComponent
{
private:
	static int _id;

    ComponentManager & manager;
public:
    Component(ComponentManager & manager);
    Component(void *ptr, ComponentManager & manager);
    Component( const Component<T> & other)
        :BaseComponent(other), manager(other.manager){}
    Component<T> & operator= (const Component<T> & other);
    ~Component();

    T& getComponent();
    
    void assign_id();
    size_t get_mask();
    size_t get_id();
};

template < class T >
int Component <T> ::_id = 0;

template <class T>
void Component<T>::assign_id()
{
    if(!_id)
    {
        if(base_id>MAX_COMPONENT_ID) throw std::runtime_error("run out of ids for components");
        _id = base_id;
        ++base_id;

        Console::get()<<"Componen::_id added: "<<_id<<"\n";
        manager.allocate_id_container(_id,sizeof(T));
    }
}

template <class T>
Component<T>::Component(ComponentManager & manager)
    :BaseComponent(nullptr, sizeof(T)), manager(manager)
{
    assign_id();
	//Console::get()<< "component constructor base id:"<<_id<<"\n";
}

template< class T > 
    Component<T> & Component<T>::operator= (const Component<T> & other)
    {
    	return static_cast <Component<T> > (BaseComponent::operator= (other) );
    }
    
template<class T>
Component<T>::Component(void *ptr, ComponentManager & manager)
    :BaseComponent(static_cast<uint8_t*>(ptr), sizeof(T)), manager(manager)
{
	Console::get()<<"component ptr c-tor\n";
}

template <class T>
Component<T>::~Component()
{;}

template <class T>
T& Component<T>::getComponent()
{
    void * d = static_cast<void*>(data);
    return *(static_cast<T*>(d));
}

template< class T >
size_t Component<T>::get_id()
{
    assign_id();
    return _id;
}

template < class T >
size_t Component<T>::get_mask()
{
    size_t ret = 1<<get_id(manager);
    return ret;
}
#endif
