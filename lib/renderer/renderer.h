
#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <assert.h>
#include "solver.h"

class Renderer {
private:
    static Renderer instance_;

    sf::Font font;
    sf::Text text;

    const sf::Color backgroundColor = sf::Color(128, 128, 128);
    const float FPSUpdatePeriod = 0.1f; 
    float elapsedTimeSinceLastFPSUpdate = 0.0f;
    uint32_t frameCount = 0;
    float fps = 0.0f;

    Renderer() {
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Style::Regular);
        text.setPosition(sf::Vector2f(10.0f, 10.0f));
    };

public:
    static Renderer& instance();
    void setFont(const char* fontFile);
    void drawFPS(sf::RenderTarget& renderTarget, float elapsedTimeSinceLastFrame);
    void draw(sf::RenderTarget& renderTarget, const Solver& solver) const;
};

#endif // __RENDERER_H__
