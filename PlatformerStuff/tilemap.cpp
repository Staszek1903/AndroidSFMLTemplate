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

void TileMap::add(const sf::Vector2f &pos, const sf::Texture &text, std::vector<sf::Vector2f> points)
{
    Guidable g;
    g.setPosition(pos);
    g.setTexture(text);
    for(auto p : points) g.addPoint(p);
    guidables.push_back(g);
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for(auto & tile : tile_map){
        target.draw(tile);
    }

    for( auto & g : guidables)
        target.draw(g);

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
    bool collided = false; // potrzebne do udatowania collision info

    ColisionData data;
    for(auto & tile : tile_map){
        data = ColisionData();
        if(coll.is_colliding(tile, data))
        {
            debug_places.push_back(tile.getPosition());
            //Console::get()<<"JEST COLLISION "<<data.normal.x<<" "<<data.normal.y
            //              <<" PEN: "<< data.penetration<<" VEL: x:"<<coll.velocity.x<<" y: "<<coll.velocity.y<<"\n";

            coll.resolve_collision(data, 0.0f, 0.4f,0.1f);
            coll.updateSidesInfo(data);
            collided = true;

        }
    }

    for(auto & g : guidables){
        data = ColisionData();
        if(coll.is_colliding(g,data))
        {
            coll.resolve_collision(data, 0.0f,0.4f,0.1f);
            coll.updateSidesInfo(data);
            collided = true;
        }
    }
    if(!collided) coll.updateSidesInfo(data);

    // Stany sie torche blokują; jak bedzie ci sie chciało popraw
    //Console::get() << "sth" <<std::bitset<8>(coll.getColidingSide())<< "\n";

}

void TileMap::update(float dt)
{
    for(auto & g : guidables)
    {
        g.update(dt);
    }
}
