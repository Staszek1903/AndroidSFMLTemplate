#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "Console.h"
#include <SFML/Graphics.hpp>

class Program 
{
	void input();
	void render();
protected:
	sf::RenderWindow win;
 
    virtual void onRender();
	virtual void onUpdate();
	virtual void onEvent(sf::Event &ev);
	
public:
	Program();
    virtual ~Program();
	
	void run();
};

#endif /* PROGRAM_H_ */
