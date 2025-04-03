#ifndef MOUTON_H
#define MOUTON_H

#include <Animal.h>

class Mouton : public Animal
{
    private:
        static int nbMouton;

    public:
        static const int obtenirNbMouton() {return nbMouton;};

        Mouton(Coordonnees, short, bool, short, short, short);
        virtual ~Mouton();

        Animal* clone(Coordonnees coord) const override {return new Mouton(coord, age % 2, 0, 0, 0, temps_reproduction);}

        void manger() override;
};

#endif // MOUTON_H
