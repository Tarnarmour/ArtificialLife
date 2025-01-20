#include <SFML/Graphics.hpp>
#include <random>

#include "util.h"
#include "World.h"
#include "Creature.h"

using namespace sf;


World::World(int popsize, int width, int height) : width(width), height(height) {

    this->window = RenderWindow{ VideoMode(Vector2u(800, 600)), "The World" };

    for (int i = 0; i < popsize; i++) {
        this->addCreature(getRandomInt(0, this->window.getSize().x), getRandomInt(0, this->window.getSize().y));
    }
}

void World::addCreature(float x, float y) {
    this->population.push_back(Creature(x, y));
}

void World::clear() {
    this->population = std::vector<Creature>();
}

void World::update() {
    for (Creature& creature : this->population) {
        creature.move();
    }
}

void World::draw() {
    this->window.clear();
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