
#ifndef __CONSTRAINT_H__
#define __CONSTRAINT_H__

#include <assert.h>
#include "verlet.h"

#define RECTANGLE_CONTRAINT     0
#define CIRCLE_CONSTRAINT       1
#define ELLIPSE_CONSTRAINT      2
#define ARC_CONSTRAINT          3


// Constraint which prevents verlets going out of the boundaries
// Objects can pass through the boundary if it comes from outside
class Constraint {
protected:
    const float outlineThickness = 2.0f;
    const sf::Color fillColor;
    const sf::Color outlineColor;

    float rotationAngleRadian;
    float angularVelocity = 0.0f;

    Constraint(float rotationAngleRadian_, const sf::Color& fillColor_, const sf::Color& outlineColor_) 
        : fillColor(fillColor_), outlineColor(outlineColor_) 
    {
        assert(0.0f <= rotationAngleRadian_ && rotationAngleRadian_ < 2.0f*M_PIf);
        rotationAngleRadian = rotationAngleRadian_;
    }

    virtual void setAngle(float rotationAngleRadian_) = 0;

public:
    virtual ~Constraint() {}
    virtual void apply(Verlet& verlet) const = 0;
    virtual void draw(sf::RenderTarget& target) const = 0;

    void updateAngle(float updateRotationAngleRadian) 
    {
        assert(-2.0f*M_PIf <= updateRotationAngleRadian && updateRotationAngleRadian < 2.0f*M_PIf);
        if (updateRotationAngleRadian == 0.0f) return;
        
        float newRotationAngleRadian = rotationAngleRadian + updateRotationAngleRadian;
        if (newRotationAngleRadian >= 2.0f*M_PIf)
        {
            newRotationAngleRadian -= 2.0f*M_PIf;
        } 
        else if (newRotationAngleRadian < 0.0f)
        {
            newRotationAngleRadian += 2.0f*M_PIf;
        }
        setAngle(newRotationAngleRadian); // guarantees that 0 <= newAngle < 2*pi 
    }
};

#endif // __CONSTRAINT_H__
