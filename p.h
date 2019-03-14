#ifndef P_H
#define P_H

#include <SFML/Graphics.hpp>
#include "Program.h"

class P : public Program
{
    sf::CircleShape s;
public:
    P();
    virtual void onRender() override;
    virtual void onUpdate() override;
};


#endif // P_H
