#ifndef HERBE_H
#define HERBE_H

#include "Chose.h"

class Herbe : public Chose
{
    private:
        static int nbHerbe;

    public:
        static const int obtenirNbHerbe() {return nbHerbe;};

        Herbe(Coordonnees, short);
        ~Herbe();

        void tourSuivant() override;
};

#endif // HERBE_H
