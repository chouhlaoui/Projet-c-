#ifndef LOUP_H
#define LOUP_H

#include "Animal.h"

class Loup : public Animal
{
    public:
        Loup();

        void tourSuivant() override;
};

#endif // LOUP_H
