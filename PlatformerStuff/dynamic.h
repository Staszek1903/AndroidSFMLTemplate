#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <SFML/Graphics.hpp>
#include "../console.h"
#include "../vect.h"

class Dynamic : public sf::Sprite
{
public:
    sf::Vector2f velocity, const_acceleration = {0.0f,500.0f};
    float decelleration_rate = 300.0f; // pixel/s^2

    Dynamic();

    void update(float dt);
    //void correct_collision(const Colidable & other);
    void get_collision_normal();

};

#endif // DYNAMIC_H
