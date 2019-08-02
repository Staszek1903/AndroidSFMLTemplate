#include "colidable.h"

Colidable::Colidable()
{

}

bool Colidable::is_colliding(const Colidable &other, ColisionData &data) const
{
    /* STARE ALE DZIALA
    sf::FloatRect bb1 = getGlobalBounds();
    sf::FloatRect bb2 = other.getGlobalBounds();

    if(!(bb1.top < bb2.top+bb2.height && bb2.top < bb1.top + bb1.height &&
            bb1.left < bb2.left+bb2.width && bb2.left < bb1.left+bb1.width))
        return false;
    return true;
    */

    sf::FloatRect bb1 = getGlobalBounds();
    sf::FloatRect bb2 = other.getGlobalBounds();

    // MAGIA STACK OVERFLOW:
    // kolizja AABB vs ray

    //AABB:
    sf::Vector2f leftTop(bb1.left, bb1.top);
    sf::Vector2f rightBottom(bb1.left + bb1.width + bb2.width,
                             bb1.top + bb1.height + bb2.height);

    //RAY
    sf::Vector2f rayPos(bb2.left, bb2.top);
    sf::Vector2f relativeVelocity = other.velocity - this->velocity; // predkość od tamtego do tego

    sf::Vector2f rayVelocityFrac( 1.0f/relativeVelocity.x, 1.0f/relativeVelocity.y); //odwrotnosc predkosci od tamtego do tego

    // tajemnicze zmienne mocy

    float t1 = (rightBottom.x - rayPos.x)* rayVelocityFrac.x,
          t2 = (leftTop.x - rayPos.x) * rayVelocityFrac.x,
          t3 = (rightBottom.y - rayPos.y) * rayVelocityFrac.y,
          t4 = (leftTop.y - rayPos.y) * rayVelocityFrac.y;

    float tmax = std::min(std::max(t1,t2), std::max(t3,t4));
    float tmin = std::max(std::min(t1,t2), std::min(t3,t4));

    if(tmin > tmax) return false;

    //data.relative_velocity = stuff::Vect::lenght(relativeVelocity);

    return true;
}


void Colidable::resolve_collision(Colidable &other, ColisionData &data)
{

}

bool Colidable::is_colliding(const sf::Sprite &other, ColisionData &data) const
{
    //STARE ALE DZIALA
    sf::FloatRect bb1 = getGlobalBounds();
    sf::FloatRect bb2 = other.getGlobalBounds();

    if(!(bb1.top < bb2.top+bb2.height && bb2.top < bb1.top + bb1.height &&
            bb1.left < bb2.left+bb2.width && bb2.left < bb1.left+bb1.width))
        return false;

    // MAGIA STACK OVERFLOW:
    // kolizja AABB vs ray

    //AABB:
    sf::Vector2f center_pos = get_global_center();
    sf::Vector2f sum_half_size( (bb1.width + bb2.width)/2, (bb1.height + bb2.height)/2);
    sf::Vector2f leftTop(center_pos.x - sum_half_size.x, center_pos.y - sum_half_size.y);
    sf::Vector2f rightBottom(center_pos.x + sum_half_size.x, center_pos.y + sum_half_size.y);

    //RAY
    sf::Vector2f rayPos((bb2.width + bb2.left + bb2.left)/2,(bb2.height + bb2.top + bb2.top)/2); // obliczanie global center
    sf::Vector2f relativeVelocity = - this->velocity; // predkość od tamtego do tego
    data.relative_velocity = - relativeVelocity;
    stuff::Vect::normalize(relativeVelocity);


    sf::Vector2f rayVelocityFrac( 1.0f/relativeVelocity.x, 1.0f/relativeVelocity.y); //odwrotnosc predkosci od tamtego do tego

    // tajemnicze zmienne mocy

    float t1 = (rightBottom.x - rayPos.x)* rayVelocityFrac.x,
          t2 = (leftTop.x - rayPos.x) * rayVelocityFrac.x,
          t3 = (rightBottom.y - rayPos.y) * rayVelocityFrac.y,
          t4 = (leftTop.y - rayPos.y) * rayVelocityFrac.y;

    float tmax = std::min(std::max(t1,t2), std::max(t3,t4));
    float tmin = std::max(std::min(t1,t2), std::min(t3,t4));

    float t = 0;
    if(tmax < 0 || tmin > tmax) return false; //  t = tmax;
    t = tmin;

    if(t == t1)
    {
        data.normal = NORMAL_RIGHT;
        data.penetration =
                (bb1.left + bb1.width) - bb2.left;
        data.colision_point = sf::Vector2f(bb1.left + bb1.width, bb1.top);
    }
    else if(t == t2)
    {
        data.normal = NORMAL_LEFT;
        data.penetration =
                (bb2.left + bb2.width)- bb1.left;
        data.colision_point = sf::Vector2f(bb1.left, bb1.top + bb1.height);
    }
    else if(t == t3)
    {
        data.normal = NORMAL_DOWN;
        data.penetration =
                (bb1.top + bb1.height) - bb2.top;
        data.colision_point = sf::Vector2f(bb1.left + bb1.width, bb1.top + bb1.height);
    }
    else if(t == t4)
    {
        data.normal = NORMAL_UP;
        data.penetration =
                (bb2.top + bb2.height) - bb1.top;
        data.colision_point = sf::Vector2f(bb1.left, bb1.top);
    }
    else assert(false);

    return true;
}

