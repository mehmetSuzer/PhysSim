
#ifndef __FIXED_COLOR_VERLET_H__
#define __FIXED_COLOR_VERLET_H__

#include "verlet.h"

class FixedColorVerlet : public Verlet {
private:
    const sf::Color color;

    void updateColor(float dt) override {}

public:
    FixedColorVerlet(const sf::Vector2f& position_, float radius_, float mass_, const sf::Color& color_);
};

#endif // __FIXED_COLOR_VERLET_H__
