#ifndef PLANT_HPP
#define PLANT_HPP

#include "Creature.hpp"

#include <SFML/Graphics.hpp>

class Plant : public Creature {

	int m_lifetime = 6;

public:

	Plant(int, int);

	virtual CreatureType getType();

	virtual char* getTypeName();

	int getLifetime();

	virtual void step();

	virtual int isDead();

	virtual int getSpeed(); // -> 0

};

#endif // #ifndef PLANT_HPP	
