#include "Hunter.hpp"

Hunter::Hunter(int x, int y) : LivingCreature(x, y)
{
    setColor(sf::Color::Red);
    setInitialHunger(70);
    setProb(0.2f);
}

CreatureType Hunter::getType()
{
    return CreatureType::Hunter;
}

const char* Hunter::getTypeName()
{
    return "Hunter";
}

int Hunter::getSpeed()
{
    if (m_hunger <= 5)
        return 2;
    return 1;
}
