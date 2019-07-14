#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <SFML/Graphics.hpp>
#include "colidable.h"
#include "../console.h"

class Dynamic : public Colidable
{
public:
    sf::Vector2f velocity, const_acceleration = {0.0f,500.0f};
    float decelleration_rate = 300.0f; // pixel/s^2

    Dynamic();

    void update(float dt);
    void correct_collision(const Colidable & other);

};

#endif // DYNAMIC_H
