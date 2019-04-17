 #ifndef P_H
#define P_H

#include <SFML/Graphics.hpp>
#include "Program.h"
#include "Console.h"
#include "touchable.h"
#include "ui.h"
#include "EntityStuff/EntityStuff.h"

class P : public Program
{
    sf::CircleShape s;
    UI ui;
	    
public:
    P();
    ~P();
    virtual void onRender() override;
    virtual void onUpdate() override;
    virtual void onEvent(sf::Event &ev) override;
};


#endif // P_H