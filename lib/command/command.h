
#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <SFML/Audio.hpp>
#include "solver.h"

class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
};

class MoveCommand : public Command {
private:
    Verlet* verlet;
    sf::Vector2f vector;

public:
    MoveCommand(Verlet* verlet_, const sf::Vector2f& vector_) : verlet(verlet_), vector(vector_) {};

    void execute() override 
    { 
        if (verlet)
        {
            verlet->accelerate(vector);
        }
    };
};

class ExitCommand : public Command {
private:
    sf::RenderWindow* window;

public:
    ExitCommand(sf::RenderWindow* window_) : window(window_) {};

    void execute() override
    { 
        if (window)
        {
            window->close();
        }
    };
};

class RotateCommand : public Command {
private:
    Solver* solver;
    float frequency;

public:
    RotateCommand(Solver* solver_, float frequency_) : solver(solver_), frequency(frequency_) {};

    void execute() override
    {
        if (solver)
        {
            solver->setConstraintRotation(frequency);
        }
    }
};

class SoundCommand : public Command {
private:
    sf::Music* music;
    bool play;
public:
    SoundCommand(sf::Music* music_, bool play_) : music(music_), play(play_) {};

    void execute() override
    {
        if (music)
        {
            if (play) { music->play(); }
            else      { music->pause(); }
        }
    }
};

#endif // __COMMAND_H__
