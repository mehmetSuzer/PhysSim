
#ifndef __CIRCLE_CONSTRAINT_H__
#define __CIRCLE_CONSTRAINT_H__

#include "mathematics.h"
#include "constraint.h"

class CircleConstraint : public Constraint {
private:
    sf::CircleShape circle;
    const sf::Vector2f center;
    const float radius;

public:
    CircleConstraint(const sf::Vector2f& center_, float radius_, 
        const sf::Color& fillColor_ = sf::Color::Black, const sf::Color& outlineColor_ = sf::Color::Blue);

    const sf::Vector2f& getCenter() const;
    float getRadius() const;

    void apply(Verlet& verlet) const override;
    void draw(sf::RenderTarget& target) const override;
    void setAngle(float rotationAngleRadian_) override;
};

#endif // __CIRCLE_CONSTRAINT_H__
