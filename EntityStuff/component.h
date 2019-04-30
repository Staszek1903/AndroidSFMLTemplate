#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <stdint.h>
#include <string>

#include "../console.h"

class BaseComponent
{
protected:
	static int base_id;
	
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
public:
    Component();
    Component(void *ptr);
    Component( const Component<T> & other)
    	:BaseComponent(other){}
    Component<T> & operator= (const Component<T> & other);
    ~Component();

    T& getComponent();
    
    static int get_id();
};

template < class T >
int Component <T> ::_id = 0;

template <class T>
Component<T>::Component()
    :BaseComponent(new uint8_t [sizeof(T)], sizeof(T))
{
	if(!_id)
	{
		_id = base_id;
		base_id<<=1;
	}
	//Console::get()<< "component constructor base id:"<<_id<<"\n";
}

template< class T > 
    Component<T> & Component<T>::operator= (const Component<T> & other)
    {
    	return static_cast <Component<T> > (BaseComponent::operator= (other) );
    }
    
template<class T>
Component<T>::Component(void *ptr)
    :BaseComponent((uint8_t*)ptr, sizeof(T))
{
	Console::get()<<"component ptr c-tor\n";
}

template <class T>
Component<T>::~Component()
{;}

template <class T>
T& Component<T>::getComponent()
{
    void * d = (void*)data;
    return *((T*)d);
}

template< class T >
int Component<T>::get_id()
{
	if(!_id)
	{
		_id = base_id;
		base_id<<=1;
	}
}
#endif