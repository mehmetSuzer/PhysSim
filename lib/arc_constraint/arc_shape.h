
#ifndef __ARC_SHAPE_H__
#define __ARC_SHAPE_H__

#include <math.h>
#include <assert.h>
#include <SFML/Graphics.hpp>

class ArcShape : public sf::Shape {
public:
    ArcShape(float radius_ = 0.0f, float sweepAngleRadian_ = M_PIf, bool isHole_ = false);

    void setRadius(float radius_);
    float getRadius() const;

    void setSweepAngleRadian(float sweepAngleRadian_);
    float getSweepAngleRadian() const;

    void setIsHole(bool isHole_);
    bool getIsHole() const;

    void setPointCount(size_t pointCount_);
    size_t getPointCount() const;

    sf::Vector2f getPoint(size_t index) const;

private:
    float radius;
    float sweepAngleRadian;
    bool isHole;
    size_t pointCount = 30;
};

#endif // __ARC_SHAPE_H__
