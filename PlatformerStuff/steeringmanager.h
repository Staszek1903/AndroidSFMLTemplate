#ifndef STEERINGMANAGER_H
#define STEERINGMANAGER_H

#include "dynamic.h"

class SteeringManager
{
    float nominal_velocity;
    float jump_velocity;
    int state;
    Dynamic * steered_entity;
public:

    enum
    {
        STAY,
        GO_LEFT,
        GO_RIGHT,
        GO_DOWN,
        JUMP
    };

    SteeringManager();
    SteeringManager(const SteeringManager &) = delete;
    void operator=(const SteeringManager*) =  delete;

    Dynamic *getSteered_entity() const;
    void setSteered_entity(Dynamic &value);
    int getState() const;
    void setState(int value);
    float getNominal_velocity() const;
    void setNominal_velocity(float value);

    void update();

    float getJump_velocity() const;
    void setJump_velocity(float value);
};

#endif // STEERINGMANAGER_H
