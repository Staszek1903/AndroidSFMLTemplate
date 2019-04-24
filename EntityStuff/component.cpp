#include "component.h"

BaseComponent::BaseComponent()
    :class_name(""), data(nullptr), size(0)
{;}

BaseComponent::BaseComponent(const BaseComponent & other)
    :BaseComponent(other.getClassName(), static_cast<uint8_t*>(other.getDataPtr()), other.getDataSize())
{
	Console::get()<<"base copy_constructor\n";
}

BaseComponent & BaseComponent::operator= (const BaseComponent & other)
{
    delete [] data;
    size = other.getDataSize();
    data = static_cast<uint8_t*>(other.getDataPtr());
    class_name = other.getClassName();
    
    Console::get()<<"base copy operator\n";
    return *this;
}

BaseComponent::BaseComponent(std::string class_name, uint8_t *data, int size)
    :class_name(class_name), data(data),size(size)
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

std::string BaseComponent::getClassName() const
{
    return class_name;
}

void BaseComponent::release()
{
    delete[] data;
}