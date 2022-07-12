#pragma once
#include "Entities/Aircraft.hpp"
struct AircraftMover
{
    sf::Vector2f velocity;
    AircraftMover(float vx, float vy) : velocity(vx, vy)
    {
    }

    void operator()(SceneNode &node, sf::Time) const
    {
        Aircraft &aircraft = static_cast<Aircraft &>(node);
        aircraft.setVelocity(aircraft.getVelocity() + velocity);
    }
};
