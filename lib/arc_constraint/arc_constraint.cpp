
#include "arc_constraint.h"

ArcConstraint::ArcConstraint(const sf::Vector2f& center_, float radius_, float sweepAngleRadian_,
    float rotationAngleRadian_, bool isHole_, const sf::Color& fillColor_, const sf::Color& outlineColor_)
    : Constraint(rotationAngleRadian_, fillColor_, outlineColor_), center(center_), radius(radius_)
{
    assert(rotationAngleRadian_+sweepAngleRadian_ < 2.0f*M_PIf);
    
    arc = ArcShape(radius, sweepAngleRadian_, isHole_);
    arc.setOutlineThickness(outlineThickness);
    arc.setOutlineColor(outlineColor);
    arc.setPosition(center);
    arc.setFillColor(fillColor);
    arc.setRotation(180.0f * rotationAngleRadian / M_PIf);
    arc.setPointCount(128);
}

const sf::Vector2f& ArcConstraint::getCenter() const
{
    return center;
}

float ArcConstraint::getRadius() const
{
    return radius;
}

void ArcConstraint::apply(Verlet& verlet) const 
{
    const sf::Vector2f centerDiff = verlet.getPosition() - center;
    const float centerDistance = Mathematics::magnitude(centerDiff);

    if (centerDistance == 0.0f) return; // At the center
    if (centerDistance > radius + verlet.getRadius()) return;// Out of the constraint

    const sf::Vector2f unit = centerDiff / centerDistance;
    const float radian = Mathematics::angle(unit); 
    if ((!arc.getIsHole() && (radian < rotationAngleRadian || radian > rotationAngleRadian+arc.getSweepAngleRadian())) ||
        (arc.getIsHole() && (radian > rotationAngleRadian && radian < rotationAngleRadian+arc.getSweepAngleRadian())))
    { // Out of sweep area
        return;
    }

    const float radiusDiff = radius - verlet.getRadius();
    if (centerDistance > radiusDiff) 
    {
        verlet.setPosition(center + unit*radiusDiff);
    }
}
    
void ArcConstraint::draw(sf::RenderTarget& target) const 
{
    target.draw(arc);
}
    
void ArcConstraint::setAngle(float rotationAngleRadian_) 
{
    if (rotationAngleRadian_+arc.getSweepAngleRadian() >= 2.0f*M_PIf)
    {
        rotationAngleRadian = rotationAngleRadian_+arc.getSweepAngleRadian();
        arc.setIsHole(!arc.getIsHole());
    }

    rotationAngleRadian = rotationAngleRadian_;
    arc.setRotation(180.0f * rotationAngleRadian / M_PIf);
}
