#include "line.h"



Line::Line()
{
    setFillColor(sf::Color::White);
}

Line::Line(const sf::Vector2f &_begining, const sf::Vector2f &_end)
    :begining(_begining), end(_end)
{
    setFillColor(sf::Color::White);
    update_shape();
}

sf::Vector2f Line::getBegining() const
{
    return begining;
}

void Line::setBegining(const sf::Vector2f &value)
{
    begining = value;
    update_shape();
}

sf::Vector2f Line::getEnd() const
{
    return end;
}

void Line::setEnd(const sf::Vector2f &value)
{
    end = value;
    update_shape();
}

void Line::setVector(const sf::Vector2f &value)
{
    end = begining + value;
    update_shape();
}

float Line::getLenght()
{
    auto vect = begining - end;
    float lenght = Vect::lenght(vect);
    return lenght;
}

float Line::getThickness() const
{
    return thickness;
}

void Line::setThickness(float value)
{
    thickness = value;
    update_shape();
}

void Line::update_shape()
{
    float lenght = getLenght();
    sf::Vector2f size(lenght, thickness);
    auto vect = end - begining;
    auto origin = size/2.0f;
    auto pos = begining + (vect/2.0f);
    double rot = Vect::getRotationDegrees(vect);

    setSize(size);
    setOrigin(origin);
    setPosition(pos);
    setRotation(static_cast<float>(rot));
}
