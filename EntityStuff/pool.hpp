#ifndef POOL_HPP
#define POOL_HPP

#include "../IOStuff/singleton.hpp"
#include <vector>
#include <utility>

namespace stuff {

    using RawID = unsigned int;
    constexpr RawID EmptyID = static_cast<RawID>(-1);

    template <class T>
    struct ComponentData{
        RawID next_free{EmptyID};
        T data;
    };

    template <class T>
    class Pool : public Singleton<Pool<T>>
    {
        static constexpr size_t INIT_SIZE = 256;

        std::vector < ComponentData<T> > data{INIT_SIZE};
        RawID first_free{0}, last_used{0};
        void expandPool();
        void initReferences(size_t size);
    public:

        class ID{
            stuff::RawID id{stuff::EmptyID};
        public:
            ID();
            ID(stuff::RawID id);
            ID(const Pool<T>::ID &id);
            ~ID();

            ID& operator=(const ID&);
            ID& operator++();
            T& operator*() const;
            T* operator->() const;
            bool operator==(const ID & rhs);
            bool operator!=(const ID & rhs);

            RawID getRaw();

            friend void swap(ID& lhs, ID& rhs);
        };



        Pool();
        Pool(const Pool &) = delete;
        Pool & operator= (const Pool *) = delete;

        /**
         * @brief addComponent marks next component node as used
         * @return componentID
         */
        template<class ... Args>
        ID allocate(Args&& ... args);

        /**
         * @brief removeComponent
         * @param id
         */
        void free(RawID id);

        /**
         * @brief operator [] returns reference to compnent data node
         * @param id componentID
         * @return reference to data
         */
        T& operator[](RawID id);

        size_t capacity();
        void reset();

        ID begin(){
            return ID(0);
        }

        ID end(){
            return ID(last_used+1);
        }
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
            data[i].data.~T();
        }
        data[stop-1].data.~T();
    }

    template<class T>
    Pool<T>::Pool()
        :data(INIT_SIZE), first_free(0)
    {
        initReferences(0);
    }

    template <class T> template<class ... Args>
    inline typename Pool<T>::ID Pool<T>::allocate(Args&& ...args)
    {
        RawID free = first_free;
        first_free = data[free].next_free;

        if(first_free == EmptyID){
            expandPool();
            first_free = data[free].next_free;
        }


        T*ptr = &(data[free].data);
        new (ptr) T(std::forward<Args>(args)...);

        if(free > last_used) last_used = free;

        return ID(free);
    }

    template<class T>
    inline void Pool<T>::free(RawID id)
    {
        data[id].next_free = first_free;
        first_free = id;
        data[id].data.~T();
    }

    template<class T>
    inline T& Pool<T>::operator[](RawID id)
    {
        return data[id].data;
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

    template<class T>
    Pool<T>::ID::ID()
    {}

    template<class T>
    Pool<T>::ID::ID(RawID id)
        :id(id)
    {}

    template<class T>
    Pool<T>::ID::ID(const Pool<T>::ID &id)
        :id(id.id)
    {}

    template<class T>
    Pool<T>::ID::~ID()
    {
        id = stuff::EmptyID;
    }

    template<class T>
    inline typename Pool<T>::ID &Pool<T>::ID::operator=(const Pool<T>::ID &id)
    {
        this->id = id.id;
        return *this;
    }

    template<class T>
    inline typename Pool<T>::ID &Pool<T>::ID::operator++()
    {
        ++id;
        return *this;
    }

    template<class T>
    T &Pool<T>::ID::operator*() const
    {
        return Pool<T>::get()[this->id];
    }

    template<class T>
    T *Pool<T>::ID::operator->() const
    {
        return &(Pool<T>::get()[this->id]);
    }

    template<class T>
    inline bool Pool<T>::ID::operator==(const Pool<T>::ID &rhs)
    {
        return this->id == rhs.id;
    }

    template<class T>
    inline bool Pool<T>::ID::operator!=(const Pool<T>::ID &rhs)
    {
        return this->id != rhs.id;
    }

    template<class T>
    inline RawID Pool<T>::ID::getRaw()
    {
        return id;
    }

}

#endif // POOL_HPP
