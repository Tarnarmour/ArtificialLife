#include "Predator.h"
#include "Creature.h"

using namespace sf;

Creature::State Predator::hunt(const std::vector<std::unique_ptr<Creature>>& population, float width, float height) const {
    Vector2f newPosition = position;
    Vector2f newDirection = direction;

    Vector2f alignmentVector{ 0.0f, 0.0f };
    Vector2f averageNeighbor{ 0.0f, 0.0f };
    Vector2f avoidanceVector{ 0.0f, 0.0f };

    float n_coherence{ 0.0f };
    float n_alignment{ 0.0f };
    float n_avoidance{ 0.0f };

    for (auto& otherCreature : population) {
        if (*otherCreature == *this)
            continue;

        Vector2f differenceVector = otherCreature->position - position;

        if (differenceVector.length() < coherenceRange) {
            averageNeighbor += otherCreature->position;
            n_coherence++;
        }

        if (differenceVector.length() < alignmentRange) {
            alignmentVector += otherCreature->direction;
            n_alignment++;
        }

        if (differenceVector.length() < avoidanceRange) {
            avoidanceVector += (position - otherCreature->position) / ((position - otherCreature->position).length());
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

void Predator::draw(RenderWindow& window) const {
    CircleShape creatureSprite(size);
    creatureSprite.setFillColor(Color::Color(255, 50, 50, 255));
    creatureSprite.setPosition(Vector2f{ position.x - size, position.y - size });
    window.draw(creatureSprite);
}