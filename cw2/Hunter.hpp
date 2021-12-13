#ifndef HUNTER_HPP
#define HUNTER_HPP

#include "LivingCreature.hpp"

class Hunter : public LivingCreature {
public:
    Hunter(int x, int y);

    virtual CreatureType getType();

    virtual const char* getTypeName();

    virtual int getSpeed(); //-> 1 or 2
};

#endif // #ifndef HUNTER_HPP
