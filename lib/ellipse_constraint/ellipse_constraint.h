
#ifndef __ELLIPSE_CONSTRAINT_H__
#define __ELLIPSE_CONSTRAINT_H__

#include "mathematics.h"
#include "constraint.h"
#include "ellipse_shape.h"

class EllipseConstraint : public Constraint {
private:
    EllipseShape ellipse;
    const sf::Vector2f center;
    const sf::Vector2f radius;
    
    float distanceSum;
    float focalLength;
    sf::Vector2f focus1;
    sf::Vector2f focus2;

    float sinOfRotationAngleRadian;
    float cosOfRotationAngleRadian;

public:
    EllipseConstraint(const sf::Vector2f& center_, const sf::Vector2f& radius_, float rotationAngleRadian_,
        const sf::Color& fillColor_ = sf::Color::Black, const sf::Color& outlineColor_ = sf::Color::Blue);

    const sf::Vector2f& getCenter() const;
    const sf::Vector2f& getRadius() const;
    const sf::Vector2f& getFocus1() const;
    const sf::Vector2f& getFocus2() const;

    void apply(Verlet& verlet) const override;
    void draw(sf::RenderTarget& target) const override;
    void setAngle(float rotationAngleRadian_) override;

private:
    void calculateFocii();
};

#endif // __ELLIPSE_CONSTRAINT_H__
