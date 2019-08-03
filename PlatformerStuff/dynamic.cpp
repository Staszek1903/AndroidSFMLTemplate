#include "dynamic.h"


Dynamic::Dynamic()
{

}

void Dynamic::update(float dt)
{
    // Console::get()<<"updating player dt:"<<dt<<" position_x:"<<getPosition().x<<"\n";
    auto pos = getPosition();
    pos = pos + (velocity*dt);

    velocity += const_acceleration* dt;
    setPosition(pos);
}
