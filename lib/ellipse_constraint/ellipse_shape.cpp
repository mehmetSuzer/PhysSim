
#include "ellipse_shape.h"

EllipseShape::EllipseShape(const sf::Vector2f& radius_)
{
    assert(radius_.x > 0.0f && radius_.y > 0.0f);
    radius = radius_;
    update();
}

void EllipseShape::setRadius(const sf::Vector2f& radius_)
{
    assert(radius_.x > 0.0f && radius_.y > 0.0f);
    radius = radius_;
    update();
}

const sf::Vector2f& EllipseShape::getRadius() const
{
    return radius;
}

void EllipseShape::setPointCount(size_t pointCount_) 
{
    pointCount = pointCount_;
    update();
}

size_t EllipseShape::getPointCount() const
{
    return pointCount;
}

sf::Vector2f EllipseShape::getPoint(size_t index) const
{
    const float angle = index * 2.0f * M_PIf / getPointCount();
    const float x = cosf(angle) * radius.x;
    const float y = sinf(angle) * radius.y;
    return sf::Vector2f(x,y);
}
