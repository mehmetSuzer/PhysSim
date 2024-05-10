
#ifndef __SPEED_COLOR_VERLET_H__
#define __SPEED_COLOR_VERLET_H__

#include "verlet.h"

class VerletPool;

class SpeedColorVerlet : public Verlet {
    friend class VerletPool;

private:
    const float speedLevel1 = 50.0f;
    const float speedLevel2 = 100.0f;
    const float speedLevel3 = 150.0f;

    SpeedColorVerlet() {} // only verlet pool can create instances of this class
    
    void updateColor(float dt) override
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
        circle.setFillColor(sf::Color(red, green, blue));
    }

    uint32_t type() const override
    {
        return SPEED_COLOR;
    }
};

#endif // __SPEED_COLOR_VERLET_H__
