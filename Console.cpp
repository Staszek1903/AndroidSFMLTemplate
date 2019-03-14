#include "Console.h"
#include <exception>

Console::Console(sf::RenderWindow & window)
: window(window)
{
	  if( ! font.loadFromFile( "font.ttf" ) )
	    throw std::runtime_error( " no font.ttf ");
	    
	  text.setFont(font);
	  
}

void Console::draw()
{
	sf::CircleShape c;
	c.setFillColor(sf::Color::Black);
	c.setPointCount(3);
	c.setPosition(sf::Vector2f(300,300));
	c.setRadius(100);
	window.draw(c);
}
	