#ifndef LIVINGCREATURE_HPP
#define LIVINGCREATURE_HPP

#include "Creature.hpp"

#include <SFML/Graphics.hpp>

class LivingCreature : public Creature {
public:
    int m_hunger = 11;
    int m_eaten = 0;
    const int m_hungerStep = -2;
    const int m_gaveBirthStep = -4;
    const int m_eatStep = 4;

    uint8_t delta = 10;

    LivingCreature(int x, int y);

    void step();

    virtual int isDead();

    void eat();

    void giveBirth();

    int getCountEaten();

    void setInitialHunger(int);
};

#endif // #ifndef LIVINGCREATURE_HPP
