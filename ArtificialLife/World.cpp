#include <math.h>
#include <SFML/Graphics.hpp>
#include <random>

#include "util.h"
#include "World.h"
#include "Creature.h"
#include "Slider.h"

using namespace sf;

World::World(int popsize, int width, int height) :
    width(width),
    height(height)
{

    this->window = RenderWindow{ VideoMode(Vector2u(width, height)), "The World", Style::Titlebar | Style::Close };
    this->window.setFramerateLimit(60);
    this->window.setPosition(Vector2i{ 0, 0 });

    float border_proportion{ 0.01f };

    for (int i = 0; i < popsize; i++) {
        Creature creature{ getRandomFloat(border_proportion * width, (1 - border_proportion) * width), getRandomFloat(border_proportion * height, (1 - border_proportion) * height), getRandomFloat(-PI, PI)};
        this->addCreature(creature);
    }
}

void World::addCreature(Creature creature) {
    this->population.push_back(creature);
}

void World::clear() {
    this->population = std::vector<Creature>();
}

void World::update() {

    std::vector<Vector2f> current_positions(population.size());
    std::vector<Vector2f> current_directions(population.size());
    
    std::transform(population.begin(), population.end(), current_positions.begin(), [](const Creature& creature) {return creature.getPosition(); });
    std::transform(population.begin(), population.end(), current_directions.begin(), [](const Creature& creature) {return creature.getDirection(); });

    std::vector<Creature::State> newStates(population.size());

    for (size_t i = 0; i < population.size(); i++) {
        newStates[i] = population[i].swarm(population, width, height);
    }

    for (size_t i = 0; i < population.size(); i++) {
        population[i].setState(newStates[i].position, newStates[i].direction);
    }
}

void World::draw() {
    this->window.clear();
    for (const Creature& creature : this->population) {
        creature.drawRanges(this->window);
    }
    for (const Creature& creature : this->population) {
        creature.draw(this->window);
    }
    this->window.display();
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