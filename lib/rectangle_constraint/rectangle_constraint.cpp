
#include "rectangle_constraint.h"

RectangleConstraint::RectangleConstraint(const sf::Vector2f& center_, float width_, float height_, 
    float rotationAngleRadian_, const sf::Color& fillColor_, const sf::Color& outlineColor_)
    : Constraint(rotationAngleRadian_, fillColor_, outlineColor_), center(center_), halfWidth(width_/2.0f), halfHeight(height_/2.0f),
    sinOfRotationAngleRadian(sinf(rotationAngleRadian_)), cosOfRotationAngleRadian(cosf(rotationAngleRadian_))
{
    rectangle.setOutlineThickness(outlineThickness);
    rectangle.setOutlineColor(outlineColor);
    rectangle.setOrigin(sf::Vector2f(halfWidth, halfHeight));
    rectangle.setPosition(center);
    rectangle.setSize(sf::Vector2f(width_, height_));
    rectangle.setRotation(180.0f * rotationAngleRadian / M_PIf);
    rectangle.setFillColor(fillColor);
}

const sf::Vector2f& RectangleConstraint::getCenter() const
{
    return center;
}

float RectangleConstraint::getWidth() const
{
    return 2.0f*halfWidth;
}

float RectangleConstraint::getHeight() const
{
    return 2.0f*halfHeight;
}

void RectangleConstraint::apply(Verlet& verlet) const
{
    const float radius = verlet.getRadius();
    sf::Vector2f positionWRTCenter = verlet.getPosition() - center;

    sf::Vector2f rotatedPositionWRTCenter = sf::Vector2f(
        positionWRTCenter.x*cosOfRotationAngleRadian + positionWRTCenter.y*sinOfRotationAngleRadian,
        -positionWRTCenter.x*sinOfRotationAngleRadian + positionWRTCenter.y*cosOfRotationAngleRadian
    );

    const float leftDiff = rotatedPositionWRTCenter.x + halfWidth;
    if (leftDiff < radius)
    {
        const sf::Vector2f dx = sf::Vector2f(radius-leftDiff, 0.0f);
        rotatedPositionWRTCenter += dx;
    }

    const float rightDiff = halfWidth - rotatedPositionWRTCenter.x;
    if (rightDiff < radius)
    {
        const sf::Vector2f dx = sf::Vector2f(rightDiff-radius, 0.0f);
        rotatedPositionWRTCenter += dx;
    }

    const float upDiff = rotatedPositionWRTCenter.y + halfHeight;
    if (upDiff < radius)
    {
        const sf::Vector2f dx = sf::Vector2f(0.0f, radius-upDiff);
        rotatedPositionWRTCenter += dx;
    }

    const float downDiff = halfHeight - rotatedPositionWRTCenter.y;
    if (downDiff < radius)
    {
        const sf::Vector2f dx = sf::Vector2f(0.0f, downDiff-radius);
        rotatedPositionWRTCenter += dx;
    }

    rotatedPositionWRTCenter = sf::Vector2f(
        rotatedPositionWRTCenter.x*cosOfRotationAngleRadian - rotatedPositionWRTCenter.y*sinOfRotationAngleRadian,
        rotatedPositionWRTCenter.x*sinOfRotationAngleRadian + rotatedPositionWRTCenter.y*cosOfRotationAngleRadian
    );
    verlet.setPosition(rotatedPositionWRTCenter+center);
}

void RectangleConstraint::draw(sf::RenderTarget& target) const {
    target.draw(rectangle);
}

void RectangleConstraint::setAngle(float rotationAngleRadian_) 
{
    rotationAngleRadian = rotationAngleRadian_;
    sinOfRotationAngleRadian = sinf(rotationAngleRadian);
    cosOfRotationAngleRadian = cosf(rotationAngleRadian);
    rectangle.setRotation(180.0f * rotationAngleRadian / M_PIf);
}

