#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Slider {
public:
    Slider(float x, float y, float length, float min, float max, float initial);

    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    float getValue() const;

private:
    sf::Vector2f position;
    float length;
    float minValue, maxValue, currentValue;
    float handlePosition;

    sf::RectangleShape bar;
    sf::RectangleShape handle;
};
