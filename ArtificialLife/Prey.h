#pragma once

#include "Creature.h"

class Prey : public Creature {
public:
    Prey() : Creature() {}
    Prey(float x, float y, float theta) : Creature(x, y, theta) {}
    Prey(sf::Vector2f position, sf::Vector2f direction) : Creature(position, direction) {}

    Creature::State flee(const std::vector<Creature>& population);

};