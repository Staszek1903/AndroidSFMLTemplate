#include "Program.h"

Program::Program()
    : win(sf::VideoMode::getDesktopMode(), "title"), console(win)
{
    auto vm = sf::VideoMode::getDesktopMode();
    //std::cout<<vm.width<<" "<<vm.height<<std::endl;
	win.setFramerateLimit(30);

}

Program::~Program()
{}

void Program::run()
{
    int tick = 0;
	while(win.isOpen())
	{
        console<<tick;
        tick++;
		input();
		onUpdate();
		render();
	}
}

void Program::input()
{
	sf::Event ev;
	while(win.pollEvent(ev))
	{
		if(ev.type == sf::Event::Closed) win.close();
		onEvent(ev);
	}
}

void Program::render()
{
	win.clear(sf::Color::Yellow);

	onRender();
    console.draw();

	win.display();
}

void Program::onRender()
{}

void Program::onUpdate()
{}

void Program::onEvent(sf::Event &ev)
{}
