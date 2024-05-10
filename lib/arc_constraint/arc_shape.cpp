

#include "arc_shape.h"

ArcShape::ArcShape(float radius_, float sweepAngleRadian_, bool isHole_)
{
    radius = radius_;
    assert(0.0f < sweepAngleRadian_ && sweepAngleRadian_ < 2.0f*M_PIf);
    sweepAngleRadian = sweepAngleRadian_;
    isHole = isHole_;
    update();
}

void ArcShape::setRadius(float radius_)
{
    radius = radius_;
    update();
}

float ArcShape::getRadius() const
{
    return radius;
}

void ArcShape::setSweepAngleRadian(float sweepAngleRadian_)
{
    assert(0.0f < sweepAngleRadian_ && sweepAngleRadian_ < 2.0f*M_PIf);
    sweepAngleRadian = sweepAngleRadian_;
    update();
}

float ArcShape::getSweepAngleRadian() const
{
    return sweepAngleRadian;
}

void ArcShape::setIsHole(bool isHole_)
{
    isHole = isHole_;
}
    
bool ArcShape::getIsHole() const
{
    return isHole;
}

void ArcShape::setPointCount(size_t pointCount_) 
{
    pointCount = pointCount_;
    update();
}

size_t ArcShape::getPointCount() const
{
    return pointCount;
}

sf::Vector2f ArcShape::getPoint(size_t index) const
{
    float angle;
    if (isHole)
    {
        angle = sweepAngleRadian + index * (2.0f*M_PIf - sweepAngleRadian) / getPointCount();
    }
    else
    {
        angle = index * sweepAngleRadian / getPointCount();
    }

    const float x = radius * cosf(angle);
    const float y = radius * sinf(angle);
    return sf::Vector2f(x,y);
}
