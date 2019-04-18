#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "Console.h"
#include "touchbuffer.h"
#include "Renderer.h"
#include "touchable.h"
#include <SFML/Graphics.hpp>

class ConsoleButtonHandler : public TouchableHandler
{
    virtual void handle(const TouchEvent & ev) override;
};

class Program 
{
	void input();
	void render();
protected:
	sf::RenderWindow win;
 	Touchable console_button;
 	ConsoleButtonHandler cb_handler;
 
    virtual void onRender();
	virtual void onUpdate();
	virtual void onEvent(sf::Event &ev);
	
public:
	Program();
    virtual ~Program();
	
	void run();
};


#endif /* PROGRAM_H_ */
