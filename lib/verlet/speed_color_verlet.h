
#ifndef __SPEED_COLOR_VERLET_H__
#define __SPEED_COLOR_VERLET_H__

#include "verlet.h"

class SpeedColorVerlet : public Verlet {
public:
    SpeedColorVerlet(const sf::Vector2f& position_, float radius_, float mass_) :
        Verlet(position_, radius_, mass_) {}

private:
    const float speedLevel1 = 50.0f;
    const float speedLevel2 = 100.0f;
    const float speedLevel3 = 150.0f;

    void updateColor(float dt) override;
};

#endif // __SPEED_COLOR_VERLET_H__