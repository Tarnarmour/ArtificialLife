#pragma once

#include <SFML/Graphics.hpp>

class Creature {
public:
    // Constructors
    Creature();
    Creature(float x, float y, float theta);
    Creature(sf::Vector2f position, sf::Vector2f direction);

    // Getters / Setters
    sf::Vector2f getPosition() const;
    sf::Vector2f getDirection() const;

    void setInteractionRange(float new_value);
    void setAvoidanceWeight(float new_value);
    void setCoherenceWeight(float new_value);
    void setEdgeWeight(float new_value);

    // Methods
    void move();
    void swarm(const std::vector<sf::Vector2f> current_positions, const std::vector<sf::Vector2f> current_directions, int width, int height);
    void draw(sf::RenderWindow& window) const;

private:
    sf::Vector2f direction;
    sf::Vector2f position;
    float velocity = 3.0f;
    float size = 5.0f;

    float avoidance_weight = 0.25f;
    float coherence_weight = 0.025f;
    float edge_weight = 0.1f;

    float interaction_range = 200.0f;
};
