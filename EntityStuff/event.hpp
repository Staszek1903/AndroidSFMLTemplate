#ifndef EVENT_H_
#define EVENT_H_

#include <cstdlib>
#include <vector>
#include <functional>
#include <iostream>

#include "../IOStuff/singleton.hpp"


namespace stuff {

    /**
     * @brief The Event class
     *        manager class for managing event handlers and events
     *        contains pointers to all HandlerConteiners for all event types
     *        enables adding and removing handler and emiting event
     */
    class Event{
        static std::vector< Event* > instances_ptr;
    public:
        Event(){
            instances_ptr.push_back(this);
        }

        virtual void reset() = 0; /**< virtual function for handler container reset */
        static void resetHandlers(); /**< resets event handler containers of all types*/

        /**
         *  @brief static function resets handler container for a specified event type
         *  @tparam E - event type
         */
        template <class E>
        static void resetSubscriptions();

        /**
         *  @brief makes given function listen to emited event of given type
         *  @tparam E - event type
         *  @param func - callback function answering the event
         */
        template <class E>
        static void subscribe(std::function<void(const E&)> func);

        /**
         *  @brief emiting event call all functions subscribed to this event
         *  @tparam E - event type
         *  @tparam Args - template pack of argument types
         *  @param args - event constructor arguments
         */
        template <class E, class ... Args>
        static void emit(Args&& ... args);
    };

    template<class E>
    class HandlerContainer : public Singleton< HandlerContainer<E> >, public Event{
    public:
        std::vector< std::function<void(const E&)> > handlers;

        virtual void reset() override;
    };

    template <class E>
    void Event::resetSubscriptions(){
        HandlerContainer< std::function<void(const E&)> > ::get().handlers.clear();
    }

    template <class E>
    void Event::subscribe(std::function <void(const E&)> func){
        HandlerContainer<E>::get().handlers.push_back(func);
    }

    template <class E, class ... Args>
    void Event::emit(Args&& ... args){
        for(auto func : HandlerContainer<E>::get().handlers)
            func(E(args...));
    }

    template<class E>
    void HandlerContainer<E>::reset()
    {
        handlers.clear();
        std::cout<<"handler container reset type<"<<typeid (E).name()<<">"<<std::endl;
    }
}

#endif /* EVENT_H_ */
