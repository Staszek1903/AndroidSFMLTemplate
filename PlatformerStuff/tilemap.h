#ifndef TILEMAP_H
#define TILEMAP_H

#include "colidable.h"
#include "dynamic.h"

class TileMap : public sf::Drawable
{
    std::vector <Colidable> tile_map;
public:
    TileMap();

    void add(const sf::Vector2f &pos, const sf::Texture & text);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void colide(Colidable & coll);
};

#endif // TILEMAP_H
