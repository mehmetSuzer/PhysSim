
#include "renderer.h"

Renderer Renderer::instance_;

Renderer& Renderer::instance()
{
    return instance_;
}

void Renderer::setFont(const char* fontFile)
{
    assert(font.loadFromFile(fontFile));
    text.setFont(font);
}

void Renderer::drawFPS(sf::RenderTarget& renderTarget, float elapsedTimeSinceLastFrame)
{
    elapsedTimeSinceLastFPSUpdate += elapsedTimeSinceLastFrame;
    frameCount++;
    if (elapsedTimeSinceLastFPSUpdate > FPSUpdatePeriod)
    {
        fps = frameCount / elapsedTimeSinceLastFPSUpdate;
        elapsedTimeSinceLastFPSUpdate = 0.0f;
        frameCount = 0;
    }
    
    char string[30];
    sprintf(string, "FPS: %u", static_cast<uint32_t>(fps));
    text.setString(string);
    renderTarget.draw(text);
}

void Renderer::draw(sf::RenderTarget& renderTarget, const Solver& solver) const {
    renderTarget.clear(backgroundColor);
    if (solver.isConstraintActive())
    {
        solver.getConstraint().draw(renderTarget);
    }

    const std::vector<Verlet*> verlets = solver.getVerlets();
    for (Verlet* verlet: verlets) 
    {
        verlet->draw(renderTarget);
    }
}
