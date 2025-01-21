#include <math.h>
#include <cstdlib>

#include "util.h"
#include "Creature.h"

using namespace sf;

Creature::Creature() : position{ 0, 0 }, direction{ 1, 0 } {

}

Creature::Creature(float x, float y, float theta) {
    position = Vector2f(x, y);
    direction = Vector2f(std::cos(theta), std::sin(theta));
}

Creature::Creature(Vector2f position, Vector2f direction) : position(position) {
    if (direction.length() != 0) {
        this->direction = direction / direction.length();
    }
    else {
        direction = Vector2f{ 1, 0 };
    }
}

Vector2f Creature::getPosition() const {
    return position;
}

Vector2f Creature::getDirection() const {
    return direction;
}

void Creature::setInteractionRange(float new_value) {
    interaction_range = new_value;
}

void Creature::setAvoidanceWeight(float new_value) {
    avoidance_weight = new_value;
}

void Creature::setCoherenceWeight(float new_value) {
    coherence_weight = new_value;
}

void Creature::setEdgeWeight(float new_value) {
    edge_weight = new_value;
}

void Creature::move() {
    position.x += (rand() % 3 - 1);
    position.y += (rand() % 5 - 2);
}

void Creature::swarm(const std::vector<Vector2f> current_positions, const std::vector<Vector2f> current_directions, int width, int height) {
    size_t n = current_positions.size();

    Vector2f avoidance_vector{ 0., 0. };
    Vector2f coherence_vector{ 0., 0. };
    Vector2f edge_vector{ interaction_range / (10 + position.x) - interaction_range / (10 + width - position.x), interaction_range / (10 + position.y) - interaction_range / (10 + height - position.y) };
    
    for (int i = 0; i < current_positions.size(); i++) {
        if (current_positions[i] == position)
            continue;

        Vector2f difference = position - current_positions[i];
        float distance = difference.length();

        if (distance > interaction_range)
            continue;

        avoidance_vector += difference / (distance * distance * n);
        coherence_vector += current_directions[i] / (distance * distance * n);
    }

    if (avoidance_vector.length() != 0)
        avoidance_vector /= avoidance_vector.length();

    if (coherence_vector.length() != 0)
        coherence_vector /= coherence_vector.length();

    // Normalize direction vector
    direction += edge_vector * edge_weight + avoidance_vector * avoidance_weight + coherence_vector * coherence_weight;
    direction /= this->direction.length();

    this->position += velocity * this->direction;

    if (this->position.x > width) {
        this->position.x = float(width);
        this->direction.x *= -1.0f;
    }
    else if (this->position.x < 0) {
        this->position.x = 0.0f;
        this->direction.x *= -1.0f;
    }
    if (this->position.y > height) {
        this->position.y = float(height);
        this->direction.y *= -1.0f;
    }
    if (this->position.y < 0) {
        this->position.y = 0.0f;
        this->direction.y *= -1.0f;
    }
}

void Creature::draw(RenderWindow& window) const {
    CircleShape creatureSprite(size);
    creatureSprite.setFillColor(Color::Blue);
    creatureSprite.setPosition(Vector2f{position.x - size, position.y - size});
    window.draw(creatureSprite);

    //CircleShape interactionRange(interaction_range);
    //interactionRange.setFillColor(Color(0, 0, 200, 50));
    //interactionRange.setPosition(Vector2f{ position.x - interaction_range, position.y - interaction_range });
    //window.draw(interactionRange);
}
