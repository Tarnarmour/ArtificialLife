#pragma once

#include "Creature.h"

class Prey : public Creature {
public:
    Prey() : Creature() {}
    Prey(float x, float y, float theta) : Creature(x, y, theta) {}
    Prey(sf::Vector2f position, sf::Vector2f direction) : Creature(position, direction) {}

    void draw(sf::RenderWindow& window) const;

    Creature::State swarm(const std::vector<std::unique_ptr<Creature>>& population, int width, int height) override;

    Creature::Type getType() const { return Creature::Type::PREY; };

private:
    Type creatureType{ Type::PREY };
    bool alive{ true };
    float velocity{ 5.0f };

    float coherenceRange{ 600.0f };
    float alignmentRange{ 100.0f };
    float avoidanceRange{ 45.0f };
    float fleeRange{ 275.0f };

    float wallWeight{ 0.1f };
    float coherenceWeight{ 0.02f };
    float alignmentWeight{ 0.015f };
    float avoidanceWeight{ 0.03f };
    float fleeWeight{ 0.0002f };
};