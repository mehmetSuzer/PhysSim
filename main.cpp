
#include "solver.h"
#include "renderer.h"
#include "event_controller.h"

#include "circle_constraint.h"
#include "rectangle_constraint.h"
#include "ellipse_constraint.h"
#include "arc_constraint.h"

#define WINDOW_WIDTH    800UL
#define WINDOW_HEIGHT   800UL
#define VERLET_COUNT    2000UL
#define PHYSICS_UPDATE_PER_SECOND   60UL

#define CONSTRAINT ARC_CONSTRAINT

const float secondsPerPhysicsUpdate = 1.0f / static_cast<float>(PHYSICS_UPDATE_PER_SECOND);
const sf::Vector2f windowCenter = sf::Vector2f(WINDOW_WIDTH/2.0f, WINDOW_HEIGHT/2.0f);
const std::string dataPath = "data/";

int main(int argc, char **argv)
{
    // Initialize the window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Physics Simulation", sf::Style::Default, settings);
    window.setFramerateLimit(PHYSICS_UPDATE_PER_SECOND);

    // Initialize the renderer and set the font
    Renderer& renderer = Renderer::instance();
    renderer.setFont((dataPath + "Roboto-Medium.ttf").c_str());

    // Initialize the constraint
#if CONSTRAINT == CIRCLE_CONSTRAINT
    const float radius = 350.0f;
    CircleConstraint constraint = CircleConstraint(windowCenter, radius);
#elif CONSTRAINT == RECTANGLE_CONTRAINT
    const float width = 600.0f;
    const float height = 400.0f;
    const float rotationAngleRadian = M_PIf / 2.0f;
    RectangleConstraint constraint = RectangleConstraint(windowCenter, width, height, rotationAngleRadian);
#elif CONSTRAINT == ELLIPSE_CONSTRAINT
    const sf::Vector2f radius = sf::Vector2f(400.0f, 240.0f);
    const float rotationAngleRadian = M_PIf/6.0f;
    EllipseConstraint constraint = EllipseConstraint(windowCenter, radius, rotationAngleRadian);
#elif CONSTRAINT == ARC_CONSTRAINT
    const float radius = 350.0f;
    const float sweepAngleRadian = M_PIf / 3.0f;
    const float rotationAngleRadian = 4.0f * M_PIf / 3.0f;
    const bool isHole = true;
    ArcConstraint constraint = ArcConstraint(windowCenter, radius, sweepAngleRadian, rotationAngleRadian, isHole);
#endif

    // Initialize the solver that handles physics
    Solver solver = Solver(secondsPerPhysicsUpdate, constraint);
    solver.activateConstraint();
    // solver.setConstraintRotation(0.1f);

    // Add a controllable verlet
    solver.addSpeedColorVerlet(windowCenter, 4.0f, 100.0f);

    // Add uncontrollable verlets
    for (uint32_t i = 0; i < VERLET_COUNT-1; i++)
    {
        const float x = randf(200.0f, 600.0f);
        const float y = randf(200.0f, 600.0f);
        const sf::Vector2f position = sf::Vector2f(x,y);
        const float radius = 2.0f;
        const float mass = 1.0f;
        solver.addSpeedColorVerlet(position, radius, mass);
    }

    // Setup the event controller
    EventController& eventController = EventController::instance();
    eventController.setSelectedWindow(&window);
    eventController.setSelectedVerlet(solver.getVerlet(0));
    eventController.setSelectedSolver(&solver);
    eventController.setMusic((dataPath + "music.ogg").c_str());

    // Initialize clock to handle time
    sf::Clock clock;
    
    while (window.isOpen())
    {
        // Handle timing
        float elapsedTimeSinceLastFrame = clock.getElapsedTime().asSeconds();
        clock.restart();

        // Handle events and commands
        eventController.handleEvents();
        eventController.handleInputs(elapsedTimeSinceLastFrame);

        // Update physics
        solver.update(elapsedTimeSinceLastFrame);

        // Render the screen
        renderer.draw(window, solver);
        renderer.drawFPS(window, elapsedTimeSinceLastFrame);
        window.display();
    }

    window.close();
    return 0;
}
