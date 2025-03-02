#ifndef MONDE_H
#define MONDE_H

#include <iostream>
#include <string>
using namespace std;

#include "Sprite.h"

class Monde
{
    private:
        int nb_ligne, nb_colonne,nb_mouton, nb_loup, nb_tour;
        Sprite**** tab;

        int* tableau_coordonees;

    public:
        Monde(int , int, int , int);
        ~Monde();

        int nombreDeLignes();
        int nombreDeColonnes();
        int nombreMouton();
        int nombreLoup();
        int nombreTour();
        Sprite**** tableau();

        void ajouterSprite(Sprite*, int, int, int);
        void supprimmerSprite(Sprite*);
        void supprimmerSprite(int , int, int);

        friend ostream& operator<<(ostream&, const Monde&);// Affichage
        void tourSuivant();

    private:
        void PlacerAnimaux();
        void InitTableauCoordonnees();

        void afficherNumeroColonne(ostream&) const;
        void afficherInterLigne(ostream&) const;
        void afficherLigne(ostream&, int) const;
        string ajouterRemplissage(int , string) const;

};

#endif // MONDE_H
