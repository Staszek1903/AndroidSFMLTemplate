#include "componentcontainer.h"

DataContainer:: DataContainer(size_t elem_size)
    :elem_size(elem_size), elems_count(0), capacity(0), data_ptr(nullptr)
{}

DataContainer:: DataContainer(const DataContainer & other)
: elem_size(other.elem_size), elems_count(other.elems_count), capacity(other.capacity), data_ptr(new char [capacity*elem_size])
{
	std::memcpy(data_ptr, other.data_ptr, elems_count*elem_size);
}

DataContainer::~DataContainer()
{
    if(data_ptr) delete [] data_ptr;
}

size_t DataContainer::size()
{
    return elems_count;
}

size_t DataContainer::get_elem_size()
{
    return elem_size;
}

size_t DataContainer::get_capacity()
{
    return capacity;
}

void DataContainer::resise(size_t n_elems)
{
     char * temp = data_ptr;
     size_t new_capacity = n_elems * elem_size;
     data_ptr = new char[new_capacity];
     size_t min_size = std::min(elems_count, new_capacity);

     std::memcpy(data_ptr, temp, min_size*elem_size);
     capacity = new_capacity;

     if( temp ) delete  temp;
}

void DataContainer::push(const char *data)
{
    if(elems_count >= capacity) resise(capacity+ CHUNK_SIZE);
    char * dest = data_ptr + (elems_count*elem_size);
    std::memcpy(dest, data, elem_size);
    elems_count++;
}

void *DataContainer::operator[](size_t n)
{
    if(n < elems_count)
        return static_cast<void*>(data_ptr + (elem_size*n));
    else
        throw std::runtime_error("Data_container out of bounds:");

}

ComponentContainer::ComponentContainer(size_t elem_size)
    : DataContainer (elem_size)
{
}

void *ComponentContainer::addComponent(size_t entity_id)
{
    if(id_component_map.find(entity_id) !=
            id_component_map.end())
    {
        std::stringstream ss;
        ss<<entity_id;
        throw std::runtime_error("component if id : <" + ss.str() + "> allready exists");
    }
	
	if(free_indices.size() == 0)
	{
	    id_component_map[entity_id] = this->size();
	    char * buffer = new char [get_elem_size()];
	    push(buffer);
	    delete [] buffer;
	}
	else
	{
		id_component_map[entity_id] = free_indices.back();
		free_incides.pop_back();
	}

    return this->operator[](id_component_map.at(entity_id));
}

void *ComponentContainer::getComponent(size_t entity_id)
{
    return this->operator[](id_component_map.at(entity_id));
}

void ComponentContainer::releaseComponent(size_t entity_id)
{
	auto it = id_component_map.find(entity_id);
	if(it == id_component_map.end()) return;
	size_t comp_index = id_component_map.at(entity_id);
	
	id_component_map.erase(it);
	free_indices.push_back(comp_index);
}	