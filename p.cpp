#include "p.h"


P::P()
{ }
 
 P::~P()
 {}
 
 void P::init()
 {
 	Console::get()<<"P::init\n";
 	ResourceManager::get();
	
    s.setPosition(sf::Vector2f (200,200));
    s.setFillColor(sf::Color::Blue);
    s.setRadius(100);
 	ui.createDefault();	
 }

void P::update(double dt)
{
    sf::Vector2f pos = s.getPosition();
    s.setPosition({pos.x+1,pos.y+1});
}

void P::render(sf::RenderWindow & win)
{
    win.draw(s);
}

void P::input(sf::Event &ev)
{
	if(ev.type == sf::Event::TouchBegan)
	{ Script sc;	sc.load_from_file("./textures/textures.conf"); }
	if(ev.type == sf::Event::KeyPressed)
	{
		if(ev.key.code == sf::Keyboard::A)
         {Script sc;	sc.load_from_file("./textures/textures.conf");}
        if(ev.key.code == sf::Keyboard::B)
        {

        }
        /*if(ev.key.code == sf::Keyboard::C)
			em.addEntity<Cc>();
		if(ev.key.code == sf::Keyboard::E)
	*/
	}
}

void P::release() 
{}