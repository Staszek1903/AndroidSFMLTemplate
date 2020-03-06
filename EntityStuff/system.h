//#ifndef SYSTEM_H_
//#define SYSTEM_H_

//#include <vector>
//#include "eventmanager.h"
//#include "component.h"
//#include "entity.h"
//#include <bitset>

//class System
//{
//protected:

//    template <typename ...>
//    struct MaskGetter
//    {
//        static size_t get() {return 0;}
//    };

//    template<class T, class ... Args>
//    struct MaskGetter <T, Args ... >
//    {
//        static size_t get()
//        {
//            size_t mask = Component<T>::get_mask();
//            mask |= MaskGetter<Args...>::get();
//            return mask;
//        }
//    };

//    typedef std::vector<Entity> Entities;

//public:
//    System();
//    System(const System &) = delete;
//    virtual ~System();
//    virtual void update(EntityManager & em, EventManager & vm, double dt) = 0;

//    template<class ... Args>
//    Entities get_entities(EntityManager & em);

//};

//template<class ... Args>
//System::Entities System::get_entities(EntityManager &em)
//{
//    Entities ents;
//    size_t mask = MaskGetter<Args ...>::get();
//    auto etds = em.get_entities(mask);
//    for(size_t index : etds)
//        ents.push_back(Entity(index, em));

//    return ents;
//}



//#endif
