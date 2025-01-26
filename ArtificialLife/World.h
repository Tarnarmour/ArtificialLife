#pragma once

#include <SFML/Graphics.hpp>
#include <random>

#include "Creature.h"
#include "Slider.h"

class World {
public:
    World(int preyPopSize, int predatorPopSize, int width, int height);
    World() : World(10, 1, 800, 600) {}

    void run();
    void clear();
    void update();
    void draw();

private:
    int width;
    int height;
    sf::RenderWindow window;
    std::vector<std::unique_ptr<Creature>> population;
};