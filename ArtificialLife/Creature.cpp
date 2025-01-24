#include <math.h>
#include <cstdlib>
#include <iostream>

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

void Creature::setState(Vector2f newPosition, Vector2f newDirection) {
    position = newPosition;
    direction = newDirection;
}

void Creature::move() {
    position.x += (rand() % 3 - 1);
    position.y += (rand() % 5 - 2);
}

Creature::State Creature::swarm(const std::vector<Creature> population, int width, int height) const {

    Vector2f newPosition = position;
    Vector2f newDirection = direction;

    Vector2f alignmentVector{ 0.0f, 0.0f };
    Vector2f averageNeighbor{ 0.0f, 0.0f };
    Vector2f avoidanceVector{ 0.0f, 0.0f };

    float n_coherence{ 0.0f };
    float n_alignment{ 0.0f };
    float n_avoidance{ 0.0f };

    for (Creature otherCreature : population) {
        if (otherCreature == *this)
            continue;

        Vector2f differenceVector = otherCreature.position - position;

        if (differenceVector.length() < coherenceRange) {
            averageNeighbor += otherCreature.position;
            n_coherence++;
        }

        if (differenceVector.length() < alignmentRange) {
            alignmentVector += otherCreature.direction;
            n_alignment++;
        }

        if (differenceVector.length() < avoidanceRange) {
            avoidanceVector += (position - otherCreature.position) / ((position - otherCreature.position).length());
            n_avoidance++;
        }
    }

    if (n_avoidance > 0 && avoidanceVector.length() > 0) {
        avoidanceVector /= n_avoidance;

        newDirection += avoidanceVector * avoidanceWeight;
    }

    if (n_coherence > 0 && averageNeighbor.length() > 0) {
        averageNeighbor /= n_coherence;
        Vector2f coherenceVector = averageNeighbor - position;
        coherenceVector /= coherenceVector.length();

        newDirection += coherenceVector * coherenceWeight;
    }

    if (n_alignment > 0 && alignmentVector.length() > 0) {
        alignmentVector /= n_alignment;

        newDirection += alignmentVector * alignmentWeight;
    }

    Vector2f wallVector{ 0.0f, 0.0f };

    float wallDist = 0.9f;

    if (position.x > wallDist * width) {
        wallVector.x = -(position.x / width - wallDist) / (1 - wallDist);
    }
    else if (position.x < 0.1 * width) {
        wallVector.x = position.x / width / (1 - wallDist);
    }

    if (position.y > wallDist * height) {
        wallVector.y = -(position.y / height - wallDist) / (1 - wallDist);
    }
    else if (position.y < 0.1 * height) {
        wallVector.y = position.y / height / (1 - wallDist);
    }

    newDirection = newDirection + wallVector * 0.1f;

    newDirection /= newDirection.length();

    newPosition += newDirection * velocity;

    if (newPosition.x > width) {
        newPosition.x = width;
        newDirection.x *= -1;
    }
    else if (newPosition.x < 0) {
        newPosition.x = 0;
        newDirection.x *= -1;
    }
    if (newPosition.y > height) {
        newPosition.y = height;
        newDirection.y *= -1;
    }
    else if (newPosition.y < 0) {
        newPosition.y = 0;
        newDirection.y *= -1;
    }

    return { newPosition, newDirection };
}

void Creature::draw(RenderWindow& window) const {
    CircleShape creatureSprite(size);
    creatureSprite.setFillColor(Color::Color(255, 255, 255, 255));
    creatureSprite.setPosition(Vector2f{position.x - size, position.y - size});
    window.draw(creatureSprite);
}

void Creature::drawRanges(RenderWindow& window) const {
    CircleShape coherenceSprite(coherenceRange);
    coherenceSprite.setFillColor(Color::Color(0, 255, 0, 1));
    coherenceSprite.setPosition(Vector2f{ position.x - coherenceRange, position.y - coherenceRange });
    window.draw(coherenceSprite);

    CircleShape avoidanceSprite(avoidanceRange);
    avoidanceSprite.setFillColor(Color::Color(255, 0, 0, 5));
    avoidanceSprite.setPosition(Vector2f{ position.x - avoidanceRange, position.y - avoidanceRange });
    window.draw(avoidanceSprite);

    CircleShape alignmentSprite(alignmentRange);
    alignmentSprite.setFillColor(Color::Color(0, 0, 255, 2));
    alignmentSprite.setPosition(Vector2f{ position.x - alignmentRange, position.y - alignmentRange });
    window.draw(alignmentSprite);
}
