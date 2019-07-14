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

void Dynamic::correct_collision(const Colidable &other)
{

}
