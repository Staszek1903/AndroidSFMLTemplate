#include "dynamic.h"

Dynamic::Dynamic()
{

}

void Dynamic::update(float dt)
{
   // Console::get()<<"updating player dt:"<<dt<<" position_x:"<<getPosition().x<<"\n";
    auto pos = getPosition();
    pos = pos + (velocity*dt);

    sf::Vector2f decel = velocity;
    stuff::Vect::normalize(decel);
    if(stuff::Vect::lenght(velocity) > (decelleration_rate * dt))
        velocity -= (decel * (decelleration_rate * dt));
    velocity += const_acceleration* dt;
    setPosition(pos);
}

//void Dynamic::correct_collision(const Colidable &other)
//{
    /*auto immers = tile.get_collision_point(); // wektor od tile center do hero center
    sf::Vector2f good_distanece
            ((tile.getLocalBounds().width + coll.getLocalBounds().width)/2,
             (tile.getLocalBounds().height + coll.getLocalBounds().height)/2    );


    bool reverse = false;
    if(std::abs(immers.x) > std::abs(immers.y))
    {
        immers.y =0;
        good_distanece.y =0;
        if((reverse = immers.x < 0)) immers = -immers;
    }
    else
    {
        immers.x =0; // normalizujemy do pion poziom
        good_distanece.x = 0;
        if((reverse = immers.y < 0)) immers = -immers;
    }

    auto correction_vector = good_distanece - immers;
    coll.move(reverse? -correction_vector : correction_vector);
    static_cast<Dynamic*>(&coll)->velocity = sf::Vector2f(0,0);*/
//}
