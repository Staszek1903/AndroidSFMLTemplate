 #ifndef P_H
#define P_H

#include <SFML/Graphics.hpp>
#include "program.h"
#include "console.h"
#include "touchable.h"
#include "ui.h"
#include "EntityStuff/entity_stuff.h"

#include "resource_manager.h"
#include "ScriptStuff/script.h"

class P : public Program
{
    sf::CircleShape s;
    UI ui;
	    
public:
    P();
    ~P() override;
    virtual void onRender() override;
    virtual void onUpdate() override;
    virtual void onEvent(sf::Event &ev) override;
};


#endif // P_H
