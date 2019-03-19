#include "p.h"

P::P()
{
    s.setPosition(sf::Vector2f (200,200));
    s.setFillColor(sf::Color::Blue);
    s.setRadius(100);
}

void P::onUpdate()
{
    sf::Vector2f pos = s.getPosition();
    s.setPosition({pos.x+1,pos.y+1});
}

void P::onRender()
{
    win.draw(s);
}

void P::onEvent(sf::Event &ev)
{
	switch(ev.type)
	{
		case sf::Event::TouchBegan:
//			Console::ge()<<"touch kurva\n";
		break;
		
		default:
		break;
	}
}