#include "tilemap.h"

TileMap::TileMap()
{

}

void TileMap::add(const sf::Vector2f &pos, const sf::Texture &text)
{
    Colidable c;
    c.setPosition(pos);
    c.setTexture(text);
    tile_map.push_back(c);
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for(auto & tile : tile_map){
        target.draw(tile);
    }
}

void TileMap::colide(Colidable &coll)
{
    for(auto & tile : tile_map){
        if(tile.is_colliding(coll)){
            auto immers = tile.get_collision_point(); // wektor od tile center do hero center
            sf::Vector2f good_distanece
                    ((tile.getLocalBounds().width + coll.getLocalBounds().width)/2,
                     (tile.getLocalBounds().height + coll.getLocalBounds().height)/2    );

            float difference = std::abs(std::abs(immers.x) - std::abs(immers.y));
            Console::get()<<"diference: " << difference <<"\n";
            bool reverse = false;
            if( difference < 3.0f)
            {
                continue;
            }
            if(std::abs(immers.x) > std::abs(immers.y))
            {
                immers.y =0;
                good_distanece.y =0;
                if((reverse = immers.x < 0)) immers = -immers;
            }
            else
            {
                immers.x =0; // normalizujemy do pio poziom
                good_distanece.x = 0;
                if((reverse = immers.y < 0)) immers = -immers;
            }

            auto correction_vector = good_distanece - immers;
            coll.move(reverse? -correction_vector : correction_vector);
        }
    }
}
