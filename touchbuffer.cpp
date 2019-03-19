#include "touchbuffer.h"

TouchBuffer * TouchBuffer::instance = nullptr;

TouchBuffer::TouchBuffer()
{

}

void TouchBuffer::pushEvent(const TouchEvent &ev)
{
    event_queue.push(ev);
    current = ev;
    Console::get()<<"finger: "<<ev.finger
    <<" touch: "<<ev.x<<" "<<ev.y<<"\n";
}

TouchEvent TouchBuffer::pollEvent()
{
    TouchEvent ret;
    if(!event_queue.empty())
    {
        ret = event_queue.front();
        event_queue.pop();
    }

    return ret;
}

TouchEvent TouchBuffer::getCurrent()
{
    std::queue<TouchEvent>().swap(event_queue);
    return current;
}

TouchBuffer &TouchBuffer::get()
{
    if(!instance)
        instance = new TouchBuffer();
    return *instance;
}

void TouchBuffer::release()
{
    if(instance)
    {
        delete instance;
        instance = nullptr;
    }
}

TouchEvent::TouchEvent(int x, int y, int finger, State state)
    :x(x), y(y), finger(finger), state(state)
{}

TouchEvent::TouchEvent()
    :x(0),y(0), finger(0), state(NO_EVENT)
{}
