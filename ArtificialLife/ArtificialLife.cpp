// ArtificialLife.cpp : Defines the entry point for the application.
//

#include "ArtificialLife.h"
#include <SFML/Graphics.hpp>
#include <random>

#include "util.h"
#include "World.h"

#include <iostream>
#include <filesystem>


int main()
{
	std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

	World world{ 600, 1700, 1000 };
	world.run();
}
