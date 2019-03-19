#ifndef TOUCHBUFFER_H
#define TOUCHBUFFER_H

#include <queue>
#include "Console.h"

class TouchEvent
{
public:
    enum State
    {
        BEGIN,
        SWIPE,
        END,
        NO_EVENT
    };

    TouchEvent(int x, int y, int finger, State state);
    TouchEvent();
    int x;
    int y;
    int finger;
    int state;
};

class TouchBuffer
{
    static TouchBuffer * instance;
    TouchBuffer();

    std::queue <TouchEvent> event_queue;
    TouchEvent current;

public:
    void pushEvent(const TouchEvent &ev);
    TouchEvent pollEvent();
    TouchEvent getCurrent();

    static TouchBuffer & get();
    static void release();
};

#endif // TOUCHBUFFER_H
