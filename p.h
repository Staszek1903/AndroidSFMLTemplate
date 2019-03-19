#ifndef P_H
#define P_H

#include <SFML/Graphics.hpp>
#include "Program.h"
#include "Console.h"

class P : public Program
{
    sf::CircleShape s;
public:
    P();
    virtual void onRender() override;
    virtual void onUpdate() override;
    virtual void onEvent(sf::Event &ev) override;
};


#endif // P_H