#ifndef UI_H_
#define UI_H_
#include <SFML/Graphics.hpp>
#include <vector>

#include "touchable.h"
#include "renderer.h"

struct Description
{
	sf::Vector2f pos;
	std::vector <sf::Vector2f> vert;
};

class UI
{
	std::vector <Touchable* > nodes;
public:
	UI();
	~UI();
	void addNode(Touchable * t );
	void createDefault();
	int getSize(){return nodes.size();}
	
	void setHandler(int t, TouchableHandler & h);
	
	enum Default
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		BUTTON
	};
};

#endif /* DFAULTUI_H_ */
