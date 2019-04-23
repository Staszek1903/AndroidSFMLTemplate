#include "p.h"

struct C
{

};

class S : public System<C>
{
public: 
	S(){}
    virtual ~S() override {}
    virtual void update() override;
};

P::P()
{
    s.setPosition(sf::Vector2f (200,200));
    s.setFillColor(sf::Color::Blue);
    s.setRadius(100);
 	ui.createDefault();
 	
 	EntityStuff::get();
    EntityStuff::get().addSystem<S>();
    Console::get()<<"empty size: "<<Component<C>().getClassName()<<'\n';
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

void S::update()
{

}
