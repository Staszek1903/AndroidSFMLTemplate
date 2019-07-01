#ifndef COLIDABLE_H
#define COLIDABLE_H

#include <SFML/Graphics.hpp>
#include "vect.h"
#include "line.h"
#include "console.h"

/**
 * @brief The Colidable class detekts collision betwen sprites
 */
class Colidable : public sf::Sprite
{
    sf::Vector2f collision_point;
public:
    Colidable();
    /**
     * @brief is_colliding chcecks AABB collision and updates collision point
     * @param other sprite
     * @return true if collision occurs
     */
    bool is_colliding(const Colidable & other);
    /**
     * @brief get_collision_point
     * @return collision point
     */

    sf::Vector2f get_collision_point() const;

    sf::Vector2f get_global_center() const;

    float get_range(const Colidable &other);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif // COLIDABLE_H
