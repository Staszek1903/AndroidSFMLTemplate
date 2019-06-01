#include "p.h"


P::P()
{}
 
 P::~P()
 {}
 
 void P::init()
 {
 	Console::get()<<"P::init\n";
    auto & tex_resource = ResourceManager<sf::Texture>::get();
	
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
    for (ScriptEntry en : sc.getEntry().get_array_value())
    {

        std::string id = en.get_name();
        if(id == "map")
        {
            break;
        }
        std::string val = en.get_string_value();
        elems[std::atoi(id.c_str())] = val;

    }

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
	{  }
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
{
    ResourceManager<sf::Texture>::release();
}
