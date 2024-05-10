
#include "speed_color_verlet.h"

void SpeedColorVerlet::updateColor(float dt)
{
    const float speed = getSpeed(dt);
    uint8_t red;
    uint8_t green;
    uint8_t blue;

    if (speed < speedLevel1) 
    {
        red = 0;
        green = static_cast<uint8_t>(255.0f * speed / speedLevel1);
        blue = 255;
    } else if (speed < speedLevel2)
    {
        red = static_cast<uint8_t>(255.0f * (speed-speedLevel1) / (speedLevel2-speedLevel1));
        green = 255;
        blue = static_cast<uint8_t>(255.0f * (speedLevel2-speed) / (speedLevel2-speedLevel1));
    } else if (speed < speedLevel3)
    {
        red = 255;
        green = static_cast<uint8_t>(255.0f * (speedLevel3-speed) / (speedLevel3-speedLevel2));
        blue = 0;
    } else
    {
        red = 255;
        green = 0;
        blue = 0;
    }

    const sf::Color color = sf::Color(red, green, blue);
    circle.setFillColor(color);
}
