// ArtificialLife.cpp : Defines the entry point for the application.
//

#include "ArtificialLife.h"
#include <SFML/Graphics.hpp>
#include <random>

#include "util.h"
#include "World.h"


int main()
{
	World world{ 10, 800, 600 };
	world.run();
}
