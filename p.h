 #ifndef P_H
#define P_H

#include <SFML/Graphics.hpp>
#include "program.h"
#include "console.h"
#include "touchable.h"
#include "ui.h"
#include "EntityStuff/entity_stuff.h"
#include "programstage.h"

#include "resource_manager.h"
#include "ScriptStuff/script.h"

class P : public ProgramStage 
{
    sf::RenderWindow & win;
    EntityStuff es;
    sf::CircleShape s;
    UI ui;
	    
public:
    P(sf::RenderWindow & win);
    ~P() override;
    virtual void init() override;
    virtual void render(sf::RenderWindow & win) override;
    virtual void update(double dt) override;
    virtual void input(sf::Event &ev) override;
	virtual void release() override;
};


#endif // P_H
