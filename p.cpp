#include "p.h"

struct C
{ 
	int i;
    int j;
};

struct C2{};
struct C3{};

class S : public System
{
public: 
    S()
    {
        //update_mask<C>();
    }
    virtual ~S() override {}
protected:
    virtual void update(EntityManager & em) override
    {
        Console::get()<<"Comp C\n";
       for(EntityData end : em.get_entities(Component<C>::get_mask()))
       {
           Entity en(end, em);
           C &c = en.component<C>().getComponent();

           Console::get()<<" i: "<<c.i<<"\n j: "
                        <<c.j<<"\n";

           c.i++;
           c.j--;
       }
    }
};

class S2 : public System
{
public: 
    S2()
    {
        update_mask<C2>();
    }
    virtual ~S2() override {}
    virtual void update(EntityManager & em) override {Console::get()<<"comp C2"<<"\n";}
};

class S3 : public System
{
public: 
    S3()
    {
        update_mask<C3>();
    }
    virtual ~S3() override {}
    virtual void update(EntityManager & em) override {Console::get()<<"comp C3"<<"\n";}
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

    Entity a1(EntityStuff::get().get_entity_manager());
    Entity a2(EntityStuff::get().get_entity_manager());
    Entity a3(EntityStuff::get().get_entity_manager());
    a1.create();
    a2.create();
    a3.create();

    //1 .do a2 sie przyisuje a do a1 już nie;
    //  ~~~~^~~~~ vector EntityMenager::entities zmenia wskaźnik danych NAPRAWIC
    //2 .inicjalizacja componentow z assign
    //3 .test systemow ( przeanalizować przesyłanie wskaźników komponentów do systemow)
    //4 .event system
    //5. ogarnąć kasowanie
    //      I komponentow
    //      II entitow

    auto & cc11 = a1.assign<C>().getComponent();
    auto & cc12 = a2.assign<C>().getComponent();
    cc11.i = 0;
    cc11.j = 100;
    cc12.i = 10;
    cc12.j = 110;
    a1.assign<C2>();
    a1.assign<C3>();
    a2.assign<C3>();

	
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
        //if(ev.key.code == sf::Keyboard::B)
           // EntityStuff::get().addComponent<C3>(1);
        /*if(ev.key.code == sf::Keyboard::C)
			em.addEntity<Cc>();
		if(ev.key.code == sf::Keyboard::E)
	*/
	}
}
