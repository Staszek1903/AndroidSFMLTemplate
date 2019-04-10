#include "p.h"

P::P()
:t1(100,500,100,100), t2(300,500, 100,100)
{
    s.setPosition(sf::Vector2f (200,200));
    s.setFillColor(sf::Color::Blue);
    s.setRadius(100);
 	t1.setFillColor(sf::Color::Blue);
 	t2.setFillColor(sf::Color::Green);
 	Renderer::get().addDrawable(t1);
 	Renderer::get().addDrawable(t2);
 	
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

}