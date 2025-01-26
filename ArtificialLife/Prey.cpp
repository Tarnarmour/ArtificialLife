#include "Prey.h"
#include "Creature.h"

using namespace sf;

Creature::State Prey::swarm(const std::vector<std::unique_ptr<Creature>>& population, int width, int height) const {
    Vector2f newPosition = position;
    Vector2f newDirection = direction;

    Vector2f alignmentVector{ 0.0f, 0.0f };
    Vector2f averageNeighbor{ 0.0f, 0.0f };
    Vector2f avoidanceVector{ 0.0f, 0.0f };
    Vector2f fleeVector{ 0.0f, 0.0f };

    float n_coherence{ 0.0f };
    float n_alignment{ 0.0f };
    float n_avoidance{ 0.0f };
    float n_flee{ 0.0f };

    for (auto& otherCreature : population) {
        if (*otherCreature == *this)
            continue;

        Vector2f differenceVector = otherCreature->position - position;

        if (otherCreature->getType() == Type::PREY) {

            if (differenceVector.length() < coherenceRange) {
                averageNeighbor += otherCreature->position;
                n_coherence++;
            }

            if (differenceVector.length() < alignmentRange) {
                alignmentVector += otherCreature->direction;
                n_alignment++;
            }

            if (differenceVector.length() < avoidanceRange) {
                avoidanceVector += differenceVector / (differenceVector.length());
                n_avoidance++;
            }
        }
        else {
            if (differenceVector.length() < fleeRange) {
                fleeVector += fleeRange * fleeRange * differenceVector / (differenceVector.length() * differenceVector.length());
                n_flee++;
            }
        }
    }

    if (n_avoidance > 0 && avoidanceVector.length() > 0) {
        avoidanceVector /= n_avoidance;

        newDirection -= avoidanceVector * avoidanceWeight;
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

    if (n_flee > 0 && fleeVector.length() > 0) {
        fleeVector /= n_flee;

        newDirection -= fleeVector * fleeWeight;
    }

    Vector2f wallVector{ 0.0f, 0.0f };

    float wallDist = 0.9f;

    if (position.x > wallDist * width) {
        wallVector.x = -(position.x / width - wallDist) / (1 - wallDist);
    }
    else if (position.x < (1 - wallDist) * width) {
        wallVector.x = -(position.x / width + wallDist - 1) / (1 - wallDist);
    }

    if (position.y > wallDist * height) {
        wallVector.y = -(position.y / height - wallDist) / (1 - wallDist);
    }
    else if (position.y < (1 - wallDist) * height) {
        wallVector.y = -(position.y / height + wallDist - 1) / (1 - wallDist);
    }

    newDirection = newDirection + wallVector * wallWeight;

    newDirection /= newDirection.length();

    newPosition += newDirection * velocity;

    return { newPosition, newDirection };
}

void Prey::draw(RenderWindow& window) const {
    CircleShape creatureSprite(size);
    creatureSprite.setFillColor(Color::Color(50, 255, 50, 255));
    creatureSprite.setPosition(Vector2f{ position.x - size, position.y - size });
    window.draw(creatureSprite);
}