
#ifndef __EVENT_CONTROLLER_H__
#define __EVENT_CONTROLLER_H__

#include <vector>
#include <assert.h>
#include "command.h"
#include "solver.h"

enum Button {
    LEFT_KEY = 0,
    RIGHT_KEY,
    UP_KEY,
    DOWN_KEY,
    EXIT_KEY,
    MUSIC_ON_KEY,
    MUSIC_OFF_KEY,
    ROTATE_CCW_KEY,
    ROTATE_STOP_KEY,
    ROTATE_CW_KEY,
    NUMBER_OF_KEYS, // Not a Key
};

class EventController {
private:
    const float rotateFrequency = 0.1f; // Hz

    sf::Vector2f downAcceleration = sf::Vector2f(0.0f, 1.0f);
    sf::Vector2f rightAcceleration = sf::Vector2f(1.0f, 0.0f);

    sf::RenderWindow* selectedWindow = nullptr;
    Verlet* selectedVerlet = nullptr;
    Solver* selectedSolver = nullptr;
    sf::Music music;

    sf::Keyboard::Key keys[NUMBER_OF_KEYS] = {
        sf::Keyboard::A,        // LEFT_KEY
        sf::Keyboard::D,        // RIGHT_KEY
        sf::Keyboard::W,        // UP_KEY
        sf::Keyboard::S,        // DOWN_KEY
        sf::Keyboard::Escape,   // EXIT_KEY
        sf::Keyboard::M,        // MUSIC_ON_KEY
        sf::Keyboard::N,        // MUSIC_OFF_KEY
        sf::Keyboard::J,        // ROTATE_CCW_KEY
        sf::Keyboard::K,        // ROTATE_STOP_KEY
        sf::Keyboard::L,        // ROTATE_CW_KEY
    };

    EventController() {};
    static EventController instance_;

public:
    static EventController& instance();

    void setSelectedWindow(sf::RenderWindow* window);
    void setSelectedVerlet(Verlet* verlet);
    void setSelectedSolver(Solver* solver);
    void setMusic(const char* musicFile);

    void assignKey(const enum Button button, const sf::Keyboard::Key& key);

    void handleInputs(float elapsedTimeSinceLastFrame);
    void handleEvents() const;

private:
    bool handleExitInputs() const;
    void handleMusicInputs();
    void handleRotateInputs() const;
    void handleMoveInputs(float elapsedTimeSinceLastFrame) const;
};

#endif // __EVENT_CONTROLLER_H__
