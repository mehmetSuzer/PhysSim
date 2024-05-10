
#ifndef __SOLVER_H__
#define __SOLVER_H__

#include <vector>
#include "mathematics.h"
#include "constraint.h"

#include "fixed_color_verlet.h"
#include "speed_color_verlet.h"


struct Link {
    Verlet* verlet1;
    Verlet* verlet2;
    const float targetDistance;
};

class Solver {
private:
    const sf::Vector2f gravity = sf::Vector2f(0.0f, 1000.0f);
    const uint32_t subStepCount = 6;

    std::vector<Verlet*> verlets;
    std::vector<Link*> links;

    Constraint& constraint;
    bool constraintActive = false;
    float constraintAngularVelocity = 0.0f;

    float elapsedTimeSinceLastPhysicsUpdate = 0.0f;
    const float secondsPerPhysicsUpdate;
    const float subSecondsPerPhysicsUpdate;

public:
    Solver(float secondsPerPhysicsUpdate_, Constraint& constraint_) : 
        secondsPerPhysicsUpdate(secondsPerPhysicsUpdate_), constraint(constraint_), 
        subSecondsPerPhysicsUpdate(secondsPerPhysicsUpdate_ / static_cast<float>(subStepCount)) {}

    ~Solver();

    void clearVerlets();
    void addFixedColorVerlet(const sf::Vector2f& position, float radius, float mass, const sf::Color& color);
    void addSpeedColorVerlet(const sf::Vector2f& position, float radius, float mass);

    uint32_t getSubStepCount() const;

    uint32_t getVerletCount() const;
    const std::vector<Verlet*>& getVerlets() const;
    Verlet* getVerlet(uint32_t index) const;
    bool hasVerlet(Verlet* verlet) const;

    void clearLinks();
    void addLink(Verlet* verlet1, Verlet* verlet2, float targetDistance);
    uint32_t getLinkCount() const;
    const std::vector<Link*>& getLinks() const;
    
    const Constraint& getConstraint() const;
    bool isConstraintActive() const;
    void activateConstraint();
    void deactivateConstraint();
    void setConstraintRotation(float frequencyWithDirection);
    float getConstraintAngularVelocity() const;

    void update(float elapsedTimeSinceLastFrame);

private:
    void sortVerletsX();
    void sortVerletsY();

    void updatePositions(float dt);
    void applyGravity();
    void rotateConstraint(float dt);
    void applyConstraint();
    void applyLinks();
    void solveCollisions(float dt);
};

#endif // __SOLVER_H__
