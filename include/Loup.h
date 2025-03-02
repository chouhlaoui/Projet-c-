#ifndef LOUP_H
#define LOUP_H

#include "Animal.h"

class Loup : public Animal
{
    public:
        static int nbLoup;
        static int getNbLoup();
        
        Loup();
        ~Loup();

        void tourSuivant() override;
};

#endif // LOUP_H
