#include "p.h"

P::P()
{
    s.setPosition(sf::Vector2f (200,200));
    s.setFillColor(sf::Color::Blue);
    s.setRadius(100);
 	ui.createDefault();
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
	if(ev.type == sf::Event::KeyPressed)
	{
		if(ev.key.code == sf::Keyboard::A)
			em.addEntity<Ca>();
		if(ev.key.code == sf::Keyboard::B)
			em.addEntity<Cb>();
		if(ev.key.code == sf::Keyboard::C)
			em.addEntity<Cc>();
	}
}