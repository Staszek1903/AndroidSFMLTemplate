#ifndef MENU_H
#define MENU_H

#include "IOStuff/programstage.h"
#include "IOStuff/touchable.h"
#include "p.h"

class Menu : public ProgramStage
{
    Touchable start{100,100,100,100},
    end{250,100,100,100};

    sf::Texture buttontexture;

public:
    Menu();

    // ProgramStage interface
public:
    virtual void init() override;
    virtual void input(sf::Event &ev) override;
    virtual void update(double dt) override;
    virtual void render(sf::RenderWindow &win) override;
    virtual void release() override;
};

#endif // MENU_H
