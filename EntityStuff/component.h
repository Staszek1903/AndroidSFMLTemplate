#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <stdint.h>
#include <string>

//#include "componentmanager.h"
//#include "../IOStuff/console.h"
#include <stdexcept>

namespace stuff {
    constexpr size_t MAX_COMPONENT_TYPE_ID = 15;

    /**
     * @brief TypeID - unique number coresponding to certain type
     */
    using TypeID = unsigned char;
    /**
     * @brief TypeMask - number with one bit set (power of 2) coresponding to certain type
     */
    using TypeMask = unsigned int;

    /**
     * @brief getNewComponentTypeID each time called returns new id.
     * @throw runtime error if MAX_COMPONENT_TYPE_ID exceeded
     * @return TypeID of new compoennt type
     */
    TypeID getNewComponentTypeID();

    /**
     *  @brief Component - helper clas for getting component ID and/or Mask,
     *  should not be used as component holder or handler
     */
    template <class T>
    class Component{
        static TypeID component_type_id;
    public:
        /**
         * @brief getTypeID returns id of template component type
         * @return unique number coresponding to template type
         */
        static TypeID getTypeID();
        /**
         * @brief getTypeMask return mask of template component type
         * @return
         */
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

#endif
