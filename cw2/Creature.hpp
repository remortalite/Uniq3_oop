#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <SFML/Graphics.hpp>

enum class CreatureType { Hunter, Prey, Plant };

class Creature {
    int m_idxX;
    int m_idxY;

    sf::Color m_color;

    float m_probability;

    char* m_name;

public:
    Creature(int, int);

    virtual CreatureType getType() = 0;

    void setX(int);
    int getX();

    void setY(int);
    int getY();

    void setPosition(int, int);

    void setColor(sf::Color);
    virtual sf::Color getColor();

    void setProb(float);
    virtual float getProb();

    virtual void step();

    virtual int isDead();

    int getSpeed();

    virtual const char* getTypeName();
};

#endif // #ifndef CREATURE_HPP
