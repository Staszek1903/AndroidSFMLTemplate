#include "p.h"

struct C
{ 
    C(int i, int j) : i(i), j(j){}
	int i;
    int j;
};

struct C2
{
    C2(float a) : a(a){}
    float a;
};
struct C3
{
    C3(std::string s) : s(s){}
    std::string s;
};

class S : public System
{
public: 
    S()
    {}
    virtual ~S() override {}
protected:
    virtual void update(EntityManager & em) override
    {

        Console::get()<<"Comp C\n";
       for(Entity en : get_entities<C>(em))
       {
           C &c = en.component<C>().getComponent();
           //Console::get()<<" i: "<<c.i<<"\n j: "<<c.j<<"\n";

           c.i++;
           c.j--;
       }
    }
};

class S2 : public System
{
public: 
    S2()
    {}
    virtual ~S2() override {}
    virtual void update(EntityManager & em) override
    {
        Console::get()<<"comp C2"<<"\n";
        for(Entity en : get_entities<C2,C3>(em))
        {
            C2 & c2 = en.component<C2>().getComponent();
            C3 & c3 = en.component<C3>().getComponent();

            //Console::get()<<c3.s<<" : "<<c2.a<< "\n";

            c2.a *= 2;
        }
    }
};

P::P()
{
    s.setPosition(sf::Vector2f (200,200));
    s.setFillColor(sf::Color::Blue);
    s.setRadius(100);
 	ui.createDefault();
 	
    es.addSystem<S>();
    es.addSystem<S2>();

    Entity a1(es.get_entity_manager());
    Entity a2(es.get_entity_manager());
    Entity a3(es.get_entity_manager());
    a1.create();
    a2.create();
    a3.create();

    //4 .event system
    //5. ogarnąć kasowanie
    //      I komponentow
    //      II entitow

    a1.assign<C>(1,1);
    a2.assign<C>(-100, 100);
    a1.assign<C2>(1.23);
    a1.assign<C3>("SIEMA KURWY");

	
      // Console::get()<<"empty size: "<<Component<C>().getClassName()<<'\n';
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
	if(ev.type == sf::Event::KeyPressed)
	{
		if(ev.key.code == sf::Keyboard::A)
            es.update_systems();
        //if(ev.key.code == sf::Keyboard::B)
           // EntityStuff::get().addComponent<C3>(1);
        /*if(ev.key.code == sf::Keyboard::C)
			em.addEntity<Cc>();
		if(ev.key.code == sf::Keyboard::E)
	*/
	}
}
