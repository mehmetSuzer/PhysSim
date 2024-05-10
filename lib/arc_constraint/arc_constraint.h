
#ifndef __ARC_CONSTRAINT_H__
#define __ARC_CONSTRAINT_H__

#include "mathematics.h"
#include "constraint.h"
#include "arc_shape.h"

class ArcConstraint : public Constraint {
private:
    ArcShape arc;
    const sf::Vector2f center;
    const float radius;

public:
    ArcConstraint(const sf::Vector2f& center_, float radius_, float sweepAngleRadian_, float rotationAngleRadian_, bool isHole_,
        const sf::Color& fillColor_ = sf::Color::Black, const sf::Color& outlineColor_ = sf::Color::Blue);

    const sf::Vector2f& getCenter() const;
    float getRadius() const;

    void apply(Verlet& verlet) const override;
    void draw(sf::RenderTarget& target) const override;
    void setAngle(float rotationAngleRadian_) override;
};

#endif // __ARC_CONSTRAINT_H__
