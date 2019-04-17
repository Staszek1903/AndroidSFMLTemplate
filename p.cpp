#include "p.h"

class S : public System
{
public: 
	S(){}
protected:
	virtual void addComponent(Component * )  override;
};

void S::addComponent(Component * c)
{
	
}

P::P()
{
    s.setPosition(sf::Vector2f (200,200));
    s.setFillColor(sf::Color::Blue);
    s.setRadius(100);
 	ui.createDefault();
 	
 	EntityStuff::get();
	EntityStuff::get().addSystem<S>();	
 }
 
 P::~P()
 {
 	EntityStuff::release();
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
		/*if(ev.key.code == sf::Keyboard::A)
			em.addEntity<Ca>();
		if(ev.key.code == sf::Keyboard::B)
			em.addEntity<Cb>();
		if(ev.key.code == sf::Keyboard::C)
			em.addEntity<Cc>();
		if(ev.key.code == sf::Keyboard::E)
	*/
	}
}