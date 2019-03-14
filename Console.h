#include <SFML/Graphics.hpp>

class Console
{
	sf::Font font;
	sf::Text text;
public:
	sf::RenderWindow & window;
	
	Console(sf::RenderWindow &window);
	
	void draw();
};