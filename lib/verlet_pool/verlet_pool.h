
#ifndef __VERLET_POOL_H__
#define __VERLET_POOL_H__

#include "speed_color_verlet.h"
#include "fixed_color_verlet.h"

class VerletPool {
private:
    static VerletPool instance_;

    static const uint32_t poolSize = 3000;
    SpeedColorVerlet speedColorVerletPool[poolSize];
    FixedColorVerlet fixedColorVerletPool[poolSize];

    uint32_t availableSpeedColorVerletCount;
    uint32_t availableFixedColorVerletCount;

    Verlet* firstAvailableSpeedColorVerlet;
    Verlet* firstAvailableFixedColorVerlet;

    VerletPool();

public:
    static VerletPool& instance();

    uint32_t getAvailableSpeedColorVerletCount() const;
    uint32_t getAvailableFixedColorVerletCount() const;

    Verlet* getSpeedColorVerlet(const sf::Vector2f& position, float radius, float mass);
    Verlet* getFixedColorVerlet(const sf::Vector2f& position, float radius, float mass, const sf::Color& color);

    void releaseVerlet(Verlet* verlet);
};

#endif // __VERLET_POOL_H__
