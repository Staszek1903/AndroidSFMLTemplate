#include "Renderer.h"

Renderer * Renderer::instance = nullptr;
sf::RenderWindow * Renderer::win_pointer = nullptr;

Renderer::Renderer(sf::RenderWindow &win)
: win(win)
{
	auto mode = sf::VideoMode::getDesktopMode();
	aspect_ratio = (float)mode.height / (float) mode.width;
	
	if(aspect_ratio >1.0f) 
	{
		aspect_ratio = 1.0f/aspect_ratio;
		view.setViewport(sf::FloatRect(0.0f,0.0f, 1.2f, aspect_ratio*aspect_ratio));
	}
	else
		view.setViewport(sf::FloatRect(0.0f,0.0f,1.2f,1.0f));
		
view.reset(sf::FloatRect(0,0,PIXEL_WIDTH, PIXEL_WIDTH*aspect_ratio));
	win.setView(view);	
}

void Renderer::mapCtoP(float xi, float yi, float & xo,float & yo)
{
	auto out = win.mapCoordsToPixel(sf::Vector2f (xi,yi));
	xo = out.x;
	yo = out.y;
}

void Renderer::mapPtoC(float xi, float yi, float & xo,float & yo)
{
	auto out = win.mapPixelToCoords(sf::Vector2i(xi,yi));
	xo = out.x;
	yo = out.y;
}
	
void Renderer::draw(sf::Drawable & d)
{
	win.draw(d);
}

void Renderer::setWindow(sf::RenderWindow & win)
{
	win_pointer = &win;
}

Renderer& Renderer::get()
{
 	if(!instance)
 		instance = new Renderer(*win_pointer);
 		
 	return *instance;
}

void Renderer::release()
{
	delete instance;
	instance = nullptr;
}
	