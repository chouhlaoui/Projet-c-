#ifndef MONDE_H
#define MONDE_H

#include <string>
using namespace std;

#include "Sprite.h"

class Monde
{
    public:
        int n, m, nb_tour;
        Sprite*** tab;

        Monde(int , int);
        ~Monde();

        void afficher();
        void tourSuivant();

    private:
        void afficherNumeroColonne();
        void afficherInterLigne();
        void afficherLigne(int);
        string ajouterRemplissage(int , string);

};

#endif // MONDE_H
