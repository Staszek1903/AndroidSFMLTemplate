#include "p.h"

P::P(sf::RenderWindow &win) : win(win)
{}
 
 P::~P()
 {}

 struct Position
 {
     Position(float x, float y) : x(x), y(y) {}
     float x,y;
 };

 struct Texture
 {
     Texture( size_t index ) : index(index) {}
     size_t index;
 };

/* class RenderSystem : public System
 {
     sf::RenderWindow & win;
 public:
     RenderSystem(sf::RenderWindow & win) : win(win){}
     ~RenderSystem(){}
 protected:
     virtual void update(EntityManager & em, EventManager & vm, double dt) override
     {
        auto & rm = ResourceManager<sf::Texture>::get();

        for(Entity en : get_entities<Position, Texture>(em))
        {
            auto pos = en.component<Position>();
            auto texture = en.component<Texture>();
            sf::Texture & tex = rm.get_resource(texture->index);
            sf::Sprite sprite;
            sprite.setTexture(tex);
            sprite.setPosition(sf::Vector2f(pos->x, pos->y));
            win.draw(sprite);
        }
    }

 };*/
 
 void P::init()
 {
 	Console::get()<<"P::init\n";
    auto & tex_resource = ResourceManager<sf::Texture>::get();

    //es.addSystem<RenderSystem>(win);
	
    s.setPosition(sf::Vector2f (200,200));
    s.setFillColor(sf::Color::Blue);
    s.setRadius(100);
 	ui.createDefault();


    Script sc;
    sc.load_from_file("./textures/textures.conf");
    for (ScriptEntry en: sc.getEntry().get_array_value())
    {
        std::string id = en.get_name();
        std::string dir = "./textures/" + en.get_string_value();
        sf::Texture &tex = tex_resource.push(id);

        if(!tex.loadFromFile(dir))
            throw std::runtime_error(" cannot load texture at <" + dir + ">");
    }

    sc.release();

    sc.load_from_file("./levels/dev_room.lvl");

    std::map <int, std::string> elems;
    std::vector <std::vector<int> > lvl;
    for (ScriptEntry en : sc.getEntry().get_array_value())
    {

        std::string id = en.get_name();
        if(id == "lvl")
        {
            lvl.clear();
            for(ScriptEntry row : en.get_array_value())
            {
                lvl.resize(lvl.size()+1);
                for(ScriptEntry tile : row.get_array_value())
                {
                    lvl.back().push_back(tile.get_int_value());
                }
            }

            break;
        }
        std::string val = en.get_string_value();
        elems[std::atoi(id.c_str())] = val;
    }


    int x = 100, y = 100;
    for(auto row : lvl)
    {
        for(int tile : row)
        {
            x+=32;
            if(elems.at(tile) == "nothing")
                continue;
            if(elems.at(tile) == "player")
            {
                hero.setTexture(tex_resource.get_resource(elems.at(tile)));
                hero.setPosition(x,y);
                hero.velocity = {100,0};
                continue;
            }
            //Entity en(es.get_entity_manager());
            //en.create();
            //en.assign<Texture>(tex_resource.get_index(elems.at(tile)));
            //en.assign<Position>(x,y);

            tile_map.add(sf::Vector2f(x,y), tex_resource.get_resource(elems.at(tile)));

        }
        x = 0;
        y += 32;

    }
// END LVL LOADER

 }

void P::update(double dt)
{
    sf::Vector2f pos = s.getPosition();
    s.setPosition({pos.x+1,pos.y+1});
    hero.update(dt);
    tile_map.colide(hero);
}

void P::render(sf::RenderWindow & win)
{
    win.draw(s);
    win.draw(tile_map);
    win.draw(hero);
    //es.update_systems(0.0);
}

void P::input(sf::Event &ev)
{
	if(ev.type == sf::Event::TouchBegan)
	{  }
	if(ev.type == sf::Event::KeyPressed)
	{
		if(ev.key.code == sf::Keyboard::A)
        {//Script sc;	sc.load_from_file("./textures/textures.conf");
            hero.velocity.x = -100;
        }
        if(ev.key.code == sf::Keyboard::D)
        {
            hero.velocity.x = 100;
        }
        if(ev.key.code == sf::Keyboard::W)
        {
            hero.velocity.y = -200;
        }
        /*if(ev.key.code == sf::Keyboard::C)
			em.addEntity<Cc>();
		if(ev.key.code == sf::Keyboard::E)
	*/
	}
}

void P::release() 
{
    ResourceManager<sf::Texture>::release();
}
