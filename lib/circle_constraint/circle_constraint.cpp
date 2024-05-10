
#include "circle_constraint.h"

CircleConstraint::CircleConstraint(const sf::Vector2f& center_, float radius_, const sf::Color& fillColor_, const sf::Color& outlineColor_) 
    : Constraint(0.0f, fillColor_, outlineColor_), center(center_), radius(radius_)
{
    circle.setOutlineThickness(outlineThickness);
    circle.setOutlineColor(outlineColor);
    circle.setOrigin(radius, radius);
    circle.setPosition(center);
    circle.setRadius(radius);
    circle.setFillColor(fillColor);
    circle.setPointCount(128);
}

const sf::Vector2f& CircleConstraint::getCenter() const
{
    return center;
}

float CircleConstraint::getRadius() const
{
    return radius;
}

void CircleConstraint::apply(Verlet& verlet) const 
{
    const sf::Vector2f centerDiff = verlet.getPosition() - center;
    const float centerDistance = Mathematics::magnitude(centerDiff);
    const float radiusDiff = radius - verlet.getRadius();
    if (centerDistance > radiusDiff) 
    {
        verlet.setPosition(center + (centerDiff/centerDistance)*radiusDiff);
    }
}

void CircleConstraint::draw(sf::RenderTarget& target) const
{
    target.draw(circle);
}

void CircleConstraint::setAngle(float rotationAngleRadian_) {}