void Colidable::resolve_collision(ColisionData &data, float bounciness)
{
    sf::Vector2f & a = data.normal,
            &b = data.relative_velocity;
    velocity -= sf::Vector2f( std::abs(a.x) * b.x , std::abs(a.y) * b.y) * (1.0f + bounciness);

    auto pos = getPosition();
    setPosition(pos - (data.normal * data.penetration));
}

sf::Vector2f Colidable::get_global_center() const
{
    sf::FloatRect bb = getGlobalBounds();
    float y = bb.top + (bb.height)/2;
    float x = bb.left + (bb.width)/2;
    return sf::Vector2f(x,y);
}

sf::Vector2f Colidable::get_half_size() const
{
    sf::FloatRect bb = getGlobalBounds();
    float x = bb.width/2;
    float y = bb.height/2;
    return sf::Vector2f(x,y);
}

float Colidable::get_range(const Colidable &other)
{
    auto global_center1 = get_global_center();
    auto global_center2 = other.get_global_center();
    auto d = global_center1 - global_center2;
    float ret = stuff::Vect::lenght(d);
    return ret;
}

void Colidable::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Sprite sp = static_cast<sf::Sprite>(*this);
    target.draw(sp);

#ifdef DEBUG_BUILD
    stuff::Line l (get_global_center(),{0,0});
    sf::Vector2f vect =  sf::Vector2f(16,16) ;
    l.setVector(vect);
    l.setFillColor(sf::Color::Magenta);
    target.draw(l);

    auto b = getGlobalBounds();
    std::array<sf::Vector2f,4> vert = { sf::Vector2f(b.left, b.top),
                            sf::Vector2f(b.left + b.width, b.top),
                            sf::Vector2f(b.left + b.width, b.top + b.height),
                            sf::Vector2f(b.left, b.top + b.height)};

    std::array<stuff::Line,4> bb = { stuff::Line(vert[0], vert[1]),
                 stuff::Line(vert[1], vert[2]),
                 stuff::Line(vert[2], vert[3]),
                 stuff::Line(vert[3], vert[0]) };

    for(auto & l : bb){
        //Console::get()<<"bb draw"<<b.left<<"\n";
        l.setFillColor(sf::Color::Green);
        l.setThickness(2);
        target.draw(l);
    }

    //Console::get()<<"collision point = "<<collision_point<<"\n";
#endif

}

