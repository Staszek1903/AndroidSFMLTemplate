#include "colisiondata.h"

ColisionData::ColisionData()
    :colision_point(sf::Vector2f(0,0)),
      normal(sf::Vector2(0,0)),
      relative_velocity(sf::Vector2f(0,0)),
      penetration(0)
{}

bool AABBCollision(const sf::FloatRect &bb1, const sf::FloatRect &bb2)
{
    return (bb1.top < bb2.top+bb2.height && bb2.top < bb1.top + bb1.height &&
              bb1.left < bb2.left+bb2.width && bb2.left < bb1.left+bb1.width);
}


bool RayCollisionDetection(const sf::FloatRect & bb1,
                           const sf::FloatRect & bb2,
                           const sf::Vector2f &leftTop,
                           const sf::Vector2f &rightBottom,
                           const sf::Vector2f &rayPosition,
                           const sf::Vector2f &rayDirection,
                           ColisionData &data)
{
    sf::Vector2f rayDirectionFrac( 1.0f/rayDirection.x, 1.0f/rayDirection.y); //odwrotnosc predkosci od tamtego do tego

    // tajemnicze zmienne mocy

    float t1 = (rightBottom.x - rayPosition.x)* rayDirectionFrac.x,
          t2 = (leftTop.x - rayPosition.x) * rayDirectionFrac.x,
          t3 = (rightBottom.y - rayPosition.y) * rayDirectionFrac.y,
          t4 = (leftTop.y - rayPosition.y) * rayDirectionFrac.y;

    float tmax = std::min(std::max(t1,t2), std::max(t3,t4));
    float tmin = std::max(std::min(t1,t2), std::min(t3,t4));

    float t = 0;
    if(tmax < 0 || tmin > tmax) return false; //  t = tmax;
    t = tmin;

    if(t == t1)
    {
        data.normal = NORMAL_RIGHT;
        data.penetration =
                (bb1.left + bb1.width) - bb2.left;
        data.colision_point = sf::Vector2f(bb1.left + bb1.width, bb1.top);
    }
    else if(t == t2)
    {
        data.normal = NORMAL_LEFT;
        data.penetration =
                (bb2.left + bb2.width)- bb1.left;
        data.colision_point = sf::Vector2f(bb1.left, bb1.top + bb1.height);
    }
    else if(t == t3)
    {
        data.normal = NORMAL_DOWN;
        data.penetration =
                (bb1.top + bb1.height) - bb2.top;
        data.colision_point = sf::Vector2f(bb1.left + bb1.width, bb1.top + bb1.height);
    }
    else if(t == t4)
    {
        data.normal = NORMAL_UP;
        data.penetration =
                (bb2.top + bb2.height) - bb1.top;
        data.colision_point = sf::Vector2f(bb1.left, bb1.top);
    }
    else assert(false);

    return true;
}
