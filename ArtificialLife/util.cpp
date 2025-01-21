#include <random>

static std::random_device rd;
static std::mt19937 gen(rd());

int getRandomInt(int low, int high) {
    return std::uniform_int_distribution<>(low, high)(gen);
}

float getRandomFloat(float low, float high) {
    return std::uniform_real_distribution<float>(low, high)(gen);
}