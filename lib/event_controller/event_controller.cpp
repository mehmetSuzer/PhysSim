
#include "event_controller.h"

EventController EventController::instance_;

EventController& EventController::instance()
{
    return instance_;
}

void EventController::setSelectedWindow(sf::RenderWindow* window)
{
    selectedWindow = window;
}

void EventController::setSelectedVerlet(Verlet* verlet)
{
    selectedVerlet = verlet;
}

void EventController::setSelectedSolver(Solver* solver)
{
    selectedSolver = solver;
    if (selectedSolver)
    {
        float acceleration = 100000.0f * solver->getSubStepCount();
        downAcceleration = sf::Vector2f(0.0f, acceleration);
        rightAcceleration = sf::Vector2f(acceleration, 0.0f);
    }
}

void EventController::setMusic(const char* musicFile)
{
    assert(music.openFromFile(musicFile));
    music.setLoop(true);
    music.play();
}

void EventController::assignKey(const enum Button button, const sf::Keyboard::Key& key)
{
    for (uint32_t i = 0; i < NUMBER_OF_KEYS; i++)
    {
        if (keys[i] == key) {
            keys[i] = sf::Keyboard::Unknown;
        }
    }
    keys[button] = key;
}

void EventController::handleInputs(float elapsedTimeSinceLastFrame)
{   
    if (!handleExitInputs())
    {
        handleMusicInputs();
        handleRotateInputs();
        handleMoveInputs(elapsedTimeSinceLastFrame);
    }
}

void EventController::handleEvents() const
{
    sf::Event event;
    while (selectedWindow->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            selectedWindow->close();
        }
    }
}

bool EventController::handleExitInputs() const
{
    if (sf::Keyboard::isKeyPressed(keys[EXIT_KEY])) 
    {
        ExitCommand(selectedWindow).execute();
        return true;
    }
    return false;
}

void EventController::handleMusicInputs()
{
    if (music.getStatus() != sf::SoundSource::Status::Stopped)
    {
        if (sf::Keyboard::isKeyPressed(keys[MUSIC_ON_KEY]) && music.getStatus() != sf::SoundSource::Status::Playing)
        {
            SoundCommand(&music, true).execute();
        }
        else if (sf::Keyboard::isKeyPressed(keys[MUSIC_OFF_KEY]) && music.getStatus() == sf::SoundSource::Status::Playing)
        {
            SoundCommand(&music, false).execute();
        }
    }
}

void EventController::handleRotateInputs() const
{
    if (selectedSolver)
    {
        if (sf::Keyboard::isKeyPressed(keys[ROTATE_CCW_KEY]))
        {
            RotateCommand(selectedSolver, -rotateFrequency).execute();
        }
        else if (sf::Keyboard::isKeyPressed(keys[ROTATE_STOP_KEY]))
        {
            RotateCommand(selectedSolver, 0.0f).execute();
        }
        else if (sf::Keyboard::isKeyPressed(keys[ROTATE_CW_KEY]))
        {
            RotateCommand(selectedSolver, rotateFrequency).execute();
        }
    }
}

void EventController::handleMoveInputs(float elapsedTimeSinceLastFrame) const
{
    if (selectedVerlet) 
    {
        if (sf::Keyboard::isKeyPressed(keys[UP_KEY])) 
        {
            MoveCommand(selectedVerlet, -elapsedTimeSinceLastFrame*downAcceleration).execute();
        }
        else if (sf::Keyboard::isKeyPressed(keys[DOWN_KEY]))
        {
            MoveCommand(selectedVerlet, elapsedTimeSinceLastFrame*downAcceleration).execute();
        }
    
        if (sf::Keyboard::isKeyPressed(keys[LEFT_KEY])) 
        {
            MoveCommand(selectedVerlet, -elapsedTimeSinceLastFrame*rightAcceleration).execute();
        }
        else if (sf::Keyboard::isKeyPressed(keys[RIGHT_KEY])) 
        {
            MoveCommand(selectedVerlet, elapsedTimeSinceLastFrame*rightAcceleration).execute();
        }
    }
}
