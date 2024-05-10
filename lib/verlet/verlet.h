
#ifndef __VERLET_H__
#define __VERLET_H__

#include <math.h>
#include <assert.h>
#include <SFML/Graphics.hpp>
#include "mathematics.h"

#define randf(low, high) (low + ((float)rand()/(float)RAND_MAX) * (high-low))

#define smaller(num1, num2) ((num1 < num2) ? num1 : num2)
#define greater(num1, num2) ((num1 > num2) ? num1 : num2)

#define SPEED_COLOR     0UL
#define FIXED_COLOR     1UL

class Verlet {
private:
    Verlet* next;

public:
    Verlet* getNext() const;
    void setNext(Verlet* next_);
    bool outOfWindow(size_t width, size_t height) const;

protected:
    sf::CircleShape circle = sf::CircleShape(1.0f);
    bool affectedByGravity = true;

    sf::Vector2f currPosition;
    sf::Vector2f prevPosition;
    sf::Vector2f acceleration;

    float radius;
    float mass;

    virtual void updateColor(float dt) = 0;

public:
    virtual uint32_t type() const = 0;
    
    void init(const sf::Vector2f& position_, float radius_, float mass_, const sf::Color& color_);
    void draw(sf::RenderTarget& target);

    const sf::Vector2f& getPosition() const;
    void setPosition(const sf::Vector2f& position);
    void updatePosition(const sf::Vector2f& dx);

    float getRadius() const;
    float getMass() const;
    sf::Vector2f getMomentum(float dt) const;
    sf::Vector2f getVelocity(float dt) const;
    float getSpeed(float dt) const;
    
    void setVelocityAfterCollision(const sf::Vector2f& velocity, float dt, const sf::Vector2f& dx);

    void update(float dt);

    bool isAffectedByGravity() const;
    void enableGravity();
    void disableGravity();

    void force(const sf::Vector2f& forceVector);
    void accelerate(const sf::Vector2f& accelerationVector);

    static sf::Color randColor(uint8_t lowRed, uint8_t highRed,
        uint8_t lowGreen, uint8_t highGreen, uint8_t lowBlue, uint8_t highBlue);
};

#endif // __VERLET_H__

