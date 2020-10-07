#include "menu.h"

Menu::Menu()
{}


void Menu::init()
{
    if(!buttontexture.loadFromFile("./textures/button.png"))
        throw std::runtime_error("texture not loaded ");



    start.setFillColor(sf::Color::White);
    start.setTexture(&buttontexture);
    start.setTextureRect({0,0,128,64});

    start.setHandler([&](const TouchEvent & ev){
        if(ev.state == TouchEvent::END){
            ProgramStage::next_stage<P>(*win);
            Console::get()<<"start\n";
        }
    });

    end.setHandler([&](const TouchEvent & ev){
        if(ev.state == TouchEvent::END){
            win->close();
            Console::get()<<"end\n";
        }
    });
}

void Menu::input(sf::Event &ev)
{
}

void Menu::update(double dt)
{
}

void Menu::render(sf::RenderWindow &win)
{
}

void Menu::release()
{
}
