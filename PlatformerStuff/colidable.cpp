#include "colidable.h"

Colidable::Colidable()
{

}

bool Colidable::is_colliding(const Colidable &other, ColisionData &data) const
{
    sf::FloatRect bb1 = getGlobalBounds();
    sf::FloatRect bb2 = other.getGlobalBounds();

    if(!AABBCollision(bb1, bb2))
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
    sf::Vector2f relativeVelocity = other.velocity - this->velocity; // predkość od tamtego do tego
    data.relative_velocity = - relativeVelocity;
    stuff::Vect::normalize(relativeVelocity);
    // tajemnicze zmienne mocy

    return RayCollisionDetection(bb1,bb2,leftTop,rightBottom,rayPos,relativeVelocity,data);
}


void Colidable::resolve_collision(Colidable &other, ColisionData &data, float bounciness, float friction)
{
    // odbicie predkości
    sf::Vector2f & a = data.normal,
            &b = data.relative_velocity;
    sf::Vector2f impact = sf::Vector2f( std::abs(a.x) * b.x , std::abs(a.y) * b.y) * (1.0f + bounciness);
    velocity -= impact*0.5f;
    other.velocity += impact*0.5f;

    // korekcja pozycji
    auto pos = getPosition();
    auto otherPos = other.getPosition();

    sf::Vector2f correction = (data.normal * data.penetration);
    setPosition(pos - correction*0.5f);
    other.setPosition(otherPos + correction*0.5f);

    //tarcie
    sf::Vector2f friction_normal = data.normal;
    std::swap( friction_normal.x, friction_normal.y );
    sf::Vector2f friction_force = sf::Vector2f( -data.relative_velocity.x * std::abs( friction_normal.x),
                                                -data.relative_velocity.y * std::abs( friction_normal.y));

    velocity += friction_force * friction * 0.5f;
    other.velocity -= friction_force * friction * 0.5f;
}

bool Colidable::is_colliding(const sf::Sprite &other, ColisionData &data) const
{
    //STARE ALE DZIALA
    sf::FloatRect bb1 = getGlobalBounds();
    sf::FloatRect bb2 = other.getGlobalBounds();

    if(!AABBCollision(bb1, bb2))
        return false;

    // rozbić na fcje calculate normal

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

    return RayCollisionDetection(bb1,bb2,leftTop,rightBottom,rayPos,relativeVelocity,data);
}

void Colidable::resolve_collision(ColisionData &data, float bounciness, float friction_x, float friction_y)
{
    // odbicie predkości
    sf::Vector2f & a = data.normal,
            &b = data.relative_velocity;
    velocity -= sf::Vector2f( std::abs(a.x) * b.x , std::abs(a.y) * b.y) * (1.0f + bounciness);

    // korekcja pozycji
    auto pos = getPosition();
    setPosition(pos - (data.normal * data.penetration));

    //tarcie
    sf::Vector2f friction_normal = data.normal;
    std::swap( friction_normal.x, friction_normal.y );
    sf::Vector2f friction_force = sf::Vector2f( -data.relative_velocity.x * std::abs( friction_normal.x) * friction_x,
                                                -data.relative_velocity.y * std::abs( friction_normal.y) * friction_y);

    velocity += friction_force;

}

void Colidable::updateSidesInfo(ColisionData &data)
{
    static int clear_delay =0; // wait 4 cycles until clearing olision information

    if(data.normal == NORMAL_UP)
    {
        collides_sides |= UP;
        clear_delay =0;
    }
    else if(data.normal == NORMAL_DOWN)
    {
        collides_sides |= DOWN;
        clear_delay =0;
    }
    else if(data.normal == NORMAL_RIGHT)
    {
        collides_sides |= RIGHT;
        clear_delay =0;
    }
    else if(data.normal == NORMAL_LEFT)
    {
        collides_sides |= LEFT;
        clear_delay =0;
    }
    else
    {
        if( clear_delay == 3 )
        {
            collides_sides = 0;
            clear_delay = 0;
        }
        ++clear_delay;
    }

}

bool Colidable::isColidingSide(std::size_t side)
{
    return ( collides_sides & side );
}

std::size_t Colidable::getColidingSide()
{
    return collides_sides;
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

/*#ifdef DEBUG_BUILD
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
#endif*/

}

