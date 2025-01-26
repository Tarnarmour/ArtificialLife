#include <math.h>
#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>

#include "util.h"
#include "World.h"
#include "Creature.h"
#include "Prey.h"
#include "Predator.h"
#include "Slider.h"

using namespace sf;

World::World(int preyPopSize, int predatorPopSize, int width, int height) :
    width(width),
    height(height)
{

    this->window = RenderWindow{ VideoMode(Vector2u(width, height)), "The World", Style::Titlebar | Style::Close };
    this->window.setFramerateLimit(60);
    this->window.setPosition(Vector2i{ 0, 0 });

    float border_proportion{ 0.01f };

    for (int i = 0; i < preyPopSize; i++) {

        float x = getRandomFloat(border_proportion * width, (1 - border_proportion) * width);
        float y = getRandomFloat(border_proportion * height, (1 - border_proportion) * height);
        float theta = getRandomFloat(-PI, PI);

        population.push_back(std::make_unique<Prey>(x, y, theta));
    }

    for (int i = 0; i < predatorPopSize; i++) {
        float x = getRandomFloat(border_proportion * width, (1 - border_proportion) * width);
        float y = getRandomFloat(border_proportion * height, (1 - border_proportion) * height);
        float theta = getRandomFloat(-PI, PI);

        population.push_back(std::make_unique<Predator>(x, y, theta));
    }
}

void World::clear() {
    population = std::vector<std::unique_ptr<Creature>>();
}

void World::update() {

    std::vector<Creature::State> newStates(population.size());

    for (size_t i = 0; i < population.size(); i++) {
        newStates[i] = population[i]->swarm(population, width, height);
    }

    for (size_t i = 0; i < population.size(); i++) {
        population[i]->setState(newStates[i].position, newStates[i].direction);
    }
}

void World::draw() {
    window.clear();
    //for (auto& creature : population) {
    //    creature->drawRanges(window);
    //}
    for (auto& creature : population) {
        creature->draw(this->window);
    }
    window.display();
}

void World::run() {
    while (this->window.isOpen()) {
        this->window.clear();
        while (const std::optional event = this->window.pollEvent()) {
            if (event->is<Event::Closed>())
                window.close();
        }
        this->update();
        this->draw();
    }
}