
#ifndef __VERLET_POOL_H__
#define __VERLET_POOL_H__

#include "speed_color_verlet.h"
#include "fixed_color_verlet.h"

class VerletPool {
private:
    static const uint32_t verletPoolSize = 3000;
    SpeedColorVerlet speedColorVerletPool[verletPoolSize];
    FixedColorVerlet FixedColorVerletPool[verletPoolSize];

public:
    SpeedColorVerlet* getSpeedColorVerlet(const sf::Vector2f& position, float radius, float mass);
    FixedColorVerlet* getFixedColorVerlet(const sf::Vector2f& position, float radius, float mass, const sf::Color& color);

};

#endif // __VERLET_POOL_H__
