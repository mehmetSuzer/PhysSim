
#include "verlet.h"

Verlet::Verlet(const sf::Vector2f& position_, float radius_, float mass_) :
    currPosition(position_), prevPosition(position_), radius(radius_), mass(mass_)
{
    assert(radius_ > 0.0f);
    assert(mass_ > 0.0f);

    circle.setOrigin(radius, radius);
    circle.setRadius(radius);

    uint32_t pointCount = (radius > 2.0f) ? static_cast<uint32_t>(2*radius) : 4UL;
    circle.setPointCount(pointCount);
}

void Verlet::draw(sf::RenderTarget& target) 
{
    circle.setPosition(currPosition);
    target.draw(circle);
}

const sf::Vector2f& Verlet::getPosition() const 
{
    return currPosition;
}

void Verlet::setPosition(const sf::Vector2f& position) 
{
    currPosition = position;
}

void Verlet::updatePosition(const sf::Vector2f& dx)
{   
    currPosition += dx;
}

float Verlet::getRadius() const 
{
    return radius;
}

float Verlet::getMass() const
{
    return mass;
}

sf::Vector2f Verlet::getMomentum(float dt) const
{
    return mass * getVelocity(dt);
}

sf::Vector2f Verlet::getVelocity(float dt) const
{
    return (currPosition-prevPosition) / dt + acceleration * dt;
}

float Verlet::getSpeed(float dt) const
{
    sf::Vector2f velocity = getVelocity(dt);
    return Mathematics::magnitude(velocity);
}

void Verlet::setVelocityAfterCollision(const sf::Vector2f& velocity, float dt, const sf::Vector2f& dx)
{
    currPosition += dx;
    prevPosition = currPosition - velocity*dt + acceleration*dt*dt;
}

void Verlet::update(float dt) 
{
    const sf::Vector2f newPosition = 2.0f*currPosition - prevPosition + acceleration*dt*dt;
    prevPosition = currPosition;
    currPosition = newPosition;
    acceleration.x = 0.0f;
    acceleration.y = 0.0f;
    updateColor(dt);
}

bool Verlet::isAffectedByGravity() const
{
    return affectedByGravity;
}

void Verlet::enableGravity()
{
    affectedByGravity = true;
}

void Verlet::disableGravity()
{
    affectedByGravity = false;
}

void Verlet::force(const sf::Vector2f& forceVector)
{
    accelerate(forceVector/mass);
}

void Verlet::accelerate(const sf::Vector2f& accelerationVector) 
{
    acceleration += accelerationVector;
}

const sf::Vector2f& Verlet::getAcceleration() const 
{
    return acceleration;
}

static sf::Color randColor(uint8_t lowRed, uint8_t highRed,
                    uint8_t lowGreen, uint8_t highGreen,
                    uint8_t lowBlue, uint8_t highBlue) 
{
    const uint8_t red = rand()%(highRed-lowRed) + lowRed;
    const uint8_t green = rand()%(highGreen-lowGreen) + lowGreen;
    const uint8_t blue = rand()%(highBlue-lowBlue) + lowBlue;
    return sf::Color(red, green, blue);
}

