#include "tilemap.h"

TileMap::TileMap()
{

}

void TileMap::add(const sf::Vector2f &pos, const sf::Texture &text)
{
    sf::Sprite c;
    c.setPosition(pos);
    c.setTexture(text);
    tile_map.push_back(c);
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for(auto & tile : tile_map){
        target.draw(tile);
    }

    for(auto d : debug_places)
    {
        sf::CircleShape c;
        c.setRadius(10);
        c.setPosition( d );
        c.setFillColor(sf::Color::Green);
        target.draw(c);
    }
}

void TileMap::colide(Colidable &coll)
{
    debug_places.clear();
    for(auto & tile : tile_map){
        ColisionData data;
        if(coll.is_colliding(tile, data))
        {
            debug_places.push_back(tile.getPosition());
            Console::get()<<"JEST COLLISION "<<data.normal.x<<" "<<data.normal.y
                         <<" PEN: "<< data.penetration<<" VEL: x:"<<coll.velocity.x<<" y: "<<coll.velocity.y<<"\n";
            coll.resolve_collision(data, 0.0f);
        }
    }
}
