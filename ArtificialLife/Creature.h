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

    bool operator==(const Creature& other) {
        return &other == this;
    }

    bool operator!=(const Creature& other) {
        return &other != this;
    }

    // Getters / Setters
    sf::Vector2f getPosition() const;
    sf::Vector2f getDirection() const;

    void setState(sf::Vector2f newPosition, sf::Vector2f newDirection);

    // Methods
    void move();
    State swarm(const std::vector<Creature> population, int width, int height) const;
    void draw(sf::RenderWindow& window) const;

private:
    sf::Vector2f direction;
    sf::Vector2f position;
    float velocity = 2.5f;
    float size = 5.0f;

    float avoidance_weight = 0.25f;
    float coherence_weight = 0.025f;
    float edge_weight = 0.1f;

    float interaction_range = 200.0f;
};
