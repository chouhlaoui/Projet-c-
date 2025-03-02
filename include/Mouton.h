#ifndef MOUTON_H
#define MOUTON_H

#include "Animal.h"

class Mouton : public Animal
{
    public:
        static int nbMouton;
        static int getNbMouton();
        
        Mouton();
        ~Mouton();

        void tourSuivant() override;
};

#endif // MOUTON_H
