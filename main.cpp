#include "Program.h"
#include <SFML/Graphics.hpp>

class P : public Program
{
	sf::CircleShape s;
public:
	P();
	virtual void onRender() override;
	virtual void onUpdate() override;
};

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

int main()
{
	P p;
	p.run();
	return 0;
}