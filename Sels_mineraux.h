#ifndef SELS_MINERAUX_H
#define SELS_MINERAUX_H

#include <Chose.h>

class Sels_Mineraux : public Chose
{
    private:
        static int nbSels;

    public:
        static const int obtenirNbSels() {return nbSels;};

        Sels_Mineraux(Coordonnees);
        virtual ~Sels_Mineraux();

        void tourSuivant() override;
};

#endif // SELS_MINERAUX_H
