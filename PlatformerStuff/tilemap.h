#ifndef TILEMAP_H
#define TILEMAP_H

#include "colidable.h"
#include "dynamic.h"

/**
 * @brief The TileMap class przowywuje wszytkie statyczne elementy mapy
 *
 */
class TileMap : public sf::Drawable
{
    std::vector <sf::Sprite> tile_map;

    std::vector<sf::Vector2f> debug_places;
public:
    TileMap();

    void add(const sf::Vector2f &pos, const sf::Texture & text);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void colide(Colidable & coll);
};

#endif // TILEMAP_H
