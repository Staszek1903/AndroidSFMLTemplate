#ifndef COLISIONDATA_H
#define COLISIONDATA_H

#include <SFML/Graphics.hpp>

#define NORMAL_UP       sf::Vector2f(0.0f, -1.0f)
#define NORMAL_DOWN     sf::Vector2f(0.0f, 1.0f)
#define NORMAL_LEFT     sf::Vector2f(-1.0f, 0.0f)
#define NORMAL_RIGHT    sf::Vector2f(1.0f, 0.0f)

struct ColisionData
{
    sf::Vector2f colision_point, normal;
    sf::Vector2f relative_velocity;
    float penetration;
};

#endif // COLISIONDATA_H
