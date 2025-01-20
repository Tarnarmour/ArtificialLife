#pragma once

#include <SFML/Graphics.hpp>

class Creature {
public:
    // Constructors
    Creature(float x, float y);

    // Methods
    void move();

    void draw(sf::RenderWindow& window) const;

private:
    sf::Vector2f position;
};
