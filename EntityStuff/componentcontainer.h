#ifndef COMPONENTCONTAINER_H
#define COMPONENTCONTAINER_H

#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <exception>

#include <map>

#define CHUNK_SIZE 16

class ComponentContainer
{
    size_t elem_size, //element size in bytes
    elems_count, //how meny element in block
    capacity;   // how meny elements could be in block
    char * data_ptr;

public:
    ComponentContainer(size_t elem_size);
    ComponentContainer(const ComponentContainer &) = delete;
    ComponentContainer & operator= (const ComponentContainer &) = delete;
    virtual ~ ComponentContainer();


    /**
     * @brief resise changes capacity
     * @param n_elems - that many elems will fit in capacity
     */
    void resise(size_t n_elems);
    void push(char * data);

    void * operator[] (size_t n);

};


template< class T>
class ComponentGetter : public ComponentContainer
{
    std::map <size_t, size_t> id_component_map;
public:
    ComponentGetter();

    void addComponent(T component);
    T * getComponent();
};

template<class T>
void ComponentGetter<T>::addComponent(T component)
{
    //TODO
}

template<class T>
T *ComponentGetter<T>::getComponent()
{
    //TODO
}


#endif // COMPONENTCONTAINER_H
