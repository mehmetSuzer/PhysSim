
#include "verlet_pool.h"

VerletPool VerletPool::instance_;

VerletPool& VerletPool::instance()
{
    return instance_;
}

VerletPool::VerletPool()
{
    firstAvailableSpeedColorVerlet = speedColorVerletPool;
    firstAvailableFixedColorVerlet = fixedColorVerletPool;

    for (uint32_t i = 0; i < poolSize-1; i++)
    {
        speedColorVerletPool[i].setNext(speedColorVerletPool+(i+1));
        fixedColorVerletPool[i].setNext(fixedColorVerletPool+(i+1));
    }
    speedColorVerletPool[poolSize-1].setNext(nullptr);
    fixedColorVerletPool[poolSize-1].setNext(nullptr);

    availableSpeedColorVerletCount = poolSize;
    availableFixedColorVerletCount = poolSize;
}

uint32_t VerletPool::getAvailableSpeedColorVerletCount() const
{
    return availableSpeedColorVerletCount;
}

uint32_t VerletPool::getAvailableFixedColorVerletCount() const
{
    return availableFixedColorVerletCount;
}

Verlet* VerletPool::getSpeedColorVerlet(const sf::Vector2f& position, float radius, float mass)
{
    assert(firstAvailableSpeedColorVerlet != nullptr);
    Verlet* verlet = firstAvailableSpeedColorVerlet;
    firstAvailableSpeedColorVerlet = verlet->getNext();
    verlet->init(position, radius, mass, sf::Color::Black);
    availableSpeedColorVerletCount--;
    return verlet;
}

Verlet* VerletPool::getFixedColorVerlet(const sf::Vector2f& position, float radius, float mass, const sf::Color& color)
{
    assert(firstAvailableFixedColorVerlet != nullptr);
    Verlet* verlet = firstAvailableFixedColorVerlet;
    firstAvailableFixedColorVerlet = verlet->getNext();
    verlet->init(position, radius, mass, color);
    availableFixedColorVerletCount--;
    return verlet;
}

void VerletPool::releaseVerlet(Verlet* verlet)
{
    if (verlet->type() == SPEED_COLOR)
    {
        verlet->setNext(firstAvailableSpeedColorVerlet);
        firstAvailableSpeedColorVerlet = verlet;
        availableSpeedColorVerletCount++;
    } else if (verlet->type() == FIXED_COLOR)
    {
        verlet->setNext(firstAvailableFixedColorVerlet);
        firstAvailableFixedColorVerlet = verlet;
        availableFixedColorVerletCount++;
    }
}
