#ifndef MONDE_H
#define MONDE_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "Chose.h"
#include "Mouton.h"
#include "Loup.h"

#include "Constantes.h"
using namespace Constantes;

class Monde
{
    private:
        int nb_ligne, nb_colonne, nb_mouton_initial, nb_loup_initial, nb_tour;
        Chose**** tableau3D;

    public:
        Monde(int, int, int, int);
        virtual ~Monde();

        int obtenirNbTour() {return nb_tour;}

        friend ostream& operator<<(ostream&, const Monde&);// Affichage

        void tourSuivant();
        void reinitialiserAction();

    private:
        void placerAnimaux();
        vector<int> initialiserTableauCoordonnees();
        long long genererNbAleatoire(long long);

        void afficherNumeroColonne(ostream&) const;
        void afficherInterLigne(ostream&) const;
        void afficherLigne(ostream&, int) const;
        void afficherLogs(ostream&) const;
        string ajouterRemplissage(int , string) const;

    public:
        bool simulationFini() {return !(Loup::obtenirNbLoup() > 0 && Mouton::obtenirNbMouton() > 0);}

        Chose* obtenirChose(Coordonnees);
        void ajouterChose(Chose*);
        void supprimmerChose(Chose*);
        void deplacerChose(Chose*, Coordonnees);

        vector<Coordonnees> caseAccessibles(Coordonnees coordonnees, short=1);
        vector<Coordonnees> casesAdjacentes(Coordonnees coordonnees);
        bool CaseValide(Coordonnees);
        bool CaseVide(Coordonnees);

        int compterTypeAdjacents(char, Coordonnees, short=1, short=1);
};

#endif // MONDE_H
