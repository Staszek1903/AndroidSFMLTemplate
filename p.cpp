#include "p.h"


P::P()
{
	
	ResourceManager::get();
	
    s.setPosition(sf::Vector2f (200,200));
    s.setFillColor(sf::Color::Blue);
    s.setRadius(100);
 	ui.createDefault();
 	
 	Script sc;
 	sc.load_from_file("./textures/textures.conf");
 	
 }
 
 P::~P()
 {
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
	if(ev.type == sf::Event::TouchBegan)
	{}
	if(ev.type == sf::Event::KeyPressed)
	{
		if(ev.key.code == sf::Keyboard::A)
         {}
        //if(ev.key.code == sf::Keyboard::B)
           // EntityStuff::get().addComponent<C3>(1);
        /*if(ev.key.code == sf::Keyboard::C)
			em.addEntity<Cc>();
		if(ev.key.code == sf::Keyboard::E)
	*/
	}
}