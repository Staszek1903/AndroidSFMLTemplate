#include "Console.h"
#include <exception>

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
      area.setScale(1.0f, -1.0f);
      area.setPosition(area.getLocalBounds().width/2, area.getLocalBounds().height/2);

      content[0] = "Android Console v0.1";
      content[1] = "Hello";
}



void Console::show(bool is)
{
    is_shown = is;
}

void Console::draw()
{
    if(is_shown)
    {
        texture.clear(sf::Color(0,0,0,128));

        int row = 0;
        for (int i = top; i != bottom; ++i, ++row) {
            i = i%constent_size;
            text.setString(content[i]);
            text.setPosition(5,row*character_size);
            texture.draw(text);
            if(i == bottom) break;
        }


        window.draw(area);
    }
}

void Console::addContent(const std::string &text)
{
    content[bottom] = text;
    bottom = (bottom+1)%constent_size;
    if( bottom == top ) top = (top +1)% constent_size;

}
	
