
struct Ev : public Event<Ev>
{
	Ev(Entity en) : en(en){;}
	Entity en;	
};

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

class S : public System, public Receiver
{
public: 
    S(EventManager & vm)
    {
    		vm.addReceiver(this);
    		update_event_mask<Ev>();
    }
    virtual ~S() override {}
protected:
    virtual void update(EntityManager & em, EventManager & vm, double dt) override
    {

        Console::get()<<"Comp C\n";
       for(Entity en : get_entities<C>(em))
       {
           auto c = en.component<C>();
           Console::get()<<" i: "<<c->i<<"\n j: "<<c->j<<"\n";

           c->i++;
           c->j--;
       }
    }
    
    virtual void receive(BaseEvent * ev) override
    {
    	Console::get()<<"Event received\n";
    	if(is_type<Ev>(ev))
    	{
    		Ev * evev  = (Ev*)ev;
    		Console::get()<<"Event is type Ev\n";
    		C2 & c = evev->en.component< C2 >().getComponent();
    		c.a = 1.23f;
    	}
    }
};

class S2 : public System
{
public: 
    S2()
    {}
    virtual ~S2() override {}
    virtual void update(EntityManager & em, EventManager & vm, double dt) override
    {
        Console::get()<<"comp C2"<<"\n";
        for(Entity en : get_entities<C2,C3>(em))
        {
            auto c2 = en.component<C2>();
            auto c3 = en.component<C3>();

            Console::get()<<(*c3).s<<" : "<<(*c2).a<< "\n";

            (*c2).a *= 2;
            if((*c2).a > 100.0f)  vm.emit<Ev>(en);
        	{
        		//en.release();
        	}
        }
    }
};

/**
   
    	INIT
    es.addSystem<S>(es.get_event_manager());
    es.addSystem<S2>();

    Entity a1(es.get_entity_manager());
    Entity a2(es.get_entity_manager());
    Entity a3(es.get_entity_manager());
    a1.create();
    a2.create();
    a3.create();

    
    //5. ogarnąć kasowanie
    //      I komponentow
    //      II entitow
	// (nie defragmentowa pamieci po kasowaniu zrobic vector dostepnych miejsc)
	//ew funkcja do defragmentacji
	
    a1.assign<C>(1,1);
    a2.assign<C>(-100, 100);
    a1.assign<C2>(1.23);
    a1.assign<C3>("SIEMA KURWY");
    
    UPDATE:
    es.update_systems(0.0f);
	*/