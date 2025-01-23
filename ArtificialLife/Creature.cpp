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

    float A1{ 0.2 };
    float B1{ 500.0 };

    float A2{ 0.25 };
    float B2{ 250.0 };

    for (Creature otherCreature : population) {
        if (&otherCreature == this)
            continue;

        Vector2f differenceVector = otherCreature.position - position;
        float distance = differenceVector.length();

        if (distance < 0.1)
            continue;

        Vector2f differenceUnitVector = differenceVector / distance;

        if (direction.dot(differenceUnitVector) < -0.25)
            continue;

        newDirection += A1 * float(expf(-distance * distance / B1) - 0.001) * -differenceVector / distance;

        newDirection += A2 * expf(-distance * distance / B2) * otherCreature.direction;
    }

    if (newDirection.length() > 0)
        newDirection /= newDirection.length();
    else
        newDirection = direction;

    Vector2f wallVector{ 0.0f, 0.0f };

    float wallDist = 0.9;

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
    creatureSprite.setFillColor(Color::Blue);
    creatureSprite.setPosition(Vector2f{position.x - size, position.y - size});
    window.draw(creatureSprite);
}
