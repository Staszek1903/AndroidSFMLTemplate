#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <stdint.h>
#include <string>

//#include "componentmanager.h"
//#include "../IOStuff/console.h"
#include <stdexcept>

namespace stuff {
    constexpr size_t MAX_COMPONENT_TYPE_ID = 15;

    using TypeID = unsigned char;
    using TypeMask = unsigned int;

    TypeID getNewComponentTypeID();

    /**
     *  @brief Component - helper clas for getting component ID and Mask
     */
    template <class T>
    class Component{
        static TypeID component_type_id;
    public:
        static TypeID getTypeID();
        static TypeMask getTypeMask();
    };

    template <class T>
    TypeID Component<T>::component_type_id = getNewComponentTypeID();

    template <class T>
    inline TypeID Component<T>::getTypeID()
    {
        return component_type_id;
    }

    template<class T>
    inline TypeMask Component<T>::getTypeMask()
    {
        return (1<<component_type_id);
    }

    template<class ... Args>
    constexpr TypeMask getComponentsTypeMask(){
        return (Component<Args>::getTypeMask()| ...);
    }
}
///**
//	* Component base class
//	* Assigns id to new component types
//	* Holds pointer to component allocated
//	* in ComponentContainer
//	*/
//class BaseComponent
//{
//protected:
//    static size_t base_id;
	
//protected:
//    uint8_t * data;
//    size_t size;

//public:
//	/**
//		* Doesnt allocate component!
//		*/
//    BaseComponent();
//    /**
//    	* Copies information about component
//    	* and its poiter
//    	* and NOT component itself
//    	*/
//    BaseComponent(const BaseComponent &);
//    /**
//    	* same as copy constructor
//    	*/
//     BaseComponent & operator= (const BaseComponent &);

//    BaseComponent(uint8_t *data, size_t size);
//    virtual ~BaseComponent();
//    /**
//    	* @return poiter to component data in
//    	* ComponentContainer
//    	*/
//    virtual void * getDataPtr() const;
//    /**
//    	* @return size of compoent in bytes
//    	*/
//    virtual size_t getDataSize() const;
//    /**
//    	* Destroys daa of a component
//    	*/
//    virtual void release();
	
//	/**
//		* Alocates new data for the component
//		* @param manager - component manager
//		* @param entity_id - id of entity which component belogs to
//		* @param component_id - id of this component type
//		*/
//void allocate(ComponentManager & manager, size_t entity_id, size_t component_id);
//};

///**
//	* Component wraper class .
//	* Used to interface with compoent data
//	*/
//template <class T>
//class Component : public BaseComponent
//{
//private:
//	static int _id;

//public:
//    /**
//    	* Same as BaseComponent
//    	* but can create new component id
//    	* if type wasnt used previously
//    	*/
//    Component();
//    /**
//    	* Wraps around pointer to data in
//    	* ComponentContainer
//    	*/
//    Component(void *ptr);
//    /**
//    	* Same as BaseComponent cc-tor
//    	*/
//    Component( const Component<T> & other)
//        :BaseComponent(other){}
//    Component<T> & operator= (const Component<T> & other);
//    ~Component();
	
//	/**
//		* @return reference to underlying component
//		*/
//    T& getComponent();
//	/**
//		* Acces to underlying component members
//		* @return piointer to component
//		*/
//	T* operator->();
//	/**
//		* Same as getComponent
//		* @returns reference to underlying component
//		*/
//	T& operator*();
	
//	/**
//		* Staticly assigns new id to component type if that type wasnt previously assigned
//		*/
//    static void assign_id();
//    /**
//    	* reformates id into component bitmask
//    	* where only one bit is high
//    	* @returns mask
//    	*/
//    static size_t get_mask();
//    /**
//		* @return id of component type
//		*/
//    static size_t get_id();
    
//    /**
//    	* @return size of compoennt of type T in bytes
//    	*/
//    static size_t getTypeSize();
//};

//template < class T >
//int Component <T> ::_id = 0;

//template <class T>
//void Component<T>::assign_id()
//{
//    if(!_id)
//    {
//        if(base_id>stuff::MAX_COMPONENT_TYPE_ID) throw std::runtime_error("run out of ids for components");
//        _id = base_id;
//        ++base_id;

//        Console::get()<<"Componen::_id added: "<<_id<<"\n";
//    }
//}

//template <class T>
//Component<T>::Component()
//    :BaseComponent(nullptr, sizeof(T))
//{
//    assign_id();
//	//Console::get()<< "component constructor base id:"<<_id<<"\n";
//}

//template< class T >
//    Component<T> & Component<T>::operator= (const Component<T> & other)
//    {
//    	return static_cast <Component<T> > (BaseComponent::operator= (other) );
//    }
    
//template<class T>
//Component<T>::Component(void *ptr)
//    :BaseComponent(static_cast<uint8_t*>(ptr), sizeof(T))
//{
//	Console::get()<<"component ptr c-tor\n";
//}

//template <class T>
//Component<T>::~Component()
//{;}

//template <class T>
//T& Component<T>::getComponent()
//{
//    void * d = static_cast<void*>(data);
//    return *(static_cast<T*>(d));
//}

//template< class T >
//size_t Component<T>::get_id()
//{
//    assign_id();
//    return _id;
//}

//template < class T >
//size_t Component<T>::get_mask()
//{
//    size_t ret = 1<<get_id();
//    return ret;
//}

//template<class T>
//size_t Component<T>::getTypeSize()
//{
//    return sizeof(T);
//}

//template < class T >
//T* Component<T>::operator->()
//{
//	return &getComponent();
//}

//template < class T >
//T& Component<T>::operator*()
//{
//	return getComponent();
//}
#endif
