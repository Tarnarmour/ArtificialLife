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
    height(height),
    interaction_range_slider(20, 20, 250, 1.0, 400.0, 50.0),
    avoidance_weight_slider(20, 50, 250, 0.0, 1.0, 0.25),
    coherence_weight_slider(20, 80, 250, 0.0, 1.0, 0.25),
    edge_weight_slider(20, 110, 250, 0.0, 1.0, 0.15)
{

    this->window = RenderWindow{ VideoMode(Vector2u(width, height)), "The World", Style::Titlebar | Style::Close };
    this->window.setFramerateLimit(60);
    this->window.setPosition(Vector2i{ 0, 0 });

    float border_proportion = 0.01;

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
    interaction_range_slider.update(window);
    avoidance_weight_slider.update(window);
    coherence_weight_slider.update(window);
    edge_weight_slider.update(window);
    float interaction_range = interaction_range_slider.getValue();
    float avoidance_weight = avoidance_weight_slider.getValue();
    float coherence_weight = coherence_weight_slider.getValue();
    float edge_weight = edge_weight_slider.getValue();

    std::vector<Vector2f> current_positions(population.size());
    std::vector<Vector2f> current_directions(population.size());
    
    std::transform(population.begin(), population.end(), current_positions.begin(), [](const Creature& creature) {return creature.getPosition(); });
    std::transform(population.begin(), population.end(), current_directions.begin(), [](const Creature& creature) {return creature.getDirection(); });

    for (Creature& creature : this->population) {
        //creature.move();
        creature.setInteractionRange(interaction_range);
        creature.setAvoidanceWeight(avoidance_weight);
        creature.setCoherenceWeight(coherence_weight);
        creature.setEdgeWeight(edge_weight);
        creature.swarm(current_positions, current_directions, width, height);
    }
}

void World::draw() {
    this->window.clear();
    for (const Creature& creature : this->population) {
        creature.draw(this->window);
    }
    interaction_range_slider.draw(window);
    coherence_weight_slider.draw(window);
    avoidance_weight_slider.draw(window);
    edge_weight_slider.draw(window);
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