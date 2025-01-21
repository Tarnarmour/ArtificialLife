#include "Slider.h"
#include <algorithm> // For std::max and std::min

Slider::Slider(float x, float y, float length, float min, float max, float initial)
    : position(x, y), length(length), minValue(min), maxValue(max), currentValue(initial) {
    // Slider bar (background)
    bar.setSize(sf::Vector2f(length, 10));
    bar.setFillColor(sf::Color::White);
    bar.setPosition(position);

    // Slider handle (foreground)
    handle.setSize(sf::Vector2f(20, 20));
    handle.setFillColor(sf::Color::Red);
    handle.setPosition(sf::Vector2f{ position.x, position.y - 5 }); // Position above the bar

    // Set up the range of the slider
    handlePosition = position.x;
}

void Slider::update(sf::RenderWindow& window) {
    // Check if mouse is pressing the slider handle
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (handle.getGlobalBounds().contains(sf::Vector2f{ static_cast<float>(mousePos.x), static_cast<float>(mousePos.y) })) {
            handlePosition = static_cast<float>(mousePos.x) - handle.getSize().x / 2; // Center the handle
            // Clamp the handle position between the slider min and max
            handlePosition = std::max(handlePosition, position.x);
            handlePosition = std::min(handlePosition, position.x + length - handle.getSize().x);
            currentValue = (handlePosition - position.x) / length * (maxValue - minValue) + minValue;
        }
    }

    handle.setPosition(sf::Vector2f{ handlePosition, position.y - 5 }); // Keep the handle above the slider
}

void Slider::draw(sf::RenderWindow& window) {
    window.draw(bar);   // Draw the slider bar
    window.draw(handle); // Draw the slider handle
}

float Slider::getValue() const {
    return currentValue;
}
