#ifndef MOUTON_H
#define MOUTON_H

#include "Animal.h"

class Mouton : public Animal
{
    public:
        Mouton();

        void tourSuivant() override;
};

#endif // MOUTON_H
