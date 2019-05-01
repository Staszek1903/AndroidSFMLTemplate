#include "p.h"

struct C
{ 
	int i;
};

struct C2{};
struct C3{};

class S : public System<C>
{
public: 
	S(){}
    virtual ~S() override {}
protected:
    virtual void update_elem(Component<C>  comp) override 
    {
    	C & c = comp.getComponent();
    	c.i++;
    	Console::get()<<"comp C "<<c.i<<" \n";
    }
};

class S2 : public System<C2>
{
public: 
	S2(){}
    virtual ~S2() override {}
    virtual void update_elem(Component<C2>  comp) override {Console::get()<<"comp C2"<<"\n";}
};

class S3 : public System<C3>
{
public: 
	S3(){}
    virtual ~S3() override {}
    virtual void update_elem(Component<C3> comp) override {Console::get()<<"comp C3"<<"\n";}
};


P::P()
{
    s.setPosition(sf::Vector2f (200,200));
    s.setFillColor(sf::Color::Blue);
    s.setRadius(100);
 	ui.createDefault();
 	
 	EntityStuff::get();
    EntityStuff::get().addSystem<S>();
    EntityStuff::get().addSystem<S2>();
	EntityStuff::get().addSystem<S3>();
	
	
    auto c1 = EntityStuff::get().addComponent<C>(1);
//	c1.getComponent().i = 0;
    auto c2 = EntityStuff::get().addComponent<C>(2);
//	c2.getComponent().i  = 10;
    auto c3 =	EntityStuff::get().addComponent<C2>(1);
    auto c4 = EntityStuff::get().addComponent<C3>(1);
    auto c5 = EntityStuff::get().addComponent<C3>(2);
	
      // Console::get()<<"empty size: "<<Component<C>().getClassName()<<'\n';
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
		if(ev.key.code == sf::Keyboard::A)
			EntityStuff::get().update_systems();
		/*if(ev.key.code == sf::Keyboard::B)
			em.addEntity<Cb>();
		if(ev.key.code == sf::Keyboard::C)
			em.addEntity<Cc>();
		if(ev.key.code == sf::Keyboard::E)
	*/
	}
}
