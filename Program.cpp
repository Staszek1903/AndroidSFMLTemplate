#include "Program.h"

Program::Program()
	: win(sf::VideoMode::getDesktopMode(), "title")
{
	win.setFramerateLimit(30);
}

Program::~Program()
{}

void Program::run()
{
	while(win.isOpen())
	{
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
	win.display();
}

void Program::onRender()
{}

void Program::onUpdate()
{}

void Program::onEvent(sf::Event &ev)
{}