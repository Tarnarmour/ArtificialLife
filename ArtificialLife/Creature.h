#pragma once

#include <SFML/Graphics.hpp>

class Creature {
public:

    struct State {
        sf::Vector2f position;
        sf::Vector2f direction;
    };

    enum class Type { NONE, PREDATOR, PREY };

    // Constructors
    Creature();
    Creature(float x, float y, float theta);
    Creature(sf::Vector2f position, sf::Vector2f direction);

    bool operator==(const Creature& other) const {
        return other.position.x == position.x && other.position.y == position.y;
    }

    bool operator!=(const Creature& other) const {
        return !(other == *this);
    }

    // Getters \ Setters
    sf::Vector2f getPosition() const;
    sf::Vector2f getDirection() const;

    void setState(sf::Vector2f newPosition, sf::Vector2f newDirection);

    // ******** Movement *********

    // Random movement
    void move();

    // Range-based swarming
    virtual State swarm(const std::vector<std::unique_ptr<Creature>>& population, int width, int height) const;

    // Semi-deprecated version of swarm
    State swarm_exp(const std::vector<std::unique_ptr<Creature>>& population, int width, int height) const;

    // ******* Drawing **********
    virtual void draw(sf::RenderWindow& window) const;
    virtual void drawRanges(sf::RenderWindow& window) const;

    // ******** Virtual functions **********
    virtual Type getType() const { return Type::NONE; };

    // Public Attributes
    sf::Vector2f direction;
    sf::Vector2f position;

protected:
    float velocity = 3.5f;
    float size = 5.0f;

    float coherenceRange{ 300.0f };
    float alignmentRange{ 100.0f };
    float avoidanceRange{ 25.0f };

    float coherenceWeight{ 0.05f };
    float alignmentWeight{ 0.005f };
    float avoidanceWeight{ 0.075f };
};
