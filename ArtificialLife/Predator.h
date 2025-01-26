#pragma once

#include "Creature.h"

class Predator : public Creature {
public:
    Predator() : Creature() {}
    Predator(float x, float y, float theta) : Creature(x, y, theta) {}
    Predator(sf::Vector2f position, sf::Vector2f direction) : Creature(position, direction) {}

    void draw(sf::RenderWindow& window) const;

    Creature::State swarm(const std::vector<std::unique_ptr<Creature>>& population, int width, int height) const override;

    Creature::Type getType() const { return Creature::Type::PREDATOR; };

private:
    float velocity{ 6.0f };

    float huntRange{ 1000.0f };
    float avoidanceRange{ 200.0f };
    float nearestRange{ 150.0f };

    float groupWeight{ 0.01f };
    float nearestWeight{ 0.15f };
    float avoidanceWeight{ 0.01f };
    float wallWeight{ 0.25f };
};