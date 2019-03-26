#include "Renderer.h"

Renderer::Renderer(sf::RenderWindow &win)
: win(win)
{
	auto mode = sf::VideoMode::getDesktopMode();
	aspect_ratio = (float)mode.height / (float) mode.width;
view.reset(sf::FloatRect(0,0,PIXEL_WIDTH, PIXEL_WIDTH*aspect_ratio));
	win.setView(view);	
}

void Renderer::draw(sf::Drawable & d)
{
	win.draw(d);
}

void draw(sf::Sprite & s)
{
}

void draw(sf::ConvexShape & s)
{
}