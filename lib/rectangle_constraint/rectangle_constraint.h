
#ifndef __RECTANGLE_CONSTRAINT_H__
#define __RECTANGLE_CONSTRAINT_H__

#include "constraint.h"

class RectangleConstraint : public Constraint {
private:
    sf::RectangleShape rectangle;
    const sf::Vector2f center;
    const float halfWidth;
    const float halfHeight;

    float sinOfRotationAngleRadian;
    float cosOfRotationAngleRadian;

public:
    RectangleConstraint(const sf::Vector2f& center_, float width_, float height_, float rotationAngleRadian_, 
        const sf::Color& fillColor_ = sf::Color::Black, const sf::Color& outlineColor_ = sf::Color::Blue);

    const sf::Vector2f& getCenter() const;
    float getWidth() const;
    float getHeight() const;

    void apply(Verlet& verlet) const override;
    void draw(sf::RenderTarget& target) const override;
    void setAngle(float rotationAngleRadian_) override;
};

#endif // __RECTANGLE_CONSTRAINT_H__
