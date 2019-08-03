#ifndef STEERINGMANAGER_H
#define STEERINGMANAGER_H

#include "colidable.h"

class SteeringManager
{
    float nominal_velocity;
    float jump_velocity;
    std::size_t state;
    Colidable * steered_entity;

public:

    enum
    {
        STAY        = 0,
        GO_LEFT     = (1<<0),
        GO_RIGHT    = (1<<1),
        GO_DOWN     = (1<<2),
        JUMP        = (1<<3)
    };

    SteeringManager();
    SteeringManager(const SteeringManager &) = delete;
    void operator=(const SteeringManager*) =  delete;

    Colidable *getSteered_entity() const;
    void setSteered_entity(Colidable &value);
    std::size_t getState() const;
    void setState(std::size_t value);
    void unsetState(std::size_t value);
    float getNominal_velocity() const;
    void setNominal_velocity(float value);

    void input(sf::Event & ev);
    void update();

    float getJump_velocity() const;
    void setJump_velocity(float value);
};

#endif // STEERINGMANAGER_H
