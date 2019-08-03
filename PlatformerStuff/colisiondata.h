#ifndef COLISIONDATA_H
#define COLISIONDATA_H

#include <SFML/Graphics.hpp>
#include <assert.h>

#define NORMAL_UP       sf::Vector2f(0.0f, -1.0f)
#define NORMAL_DOWN     sf::Vector2f(0.0f, 1.0f)
#define NORMAL_LEFT     sf::Vector2f(-1.0f, 0.0f)
#define NORMAL_RIGHT    sf::Vector2f(1.0f, 0.0f)

struct ColisionData
{
    ColisionData();
    sf::Vector2f colision_point, normal;
    sf::Vector2f relative_velocity;
    float penetration;
};

bool AABBCollision(const sf::FloatRect & bb1, const sf::FloatRect & bb2);

/**
 * @brief RayCollisionDetection checks collision between ray and a AABB object
 * @param leftTop corner of AABB object
 * @param rightBottom corner of AABB object
 * @param rayPosition
 * @param rayDirection normalised vector
 * @param normal returned calculaterd normal
 * @return if collision detected
 */
bool RayCollisionDetection( const sf::FloatRect & bb1,
                            const sf::FloatRect & bb2,
                            const sf::Vector2f &leftTop,
                            const sf::Vector2f &rightBottom,
                            const sf::Vector2f &rayPosition,
                            const sf::Vector2f &rayDirection,
                            ColisionData & data);

#endif // COLISIONDATA_H
