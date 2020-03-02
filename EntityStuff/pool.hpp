#ifndef POOL_HPP
#define POOL_HPP

#include "../IOStuff/singleton.hpp"
#include <vector>
#include <utility>

namespace stuff {

    using ComponentID = unsigned int;
    constexpr ComponentID EmptyID = static_cast<ComponentID>(-1);

    template <class T>
    struct ComponentData{
        ComponentID next_free{EmptyID};
        T data;
    };

    template <class T>
    class Pool : public Singleton<Pool<T>>
    {
        static constexpr size_t INIT_SIZE = 256;

        std::vector < ComponentData<T> > data{INIT_SIZE};
        ComponentID first_free{0};
        void expandPool();
        void initReferences(size_t size);
    public:
        Pool();
        Pool(const Pool &) = delete;
        Pool & operator= (const Pool *) = delete;

        /**
         * @brief addComponent marks next component node as used
         * @return componentID
         */
        template<class ... Args>
        ComponentID allocate(Args&& ... args);

        /**
         * @brief removeComponent
         * @param id
         */
        void free(ComponentID id);

        /**
         * @brief operator [] returns reference to compnent data node
         * @param id componentID
         * @return reference to data
         */
        T& operator[](ComponentID id);

        size_t capacity();
        void reset();
    };

    template<class T>
    inline void Pool<T>::expandPool()
    {
        size_t size = data.size();
        data.resize(2*size);
        initReferences(size-1);
    }

    template<class T>
    inline void Pool<T>::initReferences(size_t start)
    {
        size_t stop = data.size();
        for(int i=start; i<stop-1; ++i){
            data[i].next_free =i+1;
        }
    }

    template<class T>
    Pool<T>::Pool()
        :data(INIT_SIZE), first_free(0)
    {
        initReferences(0);
    }

    template <class T> template<class ... Args>
    inline ComponentID Pool<T>::allocate(Args&& ...args)
    {
        ComponentID free = first_free;
        first_free = data[free].next_free;

        if(first_free == EmptyID){
            expandPool();
            first_free = data[free].next_free;
        }


        T*ptr = &(data[free].data);
        ptr->~T();
        new (ptr) T(std::forward<Args>(args)...);

        return free;
    }

    template<class T>
    inline void Pool<T>::free(ComponentID id)
    {
        data[id].next_free = first_free;
        first_free = id;
    }

    template<class T>
    inline T& Pool<T>::operator[](ComponentID id)
    {
        return data[id];
    }

    template<class T>
    size_t Pool<T>::capacity()
    {
        return data.size();
    }

    template<class T>
    void Pool<T>::reset()
    {
        data.resize(INIT_SIZE);
        initReferences(0);
        first_free = 0;
    }

}

#endif // POOL_HPP
