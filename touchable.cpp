#include "touchable.h"

Touchable::Touchable(float x, float y, float w, float h)
	:handler(nullptr)
{
	setPosition(x,y);
	create_rect(w,h);
}

void Touchable::handle(const TouchEvent & ev)
{
	float x,y;
	Renderer::get().mapPtoC(ev.x,ev.y,x,y);
	auto b = getGlobalBounds();
		
	if(x>b.left&&x<(b.left+b.width)&& y>b.top&&y<(b.top+b.height))
	{/*
        if(handler)
        {
        	Console::get()<<"jest H\n";
        	handler->handle();
        } else
       		Console::get()<<"ni ma H\n";
   */     
	} 
}

std::size_t Touchable::getPointCount() const
{
	return points.size();
}

sf::Vector2f Touchable::getPoint(std::size_t i) const
{
	return points.at(i);
}

void Touchable::create_rect(float w, float h)
{
	points = { {0.0f,0.0f},
						{w, 0.0f},
						{w,h},
						{0.0f,h}};
	update();
}
	
void Touchable::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	const int size = points.size();
	sf::VertexArray array(sf::TriangleFan, size);
	
	states.transform = getTransform();
	states.texture = getTexture();
	
	for(int i=0; i<size; ++i)
	{
		array[i].position = points.at(i);
		array[i].color = getFillColor();
	}
	
	target.draw(array, states);
}

void Touchable::setHandler(TouchableHandler & h)
{
	handler = &h;
}

Touchable::~Touchable()
{
	if(handler) delete handler;
}