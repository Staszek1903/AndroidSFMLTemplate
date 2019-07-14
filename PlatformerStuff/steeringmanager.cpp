#include "steeringmanager.h"

Dynamic *SteeringManager::getSteered_entity() const
{
    return steered_entity;
}

void SteeringManager::setSteered_entity(Dynamic & value)
{
    steered_entity = &value;
}

int SteeringManager::getState() const
{
    return state;
}

void SteeringManager::setState(int value)
{
    state = value;
}

float SteeringManager::getNominal_velocity() const
{
    return nominal_velocity;
}

void SteeringManager::setNominal_velocity(float value)
{
    nominal_velocity = value;
}

float SteeringManager::getJump_velocity() const
{
    return jump_velocity;
}

void SteeringManager::setJump_velocity(float value)
{
    jump_velocity = value;
}

SteeringManager::SteeringManager()
    : nominal_velocity(0), steered_entity(nullptr)
{

}

void SteeringManager::update()
{
    if(!steered_entity) return;
    switch (state)
    {
    case STAY:
        break;
    case GO_LEFT:
        steered_entity->velocity.x = -nominal_velocity;
        break;
    case GO_RIGHT:
        steered_entity->velocity.x = nominal_velocity;
        break;
    case JUMP:
        steered_entity->velocity.y = -jump_velocity;
        state = STAY;
        break;
    default:
        break;

    }
}
