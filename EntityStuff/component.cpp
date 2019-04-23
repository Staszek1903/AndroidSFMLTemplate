#include "component.h"

BaseComponent::BaseComponent()
    :class_name(""), data(nullptr), size(0)
{;}

BaseComponent::BaseComponent(const BaseComponent & other)
    :BaseComponent(other.getClassName(), new uint8_t [ other.getDataSize()], other.getDataSize())
{
    auto * other_data = static_cast<uint8_t*>(other.getDataPtr());
    for(int i=0; i<size; ++i) data[i] = other_data[i];
}

BaseComponent & BaseComponent::operator= (const BaseComponent & other)
{
    delete [] data;
    size = other.getDataSize();
    data = new uint8_t [ size ] ;
    auto * other_data = static_cast<uint8_t*>(other.getDataPtr());
    for(int i=0; i<size; ++i) data[i] = other_data[i];
    class_name = other.getClassName();
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
