#ifndef MONDE_H
#define MONDE_H

#include <string>
using namespace std;

#include <Sprite.h>

class Monde
{
    private:
        int nb_ligne, nb_colonne,nb_mouton, nb_loup, nb_tour;
        Sprite*** tab;

        int a, b, N;

    public:
        Monde(int , int, int , int);
        ~Monde();

        int nombreDeLignes();
        int nombreDeColonnes();
        int nombreMouton();
        int nombreLoup();
        int nombreTour();

        void ajouterSprite(Sprite*, int, int);
        void supprimmerSprite(Sprite*);
        void supprimmerSprite(int , int);

        void afficher();
        void tourSuivant();

    private:
        void PlacerAnimaux();
        void InitFonction();
        int fonctionModulaire(int coord);

        void afficherNumeroColonne();
        void afficherInterLigne();
        void afficherLigne(int);
        string ajouterRemplissage(int , string);

};

#endif // MONDE_H
