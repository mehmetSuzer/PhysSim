
#include "solver.h"

Solver::~Solver()
{
    clearVerlets();
    clearLinks();
}

void Solver::clearVerlets() 
{
    verlets.clear();
}

void Solver::addFixedColorVerlet(const sf::Vector2f& position, float radius, float mass, const sf::Color& color)
{
    Verlet* verlet = VerletPool::instance().getFixedColorVerlet(position, radius, mass, color);
    verlets.push_back(verlet);
}

void Solver::addSpeedColorVerlet(const sf::Vector2f& position, float radius, float mass)
{
    Verlet* verlet = VerletPool::instance().getSpeedColorVerlet(position, radius, mass);
    verlets.push_back(verlet);
}

uint32_t Solver::getSubStepCount() const
{
    return subStepCount;
}

const std::vector<Verlet*>& Solver::getVerlets() const 
{
    return verlets;
}

Verlet* Solver::getVerlet(uint32_t index) const
{
    assert(index < getVerletCount());
    return verlets[index];
}

uint32_t Solver::getVerletCount() const
{
    return verlets.size();
}

bool Solver::hasVerlet(Verlet* verlet) const
{
    for (uint32_t i = 0; i < getVerletCount(); i++)
    {
        if (verlets[i] == verlet) 
        {
            return true;
        }
    }
    return false;
}

void Solver::clearLinks() 
{
    for (uint32_t i = 0; i < getLinkCount(); i++)
    {
        delete links[i];
    }
    links.clear();
}

void Solver::addLink(Verlet* verlet1, Verlet* verlet2, float targetDistance) 
{
    const uint32_t size = getVerletCount();
    if (hasVerlet(verlet1) && hasVerlet(verlet2)) 
    {
        links.push_back(new Link{verlet1, verlet2, targetDistance});
    }
}

uint32_t Solver::getLinkCount() const
{
    return links.size();
}

const std::vector<Link*>& Solver::getLinks() const 
{
    return links;
}

const Constraint& Solver::getConstraint() const
{   
    return constraint;
}

bool Solver::isConstraintActive() const
{
    return constraintActive;
}

void Solver::activateConstraint()
{
    constraintActive = true;
}

void Solver::deactivateConstraint()
{
    constraintActive = false;
}
    
void Solver::setConstraintRotation(float frequencyWithDirection)
{
    constraintAngularVelocity = 2.0f * M_PIf * frequencyWithDirection;
}

float Solver::getConstraintAngularVelocity() const
{
    return constraintAngularVelocity;
}

void Solver::update(float elapsedTimeSinceLastFrame)
{
    elapsedTimeSinceLastPhysicsUpdate += elapsedTimeSinceLastFrame;
    while (elapsedTimeSinceLastPhysicsUpdate >= secondsPerPhysicsUpdate)
    {
        for (uint32_t i = 0; i < subStepCount; i++) {
            solveCollisions(subSecondsPerPhysicsUpdate);
            rotateConstraint(subSecondsPerPhysicsUpdate);
            applyConstraint();
            applyLinks();
            applyGravity();
            updatePositions(subSecondsPerPhysicsUpdate);
        }
        elapsedTimeSinceLastPhysicsUpdate -= secondsPerPhysicsUpdate;
    }
}

void Solver::clearVerletsOutOfWindow(size_t width, size_t height)
{
    for (uint32_t i = 0; i < getVerletCount(); i++)
    {
        if (verlets[i]->outOfWindow(width, height))
        {
            VerletPool::instance().releaseVerlet(verlets[i]);
            verlets.erase(verlets.begin() + i);
        }
    }
}

void Solver::sortVerletsX()
{
    const uint32_t count = getVerletCount();
    for (int32_t i = 1; i < count; i++) 
    {
        Verlet* verlet = verlets[i];
        const float x1 = verlet->getPosition().x;
        int32_t j = i-1;
        while (j >= 0 && x1 < verlets[j]->getPosition().x)
        {
            verlets[j+1] = verlets[j];
            j--;
        }
        verlets[j+1] = verlet;
    }
}

void Solver::sortVerletsY()
{
    const uint32_t count = getVerletCount();
    for (int32_t i = 1; i < count; i++) 
    {
        Verlet* verlet = verlets[i];
        const float y1 = verlet->getPosition().y;
        int32_t j = i-1;
        while (j >= 0 && y1 < verlets[j]->getPosition().y)
        {
            verlets[j+1] = verlets[j];
            j--;
        }
        verlets[j+1] = verlet;
    }
}

