#include "guidable.h"

bool Guidable::getActive() const
{
    return active;
}

void Guidable::setActive(bool value)
{
    active = value;
}

float Guidable::getSpeed() const
{
    return speed;
}

void Guidable::setSpeed(float value)
{
    speed = value;
}

void Guidable::addPoint(const sf::Vector2f &point)
{
    points.push_back(point);
}

Guidable::Guidable()
{

}

void Guidable::update(float dt)
{
    if(active && points.size() != 0)
    {
        auto pos = getPosition();
        auto active_point = points.at(active_index);
        auto target = active_point - pos;
        float target_distance = stuff::Vect::lenght(target);

        if(target_distance < speed*dt)
        {
            active_index = (active_index+1) % points.size();
            return;
        }

        stuff::Vect::normalize(target);
        velocity = target * speed;
    }
    else
    {
        velocity = sf::Vector2f(0,0);
    }

    Dynamic::update(dt);

    Console::get()<<"POS: "<<getPosition()<<"\n";
}
