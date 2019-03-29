#ifndef RENDERER_H_
#define RENDERER_H_

#include <SFML/Graphics.hpp>
#define PIXEL_WIDTH 1200.0f

class Renderer
{
	static Renderer * instance;
	static sf::RenderWindow * win_pointer;
	
	sf::RenderWindow & win;
	sf::View view;
	float aspect_ratio= 0.0f;

	Renderer(sf::RenderWindow &win);
public:
	static void setWindow(sf::RenderWindow & win);
	static Renderer& get();
	static void release();
	
	void mapCtoP(float xi, float yi, float & xo,float & yo);
	void mapPtoC(float xi, float yi, float & xo,float & yo);
	
	void draw(sf::Drawable & d);	
};

#endif