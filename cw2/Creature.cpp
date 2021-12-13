#include "Creature.hpp"

Creature::Creature(int x, int y)
	: m_idxX(x), m_idxY(y)
{
}

CreatureType Creature::getType() {
}

void Creature::setX(int newX) {
	m_idxX = newX;
}

int Creature::getX() {
	return m_idxX;
}

void Creature::setY(int newY) {
        m_idxY = newY;
}

int Creature::getY() {
	return m_idxY;
}

void Creature::setPosition(int newX, int newY) {
	m_idxX = newX;
	m_idxY = newY;
}

void Creature::setColor(sf::Color color) {
	m_color = color;
}

sf::Color Creature::getColor() {
	return m_color;
}
     
float Creature::getProb() {
	return m_probability;
}

void Creature::setProb(float prob) {
	m_probability = prob;       
}

void Creature::step() {
}


int Creature::isDead() {
	return 0;
}
        
int Creature::getSpeed() {
	return 1;
}

char* Creature::getTypeName() {
	return "???";
}


