#include "Game.hpp"

void Game::fillProbArray()
{
    int coef = 100;

    int hunterProb = Hunter(0, 0).getProb() * coef;
    int preyProb = Prey(0, 0).getProb() * coef;
    int plantProb = Plant(0, 0).getProb() * coef;
    m_probSizeArray = hunterProb + preyProb + plantProb;

    m_probArray = new int[m_probSizeArray];
    for (int i = 0; i < hunterProb; ++i)
        m_probArray[i] = CreatureInt_Hunter;
    for (int i = 0; i < preyProb; ++i)
        m_probArray[hunterProb + i] = CreatureInt_Prey;
    for (int i = 0; i < plantProb; ++i)
        m_probArray[m_probSizeArray - 1 - i] = CreatureInt_Plant;
}

CreatureType Game::chooseRandomCreatureType()
{
    int randIdx = rand() % m_probSizeArray;
    switch (m_probArray[randIdx]) {
    case CreatureInt_Hunter:
        return CreatureType::Hunter;
    case CreatureInt_Prey:
        return CreatureType::Prey;
    case CreatureInt_Plant:
        return CreatureType::Plant;
    default:
        std::cerr << "Errrr choose (" << m_probArray[randIdx]
                  << ") ! That not supposed to happen!" << std::endl;
    }
    return CreatureType::Plant;
}

Game::Game(int Xsize, int Ysize)
    : m_Xsize(Xsize),
      m_Ysize(Ysize),
      m_window(sf::VideoMode(m_Xsize, m_Ysize), m_gameTitle)
{
    m_squareSize
            = (m_Xsize < m_Ysize ? m_Xsize : m_Ysize) / m_Nrow - m_borderSize;
    m_board = new Creature**[m_Nrow];
    for (int i = 0; i < m_Nrow; ++i) {
        m_board[i] = new Creature*[m_Nrow];
        for (int j = 0; j < m_Nrow; ++j)
            m_board[i][j] = nullptr;
    }
    initializeArray();
}

Game::Game(int Xsize) : Game(Xsize, Xsize)
{
}

Game::Game() : Game(600, 600)
{
}

sf::Vector2f Game::getCoord(int idxX, int idxY)
{
    float coordX = idxX * (m_squareSize + m_borderSize);
    float coordY = idxY * (m_squareSize + m_borderSize);
    return sf::Vector2f(coordX, coordY);
}

sf::RectangleShape Game::createShape(Creature* creature)
{
    sf::RectangleShape shape
            = sf::RectangleShape(sf::Vector2f(m_squareSize, m_squareSize));
    shape.setPosition(getCoord(creature->getX(), creature->getY()));
    shape.setFillColor(creature->getColor());
    return shape;
}

int Game::isIndexAvailable(int x, int y)
{
    if (m_board[x][y] == nullptr)
        return 1;
    return 0;
}

int Game::isSideIndexAvailable()
{
    for (int i = 0; i < m_Nrow; ++i)
        if (m_board[i][0] == nullptr || m_board[i][m_Nrow - 1] == nullptr)
            return 1;
    for (int j = 0; j < m_Nrow; ++j)
        if (m_board[0][j] == nullptr || m_board[m_Nrow - 1][j] == nullptr)
            return 1;
    return 0;
}

int Game::isBoardFull()
{
    for (int i = 0; i < m_Nrow; ++i)
        for (int j = 0; j < m_Nrow; ++j)
            if (m_board[i][j] == nullptr)
                return 0;
    return 1;
}

Creature* Game::getCreature(CreatureType type, int onSide)
{
    int randX, randY;
    if (m_countCreatures + 1 > m_Nrow * m_Nrow || isBoardFull() == 1) {
        std::cerr << "No available cell!" << std::endl;
        return nullptr;
    }
    if (onSide == 1) {
        if (isSideIndexAvailable() == 0) {
            return nullptr;
        }
    }
    int counter = 0;
    do {
        randX = rand() % m_Nrow;
        randY = rand() % m_Nrow;
        if (onSide) {
            int onSideCoef = rand() % 2;
            int onSideCoef9 = rand() % 2;
            randX *= onSideCoef;
            randY *= !onSideCoef;
            randX += randX ? 0 : onSideCoef9 ? m_Nrow - 1 : 0;
            randY += randY ? 0 : onSideCoef9 ? m_Nrow - 1 : 0;
        }
        ++counter;
    } while (isIndexAvailable(randX, randY) == 0);

    switch (type) {
    case CreatureType::Hunter:
        return new Hunter(randX, randY);
    case CreatureType::Prey:
        return new Prey(randX, randY);
    case CreatureType::Plant:
        return new Plant(randX, randY);
    default:
        std::cerr << "Errrr get! That not supposed to happen!" << std::endl;
        break;
    }
    return nullptr;
}

Creature* Game::getRandomCreature()
{
    switch (chooseRandomCreatureType()) {
    case CreatureType::Hunter:
        return getCreature(CreatureType::Hunter);
    case CreatureType::Prey:
        return getCreature(CreatureType::Prey);
    case CreatureType::Plant:
        return getCreature(CreatureType::Plant);
    default:
        std::cerr << "Errrr! That not supposed to happen!" << std::endl;
    }
    return nullptr;
}

void Game::initializeArray()
{
    fillProbArray();
    for (int i = 0; i < m_sizeArrayCreatures; ++i) {
        Creature* creature = getRandomCreature();

        if (creature == nullptr)
            break;

        m_board[creature->getX()][creature->getY()] = creature;
        ++m_countCreatures;
    }
}

