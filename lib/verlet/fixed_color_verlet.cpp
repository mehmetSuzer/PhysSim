
#include "fixed_color_verlet.h"

FixedColorVerlet::FixedColorVerlet(const sf::Vector2f& position_, float radius_, float mass_, const sf::Color& color_) :
    Verlet(position_, radius_, mass_), color(color_)
{
    circle.setFillColor(color);
}
