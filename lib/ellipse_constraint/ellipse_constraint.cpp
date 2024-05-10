
#include "ellipse_constraint.h"

EllipseConstraint::EllipseConstraint(const sf::Vector2f& center_, const sf::Vector2f& radius_, float rotationAngleRadian_,
    const sf::Color& fillColor_, const sf::Color& outlineColor_)
    : Constraint(rotationAngleRadian_, fillColor_, outlineColor_), center(center_), radius(radius_),
    sinOfRotationAngleRadian(sinf(rotationAngleRadian_)), cosOfRotationAngleRadian(cosf(rotationAngleRadian_))
{
    ellipse.setOutlineThickness(outlineThickness);
    ellipse.setOutlineColor(outlineColor);
    ellipse.setPosition(center);
    ellipse.setRadius(radius);
    ellipse.setFillColor(fillColor);
    ellipse.setRotation(180.0f * rotationAngleRadian / M_PIf);
    ellipse.setPointCount(128);

    if (radius.x > radius.y)
    {
        distanceSum = 2.0f * radius.x;
        focalLength = sqrtf(radius.x*radius.x - radius.y*radius.y);
    } else 
    {
        distanceSum = 2.0f * radius.y;
        focalLength = sqrtf(radius.y*radius.y - radius.x*radius.x);
    }

    calculateFocii();
}

const sf::Vector2f& EllipseConstraint::getCenter() const
{
    return center;
}
    
const sf::Vector2f& EllipseConstraint::getRadius() const
{
    return radius;
}

const sf::Vector2f& EllipseConstraint::getFocus1() const
{
    return focus1;
}

const sf::Vector2f& EllipseConstraint::getFocus2() const
{
    return focus2;
}

void EllipseConstraint::apply(Verlet& verlet) const
{
    const sf::Vector2f focus1Difference = focus1-verlet.getPosition();
    const sf::Vector2f focus2Difference = focus2-verlet.getPosition();

    const float focus1Distance = Mathematics::magnitude(focus1Difference);
    const float focus2Distance = Mathematics::magnitude(focus2Difference);
    const sf::Vector2f v1 = focus1Difference / focus1Distance;

    const sf::Vector2f p = verlet.getPosition() - v1 * verlet.getRadius();
    const float p2Distance = Mathematics::magnitude(focus2-p);

    if (p2Distance + focus1Distance + verlet.getRadius() > distanceSum)
    {
        const sf::Vector2f v2 = focus2Difference / focus2Distance;
        const sf::Vector2f bi = Mathematics::bisector(v1, v2);
        verlet.updatePosition(bi);
    }
}

void EllipseConstraint::draw(sf::RenderTarget& target) const
{
    target.draw(ellipse);
}

void EllipseConstraint::calculateFocii()
{
    if (radius.x > radius.y)
    {
        sf::Vector2f focus1WRTCenter = sf::Vector2f(focalLength*cosOfRotationAngleRadian, focalLength*sinOfRotationAngleRadian);
        focus1 = center + focus1WRTCenter;
        focus2 = center - focus1WRTCenter;
    } else 
    {
        sf::Vector2f focus1WRTCenter = sf::Vector2f(-focalLength*sinOfRotationAngleRadian, focalLength*cosOfRotationAngleRadian);
        focus1 = center + focus1WRTCenter;
        focus2 = center - focus1WRTCenter;
    }
}

void EllipseConstraint::setAngle(float rotationAngleRadian_) 
{
    rotationAngleRadian = rotationAngleRadian_;
    sinOfRotationAngleRadian = sinf(rotationAngleRadian);
    cosOfRotationAngleRadian = cosf(rotationAngleRadian);
    ellipse.setRotation(180.0f * rotationAngleRadian / M_PIf);
    calculateFocii();
}