void Game::updateEnvironment()
{
    if (m_steps % 5 == 0)
        for (int i = 0; i < 15; ++i) {
            Creature* creature = getCreature(CreatureType::Plant);
            if (creature == nullptr)
                break;
            m_board[creature->getX()][creature->getY()] = creature;
            ++m_countCreatures;
        }

    if (countHunters() < 5) {
        for (int i = 0; i < 5; ++i) {
            Creature* creature = getCreature(CreatureType::Hunter, 1);
            if (creature == nullptr)
                break;
            else
                m_board[creature->getX()][creature->getY()] = creature;
            ++m_countCreatures;
        }
    }

    if (countPreys() < 3) {
        for (int i = 0; i < 2; ++i) {
            Creature* creature = getCreature(CreatureType::Prey, 1);
            if (creature == nullptr)
                break;
            else
                m_board[creature->getX()][creature->getY()] = creature;
            ++m_countCreatures;
        }
    }
}

void Game::lifeStep()
{
    ++m_steps;

    int dx, dy;
    for (int i = 0; i < m_Nrow; ++i) {
        for (int j = 0; j < m_Nrow; ++j) {
            Creature* creature = m_board[i][j];
            if (!creature)
                continue;
            creature->step();
            if (creature->isDead()) {
                m_board[i][j] = nullptr;
                --m_countCreatures;
                continue;
            }

            int speed = creature->getSpeed();
            if (speed == 1) {
                dx = rand() % 3 - 1;
                dy = rand() % 3 - 1;
            } else {
                dx = rand() % 5 - 2;
                dy = rand() % 5 - 2;
            }

            if (i + dx < 0 || i + dx >= m_Nrow)
                dx = 0;
            if (j + dy < 0 || j + dy >= m_Nrow)
                dy = 0;
            Creature* nextCell = m_board[i + dx][j + dy];
            int isChild;
            switch (creature->getType()) {
            case CreatureType::Plant:
                break;
            case CreatureType::Prey:
                isChild = rand() % 100 < 25 ? 1 : 0;
                if (nextCell == nullptr) {
                    m_board[i + dx][j + dy] = m_board[i][j];

                    if (isChild) {
                        Creature* child = getCreature(CreatureType::Prey);
                        if (child) {
                            m_board[i][j] = child;
                            ++m_countCreatures;
                        } else
                            m_board[i][j] = nullptr;
                    } else
                        m_board[i][j] = nullptr;
                } else {
                    if (nextCell
                        && nextCell->getType() == CreatureType::Plant) {
                        Prey* creature = (Prey*)m_board[i][j];
                        creature->eat();
                        --m_countCreatures;
                        m_board[i + dx][j + dy] = m_board[i][j];
                        if (isChild) {
                            Creature* child = getCreature(CreatureType::Prey);
                            if (child) {
                                child->setPosition(i, j);
                                m_board[i][j] = child;
                                ++m_countCreatures;
                                creature->giveBirth();
                            } else
                                m_board[i][j] = nullptr;
                        } else {
                            m_board[i][j] = nullptr;
                        }
                    }
                }
                break;
            case CreatureType::Hunter:
                if (nextCell == nullptr) {
                    m_board[i + dx][j + dy] = m_board[i][j];
                    m_board[i][j] = nullptr;
                } else {
                    if (nextCell && nextCell->getType() == CreatureType::Prey) {
                        Hunter* creature = (Hunter*)m_board[i][j];
                        creature->eat();
                        if (creature->getCountEaten() == 2)
                            isChild = rand() % 100 < 25 ? 1 : 0;
                        m_board[i + dx][j + dy] = nullptr;
                        --m_countCreatures;
                        m_board[i + dx][j + dy] = m_board[i][j];
                        if (isChild) {
                            Creature* child = getCreature(CreatureType::Hunter);
                            if (child != nullptr) {
                                child->setPosition(i, j);
                                m_board[i][j] = child;
                                ++m_countCreatures;
                                creature->giveBirth();
                            } else {
                                m_board[i][j] = nullptr;
                            }
                        } else {
                            m_board[i][j] = nullptr;
                        }
                    }
                }
                break;

            default:
                break;
            }
        }
    }

            // update in-class positions
        for (int i = 0; i < m_Nrow; ++i)
            for (int j = 0; j < m_Nrow; ++j)
                if (m_board[i][j] != nullptr)
                    m_board[i][j]->setPosition(i, j);

        updateEnvironment();

}

int Game::countHunters()
{
    int count = 0;
    for (int i = 0; i < m_Nrow; ++i)
        for (int j = 0; j < m_Nrow; ++j)
            if (m_board[i][j]
                && m_board[i][j]->getType() == CreatureType::Hunter)
                ++count;
    return count;
}

int Game::countPreys()
{
    int count = 0;
    for (int i = 0; i < m_Nrow; ++i)
        for (int j = 0; j < m_Nrow; ++j)
            if (m_board[i][j] && m_board[i][j]->getType() == CreatureType::Prey)
                ++count;
    return count;
}

void Game::run()
{
    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed
                || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                m_window.close();
            else if (
                    event.type == sf::Event::KeyPressed
                    && sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                lifeStep();
            }
        }

        //lifeStep();

        // update inside-class coordinates
        for (int i = 0; i < m_Nrow; ++i)
            for (int j = 0; j < m_Nrow; ++j)
                if (m_board[i][j] != nullptr)
                    m_board[i][j]->setPosition(i, j);

        m_window.clear(sf::Color::Black);

        for (int i = 0; i < m_Nrow; ++i) {
            for (int j = 0; j < m_Nrow; ++j) {
                Creature* creature = m_board[i][j];
                if (creature == nullptr)
                    continue;
                m_window.draw(createShape(m_board[i][j]));
            }
        }

        m_window.display();
    }
}
