
#ifndef __ELLIPSE_SHAPE_H__
#define __ELLIPSE_SHAPE_H__

#include <math.h>
#include <assert.h>
#include <SFML/Graphics.hpp>

class EllipseShape : public sf::Shape {
public:
    EllipseShape(const sf::Vector2f& radius_ = sf::Vector2f(1.0f, 1.0f));

    void setRadius(const sf::Vector2f& radius_);
    const sf::Vector2f& getRadius() const;

    void setPointCount(size_t pointCount_);
    size_t getPointCount() const;

    sf::Vector2f getPoint(size_t index) const;

private:
    sf::Vector2f radius;
    size_t pointCount = 30;
};

#endif // __ELLIPSE_SHAPE_H__
