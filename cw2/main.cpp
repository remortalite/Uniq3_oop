#include <SFML/Graphics.hpp>

#include <iostream>
#include <random>
#include <ctime>

#include "Game.hpp"

int main() {
	srand(time(0));

	Game game;
	game.run();
}
