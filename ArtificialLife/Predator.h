#pragma once

#include "Creature.h"

class Predator : public Creature {
public:
    Predator() : Creature() {}
    Predator(float x, float y, float theta) : Creature(x, y, theta) {}
    Predator(sf::Vector2f position, sf::Vector2f direction) : Creature(position, direction) {}

    void draw(sf::RenderWindow& window) const;

    Creature::State hunt(const std::vector<std::unique_ptr<Creature>>& population, float width, float height) const;

    Creature::Type getType() const { return Creature::Type::PREDATOR; };
};