void Solver::updatePositions(float dt) 
{
    for (uint32_t i = 0; i < getVerletCount(); i++) 
    {
        verlets[i]->update(dt);
    }
}

void Solver::applyGravity() 
{
    for (uint32_t i = 0; i < getVerletCount(); i++) 
    {
        if (verlets[i]->isAffectedByGravity())
        {
            verlets[i]->accelerate(gravity);
        }
    }
}

void Solver::rotateConstraint(float dt)
{
    constraint.updateAngle(constraintAngularVelocity * dt);
}

void Solver::applyConstraint() 
{
    if (constraintActive)
    {
        for (uint32_t i = 0; i < getVerletCount(); i++) 
        {
            constraint.apply(*(verlets[i]));
        }
    }
}

void Solver::applyLinks() 
{
    for (uint32_t i = 0; i < getLinkCount(); i++) 
    {
        Verlet* verlet1 = links[i]->verlet1;
        Verlet* verlet2 = links[i]->verlet2;

        const sf::Vector2f centerDiffVector = verlet1->getPosition() - verlet2->getPosition();
        const float centerDistance = Mathematics::magnitude(centerDiffVector);
        const sf::Vector2f axis = centerDiffVector / centerDistance;
        const float dx = (links[i]->targetDistance - centerDistance) * 0.5f;

        verlet1->updatePosition(axis * dx);
        verlet2->updatePosition(-axis * dx);
    }
}

void Solver::solveCollisions(float dt) 
{
    const uint32_t count = getVerletCount();
    if (count < 2) return;

    sortVerletsX();

    for (uint32_t i = 0; i < count-1; i++) 
    {
        Verlet* verlet1 = verlets[i];
        uint32_t j = i+1;
        while (j < count)
        {
            Verlet* verlet2 = verlets[j];
            const float radiiSum = verlet2->getRadius() + verlet1->getRadius();

            if (verlet2->getPosition().x - verlet1->getPosition().x > radiiSum) 
            {
                break;
            }
            
            if (verlet2->getPosition().y - verlet1->getPosition().y > radiiSum)
            {
                j++;
                continue;
            }

            const sf::Vector2f centerDiffVector = verlet2->getPosition() - verlet1->getPosition();
            const float centerDistance = Mathematics::magnitude(centerDiffVector);
            if (centerDistance <= radiiSum) 
            {
                const sf::Vector2f initialVelocity1 = verlet1->getVelocity(dt);
                const sf::Vector2f initialVelocity2 = verlet2->getVelocity(dt);

                const sf::Vector2f collisionAxis = centerDiffVector / centerDistance;

                const sf::Vector2f initialCollisionVelocity1 = Mathematics::dot(initialVelocity1, collisionAxis) * collisionAxis;
                const sf::Vector2f initialTangentVelocity1 = initialVelocity1 - initialCollisionVelocity1;

                const sf::Vector2f initialCollisionVelocity2 = Mathematics::dot(initialVelocity2, collisionAxis) * collisionAxis;
                const sf::Vector2f initialTangentVelocity2 = initialVelocity2 - initialCollisionVelocity2;

                const float mass1 = verlet1->getMass();
                const float mass2 = verlet2->getMass();

                sf::Vector2f finalVelocity1;
                sf::Vector2f finalVelocity2;

                if (abs(mass1-mass2) < 1E-3f)
                {
                    finalVelocity1 = initialTangentVelocity1 + initialCollisionVelocity2;
                    finalVelocity2 = initialTangentVelocity2 + initialCollisionVelocity1;
                } else 
                {
                    finalVelocity1 = initialTangentVelocity1 + (2.0f*mass2*initialCollisionVelocity2 + (mass1-mass2)*initialCollisionVelocity1) / (mass1+mass2);
                    finalVelocity2 = initialTangentVelocity2 + (2.0f*mass1*initialCollisionVelocity1 + (mass2-mass1)*initialCollisionVelocity2) / (mass2+mass1);
                }
                
                const float dx = 1.0f - centerDistance/radiiSum;  
                const float dx1 = dx * verlet1->getRadius();
                const float dx2 = dx * verlet2->getRadius();

                verlet1->setVelocityAfterCollision(finalVelocity1, dt, -collisionAxis * dx1);
                verlet2->setVelocityAfterCollision(finalVelocity2, dt, collisionAxis * dx2);
            }
            j++;
        }
    }
}

