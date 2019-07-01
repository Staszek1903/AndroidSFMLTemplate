#ifndef COMPONENTCONTAINER_H
#define COMPONENTCONTAINER_H

#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <exception>
#include <sstream>

#include <map>
#include <vector>

#include "sizemap.h"

#define CHUNK_SIZE 16

/**
	* Generic class of DataContainer
	* Non template class available if containing varius types
	*
	*/
class DataContainer
{
    size_t elem_size, //element size in bytes
    elems_count, //how many element in block
    capacity;   // how many elements could be in block
    char * data_ptr;

public:
	/**
		* @param elem_size - size of single memory cell in container in bytes
		*/
    DataContainer(size_t elem_size);
    DataContainer(const DataContainer &);
    DataContainer & operator= (const DataContainer &) = delete;
    virtual ~ DataContainer();


    size_t size();
    size_t get_elem_size();
    
    /**
    	* current amount of elements container is available to consist
    	*/
    size_t get_capacity();
    
    /**
     * @brief resise changes capacity
     * @param n_elems - that many elems will fit in capacity
     */
    void resise(size_t n_elems);
    /**
    	* alocates new component in memory
    	* resizes container if needed
    	*/
    void push(const char * data);
	
	/**
		* accesses element in memory
		* @param n - index of element
		* @return pointer to element
		*/
    void * operator[] (size_t n);

};

/**
	* ComponentContainer class is DataContainer that bins ComponentData with id of entity it belogs to
	*/
class ComponentContainer : public DataContainer
{
protected:
    /**
      * first: entity id
      * second: intex of component
      */
    std::map<size_t, size_t> id_component_map;
    std::vector<size_t> free_indices;
public:
    /**
    	* same as DataContainer
    	*/
    ComponentContainer(size_t elem_size);
    /**
    	* allocates new component data
    	* saves binding of it with entity id
    	* @param entity_id cannot be the same as id that is allredy added to container
    	* @return pointer to allocated data
    	*/
    void * addComponent(size_t entity_id);
    /**
    	* Gets ponter to component binded to id
    	* @param entity_id 
    	* @return pointer to data
    	*/
    void * getComponent(size_t entity_id);
	/**
		* sets memory cell belonging to entity to as free and able for allocate
		*@param entity_id
		*/
	void releaseComponent(size_t entity_id);
	
	/**
		* defragments container data romoving emty indices and reducing container size
		* @TODO
		*/
	void defragment();
};

#endif // COMPONENTCONTAINER_H
