#include "Creature.hpp"
#include "Plant.hpp"

Plant::Plant(int x, int y)
	: Creature(x, y)
{
	setColor(sf::Color::Green);
	setProb(0.6f);
}

CreatureType Plant::getType() {
	return CreatureType::Plant;
}

char* Plant::getTypeName() {
	return "Plant";
}

int Plant::getLifetime() {
      	return m_lifetime;      
}

void Plant::step()
{
	Creature::step();
	--m_lifetime;
}

int Plant::isDead() {
	if (m_lifetime <= 0)
		return 1;
	return 0;
}

int Plant::getSpeed() {
	return 0;
}



