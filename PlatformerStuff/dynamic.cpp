#include "dynamic.h"

Dynamic::Dynamic()
{

}

void Dynamic::update(float dt)
{
   // Console::get()<<"updating player dt:"<<dt<<" position_x:"<<getPosition().x<<"\n";
    auto pos = getPosition();
    pos = pos + (velocity*dt);

    velocity*=decelleration_rate;
    velocity += const_acceleration;
    setPosition(pos);
}

void Dynamic::correct_collision(const Colidable &other)
{

}
