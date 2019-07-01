#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <SFML/Graphics.hpp>
#include "colidable.h"
#include "console.h"

class Dynamic : public Colidable
{
public:
    sf::Vector2f velocity, const_acceleration = {0.0f,9.0f};
    float decelleration_rate = 0.95f;

    Dynamic();

    void update(float dt);
    void correct_collision(const Colidable & other);

};

#endif // DYNAMIC_H
