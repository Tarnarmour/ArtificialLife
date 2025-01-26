#include "Predator.h"
#include "Creature.h"

using namespace sf;

Creature::State Predator::swarm(const std::vector<std::unique_ptr<Creature>>& population, int width, int height) const {
    Vector2f newPosition = position;
    Vector2f newDirection = direction;

    Vector2f averageNeighbor{ 0.0f, 0.0f };
    Vector2f nearestVector{ 0.0f, 0.0f };
    Vector2f avoidanceVector{ 0.0f, 0.0f };

    float n_neighbor{ 0.0f };
    float n_avoidance{ 0.0f };

    for (auto& otherCreature : population) {
        if (*otherCreature == *this)
            continue;

        Vector2f differenceVector = otherCreature->position - position;

        if (otherCreature->getType() == Creature::Type::PREY) {

            if (differenceVector.length() < huntRange) {
                averageNeighbor += otherCreature->position;
                n_neighbor++;

                if (differenceVector.length() < nearestRange && differenceVector.length() < nearestVector.length() || nearestVector.length() == 0.0) {
                    nearestVector = differenceVector;
                }
            }
        }
        else if (differenceVector.length() < avoidanceRange) {
            avoidanceVector += differenceVector / differenceVector.lengthSquared();
            n_avoidance++;
        }
    }

    if (n_neighbor > 0 && averageNeighbor.length() > 0) {
        averageNeighbor /= n_neighbor;
        Vector2f coherenceVector = averageNeighbor - position;
        coherenceVector /= coherenceVector.length();

        newDirection += coherenceVector * groupWeight;
    }

    if (nearestVector.length() > 0.0) {
        newDirection += nearestVector / nearestVector.length() * nearestWeight;
    }

    if (n_avoidance > 0 && avoidanceVector.length() > 0) {
        newDirection += -avoidanceVector / avoidanceVector.length() * avoidanceWeight;
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

    newDirection += wallVector * wallWeight;

    newDirection /= newDirection.length();

    newPosition += velocity * newDirection;

    return { newPosition, newDirection };
}

void Predator::draw(RenderWindow& window) const {
    CircleShape creatureSprite(size);
    creatureSprite.setFillColor(Color::Color(255, 50, 50, 255));
    creatureSprite.setPosition(Vector2f{ position.x - size, position.y - size });
    window.draw(creatureSprite);
}