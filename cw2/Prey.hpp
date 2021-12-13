#ifndef PREY_HPP
#define PREY_HPP

#include "LivingCreature.hpp"

class Prey : public LivingCreature {
public:
    Prey(int x, int y);

    virtual CreatureType getType();

    virtual const char* getTypeName();

    virtual int getSpeed(); //-> 1
};

#endif // #ifndef PREY_HPP
