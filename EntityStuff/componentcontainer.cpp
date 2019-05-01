#include "componentcontainer.h"

ComponentContainer:: ComponentContainer(size_t elem_size)
    :elem_size(elem_size), elems_count(0), capacity(0), data_ptr(nullptr)
{}

ComponentContainer:: ComponentContainer(const ComponentContainer & other)
: elem_size(other.elem_size), elems_count(other.elems_count), capacity(other.capacity), data_ptr(new char [capacity*elem_size])
{
	std::memcpy(data_ptr, other.data_ptr, elems_count*elem_size);
}

ComponentContainer::~ComponentContainer()
{
    if(data_ptr) delete data_ptr;
}

size_t ComponentContainer::size()
{
	return elems_count;
}

void ComponentContainer::resise(size_t n_elems)
{
     char * temp = data_ptr;
     size_t new_capacity = n_elems * elem_size;
     data_ptr = new char[new_capacity];
     size_t min_size = std::min(elems_count, new_capacity);

     std::memcpy(data_ptr, temp, min_size*elem_size);
     capacity = new_capacity;

     if( temp ) delete  temp;
}

void ComponentContainer::push(const char *data)
{
    if(elems_count >= capacity) resise(capacity+ CHUNK_SIZE);
    char * dest = data_ptr + (elems_count*elem_size);
    std::memcpy(dest, data, elem_size);
    elems_count++;
}

void *ComponentContainer::operator[](size_t n)
{
    if(n < elems_count)
        return static_cast<void*>(data_ptr + (elem_size*n));
    else
        throw std::runtime_error("component_container out of bounds:");

}