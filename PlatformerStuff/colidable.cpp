#include "colidable.h"

Colidable::Colidable()
    : collision_point({0,0})
{

}

bool Colidable::is_colliding(const Colidable &other)
{
    sf::FloatRect bb1 = getGlobalBounds();
    sf::FloatRect bb2 = other.getGlobalBounds();

    if(!(bb1.top < bb2.top+bb2.height && bb2.top < bb1.top + bb1.height &&
            bb1.left < bb2.left+bb2.width && bb2.left < bb1.left+bb1.width))
        return false;

    sf::Vector2f global_center1 = get_global_center();
    sf::Vector2f global_center2 = other.get_global_center();

    auto offset = global_center2 - global_center1;
    //Vect::normalize(offset);
    collision_point = offset;

    return true;
}

sf::Vector2f Colidable::get_collision_point() const
{
    return collision_point;
}

sf::Vector2f Colidable::get_global_center() const
{
    sf::FloatRect bb = getGlobalBounds();
    float y = bb.top + (bb.height)/2;
    float x = bb.left + (bb.width)/2;
    return sf::Vector2f(x,y);
}

float Colidable::get_range(const Colidable &other)
{
    auto global_center1 = get_global_center();
    auto global_center2 = other.get_global_center();
    auto d = global_center1 - global_center2;
    float ret = Vect::lenght(d);
    return ret;
}

void Colidable::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Sprite sp = static_cast<sf::Sprite>(*this);
    target.draw(sp);

#ifdef DEBUG_BUILD
    Line l (get_global_center(),{0,0});
    sf::Vector2f vect = (Vect::len_sq(collision_point) < std::numeric_limits<float>::epsilon())? sf::Vector2f(16,16) : collision_point;
    l.setVector(vect);
    l.setFillColor(sf::Color::Magenta);
    target.draw(l);

    auto b = getGlobalBounds();
    std::array<sf::Vector2f,4> vert = { sf::Vector2f(b.left, b.top),
                            sf::Vector2f(b.left + b.width, b.top),
                            sf::Vector2f(b.left + b.width, b.top + b.height),
                            sf::Vector2f(b.left, b.top + b.height)};

    std::array<Line,4> bb = { Line(vert[0], vert[1]),
                 Line(vert[1], vert[2]),
                 Line(vert[2], vert[3]),
                 Line(vert[3], vert[0]) };

    for(auto & l : bb){
        //Console::get()<<"bb draw"<<b.left<<"\n";
        l.setFillColor(sf::Color::Green);
        l.setThickness(2);
        target.draw(l);
    }

    //Console::get()<<"collision point = "<<collision_point<<"\n";
#endif
}

