#pragma once

#include "Creature.h"

class Prey : public Creature {
public:
    Prey() : Creature() {}
    Prey(float x, float y, float theta) : Creature(x, y, theta) {}
    Prey(sf::Vector2f position, sf::Vector2f direction) : Creature(position, direction) {}

    void draw(sf::RenderWindow& window) const;

    Creature::State flee(const std::vector<std::unique_ptr<Creature>>& population, float width, float height) const;

    Creature::Type getType() const { return Creature::Type::PREY; };

};