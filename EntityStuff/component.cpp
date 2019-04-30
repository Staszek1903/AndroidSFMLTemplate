#include "component.h"

int BaseComponent::base_id = 1;  

BaseComponent::BaseComponent()
    :data(nullptr), size(0)
{;}

BaseComponent::BaseComponent(const BaseComponent & other)
    :BaseComponent( static_cast<uint8_t*> (other.getDataPtr()), other.getDataSize())
{
	Console::get()<<"base copy_constructor\n";
}

BaseComponent & BaseComponent::operator= (const BaseComponent & other)
{
    delete [] data;
    size = other.getDataSize();
    data = static_cast<uint8_t*>(other.getDataPtr());
    
    Console::get()<<"base copy operator\n";
    return *this;
}

BaseComponent::BaseComponent(uint8_t *data, int size)
    : data(data),size(size)
{;}

BaseComponent::~BaseComponent()
{}

void *BaseComponent::getDataPtr() const
{
    return static_cast<void*>(data);
}

int BaseComponent::getDataSize() const
{
    return size;
}

void BaseComponent::release()
{
    delete[] data;
}