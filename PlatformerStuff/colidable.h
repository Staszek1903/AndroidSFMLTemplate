#ifndef COLIDABLE_H
#define COLIDABLE_H

#include <SFML/Graphics.hpp>
#include "vect.h"
#include "../line.h"
#include "../console.h"
#include "dynamic.h"
#include "colisiondata.h"
#include <assert.h>

/**
 * @brief The Colidable class detekts collision betwen sprites
 */
class Colidable : public Dynamic
{
public:
    Colidable();
    /**
     * @brief is_colliding chcecks AABB collision and updates collision point
     * @param other sprite
     * @return true if collision occurs
     */
    bool is_colliding(const Colidable & other, ColisionData & data) const;

    void resolve_collision(Colidable & other,  ColisionData & data);

    bool is_colliding(const sf::Sprite & other, ColisionData & data) const;

    void resolve_collision(ColisionData & data, float bounciness);

    sf::Vector2f get_global_center() const;
    sf::Vector2f get_half_size() const;

    float get_range(const Colidable &other);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif // COLIDABLE_H
