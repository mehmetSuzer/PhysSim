
#include "mathematics.h"

float Mathematics::magnitude(const sf::Vector2f& vector)
{
    return sqrtf(vector.x*vector.x + vector.y*vector.y);
}

float Mathematics::dot(const sf::Vector2f& vec1, const sf::Vector2f& vec2)
{
    return vec1.x*vec2.x + vec1.y*vec2.y;
}

sf::Vector2f Mathematics::project(const sf::Vector2f& vec, const sf::Vector2f& onto)
{
    return dot(onto, vec) / dot(onto, onto) * onto;
}

sf::Vector2f Mathematics::rotate(const sf::Vector2f& vector, float radian)
{
    return sf::Vector2f(
        vector.x*cosf(radian) - vector.y*sinf(radian),
        vector.x*sinf(radian) + vector.y*cosf(radian)
    ); 
}

sf::Vector2f Mathematics::normalize(const sf::Vector2f& vector)
{
    float mag = magnitude(vector);
    assert(mag > 0.0f);
    return vector / mag;
}

sf::Vector2f Mathematics::bisector(const sf::Vector2f& unit1, const sf::Vector2f& unit2)
{
    sf::Vector2f unitSum = unit1 + unit2;
    return unitSum / magnitude(unitSum);
}

float Mathematics::angle(const sf::Vector2f& unit)
{
    float angle = acosf(unit.x);
    if (unit.y < 0.0f)
    {
        angle = 2.0f*M_PIf - angle;
    }
    return angle;
}
