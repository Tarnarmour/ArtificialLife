#include "Creature.h"
#include <cstdlib>

using namespace sf;

Creature::Creature(float x, float y) {
    position = Vector2f(x, y);
}

void Creature::move() {
    position.x += (rand() % 3 - 1);
    position.y += (rand() % 5 - 2);
}

void Creature::draw(RenderWindow& window) const {
    CircleShape creatureSprite(10.0f);
    creatureSprite.setFillColor(Color::Blue);
    creatureSprite.setPosition(position);
    window.draw(creatureSprite);
}
