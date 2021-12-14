#include <SFML/Graphics.hpp>

#include <ctime>
#include <iostream>
#include <random>

#include "Game.hpp"

int main()
{
    srand(time(0));

    Game game;
    game.run();
}
