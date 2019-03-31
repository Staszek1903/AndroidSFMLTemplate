#ifndef TOUCHABLE_H_
#define TOUCHABLE_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include "touchbuffer.h"
#include "Console.h"
#include "Renderer.h"

class TouchableHandler
{
public:
	virtual void handle() =0;
	virtual ~TouchableHandler();
};

class Touchable : public TouchHandler, public sf::Shape
{
	std::vector <sf::Vector2f> points;
	TouchableHandler * handler;
		
public:
	Touchable(float x, float y, float w, float h);
	virtual void handle(const TouchEvent & ev) override;
	virtual std::size_t getPointCount() const override;
	virtual sf::Vector2f getPoint(std::size_t i) const override;
	
	void create_rect(float w, float h);
	
  virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;		

	void setHandler(TouchableHandler & h);
	virtual ~Touchable();
};

#endif 
