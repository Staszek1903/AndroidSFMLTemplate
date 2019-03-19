#include "Program.h"

Program::Program()
    : win(sf::VideoMode::getDesktopMode(), "title")
{
    //auto vm = sf::VideoMode::getDesktopMode();
    //std::cout<<vm.width<<" "<<vm.height<<std::endl;
	win.setFramerateLimit(30);
    Console::set_window(&win);
    Console::get();
    TouchBuffer::get();
}

Program::~Program()
{
    Console::release();
    TouchBuffer::release();
}

void Program::run()
{
    //int tick = 0;
	while(win.isOpen())
	{
        //Console::get()<<"tick: "<<tick<<'\n';
        //tick++;
		input();
		onUpdate();
		render();
	}
}

void Program::input()
{
    static int mousePressed = 0;
	sf::Event ev;
	while(win.pollEvent(ev))
	{   
        switch(ev.type)
        {
        case sf::Event::Closed:
            win.close();
            break;

        case sf::Event::TouchBegan:
            TouchBuffer::get().pushEvent(TouchEvent(ev.touch.x, ev.touch.y, ev.touch.finger, TouchEvent::BEGIN));
            break;

        case sf::Event::TouchMoved:
            TouchBuffer::get().pushEvent(TouchEvent(ev.touch.x, ev.touch.y, ev.touch.finger, TouchEvent::SWIPE));
            break;

        case sf::Event::TouchEnded:
            TouchBuffer::get().pushEvent(TouchEvent(ev.touch.x, ev.touch.y, ev.touch.finger, TouchEvent::END));
            break;

        case sf::Event::MouseButtonPressed:
            TouchBuffer::get().pushEvent(TouchEvent(ev.mouseButton.x, ev.mouseButton.y, ev.mouseButton.button, TouchEvent::BEGIN));
            mousePressed++;
            break;

        case sf::Event::MouseMoved:
            if(mousePressed>0)
                TouchBuffer::get().pushEvent(TouchEvent(ev.mouseMove.x, ev.mouseMove.y, 0, TouchEvent::SWIPE));
            break;

        case sf::Event::MouseButtonReleased:
            TouchBuffer::get().pushEvent(TouchEvent(ev.mouseButton.x, ev.mouseButton.y, ev.mouseButton.button, TouchEvent::END));
            mousePressed--;
            break;

        default:
            break;
        }

        onEvent(ev);
	}
}

void Program::render()
{
	win.clear(sf::Color::Yellow);
	onRender();
    Console::get().display();
	win.display();
}

void Program::onRender()
{}

void Program::onUpdate()
{}

void Program::onEvent(sf::Event &ev)
{}
