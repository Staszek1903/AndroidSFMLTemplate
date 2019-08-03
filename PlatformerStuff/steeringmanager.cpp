#include "steeringmanager.h"

Colidable *SteeringManager::getSteered_entity() const
{
    return steered_entity;
}

void SteeringManager::setSteered_entity(Colidable &value)
{
    steered_entity = &value;
}

std::size_t SteeringManager::getState() const
{
    return state;
}

void SteeringManager::setState(std::size_t value)
{
    if(!value) state = 0;
    state |= value;
}

void SteeringManager::unsetState(std::size_t value)
{
    state &= ~value;
}

float SteeringManager::getNominal_velocity() const
{
    return nominal_velocity;
}

void SteeringManager::setNominal_velocity(float value)
{
    nominal_velocity = value;
}

void SteeringManager::input(sf::Event &ev)
{
    if(ev.type == sf::Event::KeyPressed)
    {
        if(ev.key.code == sf::Keyboard::A)
            setState(SteeringManager::GO_LEFT);

        if(ev.key.code == sf::Keyboard::D)
            setState(SteeringManager::GO_RIGHT);

        if(ev.key.code == sf::Keyboard::W)
            setState(SteeringManager::JUMP);
    }
    if(ev.type == sf::Event::KeyReleased)
    {
        if(ev.key.code == sf::Keyboard::A)
            unsetState(SteeringManager::GO_LEFT);

        if(ev.key.code == sf::Keyboard::D)
            unsetState(SteeringManager::GO_RIGHT);
    }
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

    if(state & GO_LEFT && !( state & GO_RIGHT))
        steered_entity->velocity.x = -nominal_velocity;
    else if(state & GO_RIGHT && !(state & GO_LEFT))
        steered_entity->velocity.x = nominal_velocity;

    if((state & JUMP) && steered_entity->isColidingSide(Colidable::DOWN))
        steered_entity->velocity.y = -jump_velocity;

    unsetState(JUMP);
}
