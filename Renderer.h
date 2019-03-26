#include <SFML/Graphics.hpp>
//#include "Console.h"
#define PIXEL_WIDTH 1000.0f

class Renderer
{
	sf::RenderWindow & win;
	sf::View view;
	float aspect_ratio= 0.0f;
	public:
	Renderer(sf::RenderWindow &win);
	void draw(sf::Drawable & d);
	void draw(sf::Sprite & s);
	void draw(sf::ConvexShape & s);	
};