#pragma once

#include <SFML/Graphics.hpp>
#include <random>

#include "Creature.h"
#include "Slider.h"

class World {
public:
    World(int popsize, int width, int height);
    World() : World(10, 800, 600) {}

    void run();
    void addCreature(Creature creature);
    void clear();
    void update();
    void draw();

private:
    int width;
    int height;
    sf::RenderWindow window;
    std::vector<Creature> population;
};