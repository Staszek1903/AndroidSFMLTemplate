#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <stdint.h>
#include <string>

#include "componentmanager.h"
#include "../console.h"
#include <exception>

#define MAX_COMPONENT_ID 31

class BaseComponent
{
protected:
    static size_t base_id;
	
protected:
    uint8_t * data;
    size_t size;

public:
    BaseComponent();
    BaseComponent(const BaseComponent &);
    BaseComponent & operator= (const BaseComponent &);

    BaseComponent(uint8_t *data, size_t size);
    virtual ~BaseComponent();
    virtual void * getDataPtr() const;
    virtual size_t getDataSize() const;
    virtual void release();

    void allocate(ComponentManager & manager, size_t entity_id, size_t component_id);
};


template <class T>
class Component : public BaseComponent
{
private:
	static int _id;

public:
    Component();
    Component(void *ptr);
    Component( const Component<T> & other)
        :BaseComponent(other){}
    Component<T> & operator= (const Component<T> & other);
    ~Component();

    T& getComponent();
	T* operator->();
	T& operator*();
	
    static void assign_id();
    static size_t get_mask();
    static size_t get_id();
    static size_t getTypeSize();
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
    }
}

template <class T>
Component<T>::Component()
    :BaseComponent(nullptr, sizeof(T))
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
Component<T>::Component(void *ptr)
    :BaseComponent(static_cast<uint8_t*>(ptr), sizeof(T))
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
    size_t ret = 1<<get_id();
    return ret;
}

template<class T>
size_t Component<T>::getTypeSize()
{
    return sizeof(T);
}

template < class T >
T* Component<T>::operator->()
{
	return &getComponent();
}

template < class T >
T& Component<T>::operator*()
{
	return getComponent();
}
#endif