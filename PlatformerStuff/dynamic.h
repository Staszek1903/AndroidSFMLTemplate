#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <SFML/Graphics.hpp>
#include "../console.h"
#include "../vect.h"

class Dynamic : public sf::Sprite
{
public:
    sf::Vector2f velocity, const_acceleration = {0.0f,500.0f};

    Dynamic();

    virtual void update(float dt);

};

#endif // DYNAMIC_H
