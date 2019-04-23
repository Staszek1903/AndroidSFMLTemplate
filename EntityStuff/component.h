#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <stdint.h>
#include <string>

class BaseComponent
{
protected:
    std::string class_name;
    uint8_t * data;
    int size;

public:
    BaseComponent();
    BaseComponent(const BaseComponent &);
    BaseComponent & operator= (const BaseComponent &);

    BaseComponent(std::string class_name, uint8_t *data, int size);
    virtual ~BaseComponent();
    virtual void * getDataPtr() const;
    virtual int getDataSize() const;
    virtual std::string getClassName() const;
    virtual void release();
};


template <class T>
class Component : public BaseComponent
{

public:
    Component();
    Component(void *ptr);
    ~Component();

    T& getComponent();
};

template <class T>
Component<T>::Component()
    :BaseComponent(typeid(T).name(), new uint8_t [sizeof(T)], sizeof(T))
{}

template<class T>
Component<T>::Component(void *ptr)
    :BaseComponent(typeid(T).name(), (uint8_t*)ptr, sizeof(T))
{}

template <class T>
Component<T>::~Component()
{;}

template <class T>
T& Component<T>::getComponent()
{
    void * d = (void*)data;
    return *((T*)d);
}

#endif
