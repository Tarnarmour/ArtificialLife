#pragma once

#include "Creature.h"

class Predator : public Creature {
public:
    Predator() : Creature() {}
    Predator(float x, float y, float theta) : Creature(x, y, theta) {}
    Predator(sf::Vector2f position, sf::Vector2f direction) : Creature(position, direction) {}

    Creature::State hunt(const std::vector<Creature>& population, float width, float height) const;

};