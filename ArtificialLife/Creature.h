#pragma once

#include <SFML/Graphics.hpp>

class Creature {
public:

    struct State {
        sf::Vector2f position;
        sf::Vector2f direction;
    };

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

    // Getters / Setters
    sf::Vector2f getPosition() const;
    sf::Vector2f getDirection() const;

    void setState(sf::Vector2f newPosition, sf::Vector2f newDirection);

    // Methods
    void move();
    State swarm(const std::vector<Creature> population, int width, int height) const;
    void draw(sf::RenderWindow& window) const;
    void drawRanges(sf::RenderWindow& window) const;

private:
    sf::Vector2f direction;
    sf::Vector2f position;
    float velocity = 3.5f;
    float size = 5.0f;

    float coherenceRange{ 300.0f };
    float alignmentRange{ 100.0f };
    float avoidanceRange{ 75.0f };

    float coherenceWeight{ 0.01f };
    float alignmentWeight{ 0.01f };
    float avoidanceWeight{ 0.01f };
};
