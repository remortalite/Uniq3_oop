#ifndef LIVINGCREATURE_HPP
#define LIVINGCREATURE_HPP

#include "Creature.hpp"

#include <SFML/Graphics.hpp>

class LivingCreature : public Creature
{

public:

        int m_hunger = 15;
        int m_eaten = 0;
        const int m_hungerStep = -2;
        const int m_gaveBirthStep = -4;
        const int m_eatStep = 2;

        uint8_t delta = 20;

        LivingCreature(int x, int y);

	void step();

	virtual int isDead();

	void eat();

	void giveBirth();

	int getCountEaten();

};


#endif // #ifndef LIVINGCREATURE_HPP	
