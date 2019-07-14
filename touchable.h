#ifndef TOUCHABLE_H_
#define TOUCHABLE_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include "touchbuffer.h"
#include "console.h"
#include "renderer.h"

/**
 * @brief The TouchableHandler class is an obstract class for handler methode which is called on touchable interraction
 */
class TouchableHandler
{
public:
	virtual void handle(const TouchEvent & ev) =0;
    virtual ~TouchableHandler();
};


class Touchable : public TouchHandler, public sf::Shape
{
	std::vector <sf::Vector2f> points;
    std::function<void(const TouchEvent & ev)> handler;
		
public:
	Touchable(float x, float y, float w, float h);
	Touchable(float x, float y, const std::vector<sf::Vector2f > &points);
	virtual void handle(const TouchEvent & ev) override;
	virtual std::size_t getPointCount() const override;
	virtual sf::Vector2f getPoint(std::size_t i) const override;
	
	void create_rect(float w, float h);
	
  virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;		

    void setHandler(std::function<void(const TouchEvent &)> h);
    virtual ~Touchable() override;
};

#endif 
