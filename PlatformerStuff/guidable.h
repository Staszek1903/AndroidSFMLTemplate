#ifndef GUIDABLE_H
#define GUIDABLE_H

#include "colidable.h"
#include "console.h"

class Guidable : public Colidable
{
    std::vector <sf::Vector2f> points;
    std::size_t active_index = 0;
    float speed = 100;
    bool active = true;

public:
    Guidable();


    virtual void update(float dt) override;
    bool getActive() const;
    void setActive(bool value);
    float getSpeed() const;
    void setSpeed(float value);

    void addPoint(const sf::Vector2f &point);
};

#endif // GUIDABLE_H
