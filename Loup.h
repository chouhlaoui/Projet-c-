#ifndef LOUP_H
#define LOUP_H

#include "Animal.h"
#include "Monde.h"

class Loup : public Animal
{
    private:
        static int nbLoup;

    public:
        static const int obtenirNbLoup() {return nbLoup;};

        Loup(Coordonnees, bool, short, short, short, short);
        virtual ~Loup();

        Animal* clone(Coordonnees coord) const override { return new Loup(coord, age % 2, 0, 0, 0, temps_reproduction);}

        void manger() override;
        Mouton* rechercherMouton();
};
#endif // LOUP_H
