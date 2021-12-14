#include "LivingCreature.hpp"

LivingCreature::LivingCreature(int x, int y) : Creature(x, y)
{
}

void LivingCreature::step()
{
    Creature::step();
    m_hunger += m_hungerStep;
    sf::Color color = getColor();
    if (color.a - delta >= delta)
        setColor(sf::Color(color.r, color.g, color.b, color.a - delta));
};

int LivingCreature::isDead()
{
    if (m_hunger <= 0)
        return 1;
    return 0;
}

void LivingCreature::eat()
{
    m_hunger += m_eatStep;
    ++m_eaten;

    sf::Color color = getColor();
    if (color.a + delta >= 254)
        setColor(sf::Color(color.r, color.g, color.b, color.a + delta));
}

void LivingCreature::giveBirth()
{
    m_hunger += m_gaveBirthStep;
}

int LivingCreature::getCountEaten()
{
    return m_eaten;
}

void LivingCreature::setInitialHunger(int hunger)
{
    m_hunger = hunger;
}
