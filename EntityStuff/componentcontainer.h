#ifndef COMPONENTCONTAINER_H
#define COMPONENTCONTAINER_H

#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <exception>
#include "component.h"

#include <map>

#define CHUNK_SIZE 16

class ComponentContainer
{
    size_t elem_size, //element size in bytes
    elems_count, //how many element in block
    capacity;   // how many elements could be in block
    char * data_ptr;

public:
    ComponentContainer(size_t elem_size);
    ComponentContainer(const ComponentContainer &);
    ComponentContainer & operator= (const ComponentContainer &) = delete;
    virtual ~ ComponentContainer();


    /**
     * @brief resise changes capacity
     * @param n_elems - that many elems will fit in capacity
     */
    size_t size();
    void resise(size_t n_elems);
    void push(const char * data);

    void * operator[] (size_t n);

};


template< class T>
class ComponentGetter : public ComponentContainer
{
	/**
	  * first: entity id
	  * second: intex of component
	  */
    std::map <size_t, size_t> id_component_map;
    
public:
    ComponentGetter();

    void addComponent(Component<T> component, size_t id);
    Component<T> getComponent(size_t id);
};

template<class T>
void ComponentGetter<T>::addComponent(Component<T> component, size_t id)
{
	const char * temp = static_cast<char *>(component.getDataPtr());
	
	id_component_map[id] = this-> 
	size();
    push(temp);
}

template<class T>
Component <T>  ComponentGetter<T>::getComponent(size_t id)
{
    if(id_component_map.find(id) == id_component_map.end()) throw std::runtime_error ( "no id in component getter" );
    
    size_t index = id_component_map.at(id);
    Component<T> ret (this->operator[](index));
    return ret;
}


#endif // COMPONENTCONTAINER_H