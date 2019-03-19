#include "Console.h"
#include <exception>

Console * Console::instance = nullptr;
sf::RenderWindow * Console::main_window = nullptr;

Console::Console(sf::RenderWindow & window)
: window(window)
{
      if( ! font.loadFromFile( "Arial.ttf" ) )
	    throw std::runtime_error( " no font.ttf ");	    
      text.setFont(font);
      text.setFillColor(sf::Color::White);
      text.setCharacterSize(character_size);
      texture.create(400,300);
      area.setTexture(texture.getTexture());

      area.setOrigin(area.getLocalBounds().width/2, area.getLocalBounds().height/2);
      area.setScale(2.0f, -2.0f);
      area.setPosition(area.getLocalBounds().width, area.getLocalBounds().height);

      content[0] = "Android Console v0.1";
      content[1] = "Hello";
      addContent("\n");
}

void Console::show(bool is)
{
    is_shown = is;
}

void Console::draw()
{
    texture.clear(sf::Color(0,0,0,128));

    int row = 0;
    for (int i = top; i != bottom; (++i) %= constent_size, ++row) {
        text.setString(content[i]);
        text.setPosition(5,row*character_size);
        texture.draw(text);
    }
}

void Console::display()
{
    if(is_shown)
        window.draw(area);
}

void Console::set_window(sf::RenderWindow *window)
{
    main_window = window;
}

Console &Console::get()
{
    if(! instance ) instance = new Console(*main_window);
    return *instance;
}

void Console::release()
{
    if(instance)
    {
        delete instance;
        instance = nullptr;
    }
}

void Console::addContent(const std::string &text)
{
    content[bottom] = content[bottom] + text;
    draw();
}

void Console::nextLine()
{
    bottom = (bottom+1)%constent_size;
    if( bottom == top ) {
        content[top] = "";
        top = (top +1)% constent_size;
       }
    draw();
}
	
