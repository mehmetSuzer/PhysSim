
#ifndef __MATHEMATICS_H__
#define __MATHEMATICS_H__

#include <math.h>
#include <assert.h>
#include <SFML/Graphics.hpp>

class Mathematics {
public:
    static float magnitude(const sf::Vector2f& vector);
    static float dot(const sf::Vector2f& vec1, const sf::Vector2f& vec2);
    static sf::Vector2f project(const sf::Vector2f& vec, const sf::Vector2f& onto);
    static sf::Vector2f rotate(const sf::Vector2f& vector, float radian);
    static sf::Vector2f normalize(const sf::Vector2f& vector);
    static sf::Vector2f bisector(const sf::Vector2f& unit1, const sf::Vector2f& unit2);
    static float angle(const sf::Vector2f& unit);
};

#endif // __MATHEMATICS_H__
