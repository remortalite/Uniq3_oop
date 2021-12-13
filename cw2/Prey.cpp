#include "Prey.hpp"
#include "LivingCreature.hpp"

Prey::Prey(int x, int y) : LivingCreature(x, y)
{
    setColor(sf::Color::Yellow);
    setProb(0.4f);
}

CreatureType Prey::getType()
{
    return CreatureType::Prey;
}

const char* Prey::getTypeName()
{
    return "Prey";
}

int Prey::getSpeed()
{
    return 1;
}
