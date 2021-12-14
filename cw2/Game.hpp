#ifndef GAME_HPP
#define GAME_HPP

#include "Creature.hpp"
#include "Hunter.hpp"
#include "LivingCreature.hpp"
#include "Plant.hpp"
#include "Prey.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <random>

class Game {
    int m_Xsize;
    int m_Ysize;

    const char* m_gameTitle = "Game of life";

    sf::RenderWindow m_window;

    int m_Nrow = 150; // square count per column or row

    int m_borderSize = 2;

    int m_squareSize;

    typedef Creature** CreatureArray;

    int m_sizeArrayCreatures = m_Nrow;
    int m_countCreatures = 0;

    CreatureArray* m_board;

    int m_steps = 0;

    // probabilities

    int m_probSizeArray;
    int* m_probArray;

    typedef enum CreatureInt {
        CreatureInt_Hunter = 1,
        CreatureInt_Prey = 2,
        CreatureInt_Plant = 3
    } CreatureInt;

    void fillProbArray();

    CreatureType chooseRandomCreatureType();

public:
    Game(int Xsize, int Ysize);

    Game(int Xsize);

    Game();

    sf::Vector2f getCoord(int, int);

    sf::RectangleShape createShape(Creature* creature);

    int isIndexAvailable(int x, int y);

    int isSideIndexAvailable();

    int isBoardFull();

    Creature* getCreature(CreatureType type, int onSide = 0);

    Creature* getRandomCreature();

    void initializeArray();

    void updateEnvironment();

    void lifeStep();

    int countHunters();

    int countPreys();

    void run();
};

#endif // #ifndef GAME_HPP
