#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

#include "Monde.h"
#include "Mouton.h"
#include "Loup.h"
#include "Herbe.h"
#include "Sels_Mineraux.h"

#include "Constantes.h"
using namespace Constantes;

Monde::Monde(int n, int m, int mouton, int loup) : nb_ligne(n), nb_colonne(m), nb_mouton_initial(mouton), nb_loup_initial(loup)
{
    nb_tour = 0;

    tableau3D = new Chose***[n];
    for (int x = 0; x < n; x++) {
        tableau3D[x] = new Chose**[m];

        for (int y = 0; y < m; y++) {
            tableau3D[x][y] = new Chose*[HAUTEUR];

            tableau3D[x][y][0] = new Herbe(make_tuple(x, y, 0));// Herbe en bas/au sol
            for (int z = 1; z < HAUTEUR; z++) {
                tableau3D[x][y][z] = nullptr;
            }
        }
    }

    placerAnimaux();
}

void Monde::placerAnimaux()
{
    vector<int> tableau_coordonnees = initialiserTableauCoordonnees();

    int index;
    Mouton *mouton;
    for(int i=0; i<nb_mouton_initial; i++)
    {
        index = tableau_coordonnees[i];
        mouton = new Mouton({index / nb_colonne, index % nb_colonne, 1},
                            genererNbAleatoire(i) % max(1, DUREE_VIE_MOUTON / 2),
                            genererNbAleatoire(i) % 2,
                            genererNbAleatoire(i) % max(1, TOURS_SANS_MANGER_MOUTON / 2),
                            genererNbAleatoire(i) % max(1, RYTHME_REPRODUCTION_MOUTON / 2),
                            TEMPS_REPRODUCTION_MOUTON+1);
        ajouterChose(mouton);
    }

    Loup *loup;
    for(int i=0; i<nb_loup_initial; i++)
    {
        index = tableau_coordonnees[nb_mouton_initial + i];
        loup = new Loup({index/nb_colonne, index%nb_colonne, 1},
                        genererNbAleatoire(i) % max(1, DUREE_VIE_LOUP/2),
                        genererNbAleatoire(i) % 2,
                        genererNbAleatoire(i) % max(1, TOURS_SANS_MANGER_LOUP/2),
                        genererNbAleatoire(i) % max(1, RYTHME_REPRODUCTION_LOUP/2),
                        TEMPS_REPRODUCTION_LOUP+1);
        ajouterChose(loup);
    }
}

vector<int> Monde::initialiserTableauCoordonnees() {
    int index;
    int length = nb_ligne * nb_colonne;
    int nb_aleatoire = genererNbAleatoire(nb_mouton_initial + nb_loup_initial);

    vector<int> tableau_coordonnees(length);
    for (int i = 0; i < length; i++) {
        tableau_coordonnees[i] = i;
    }

    // Mélange de Fisher-Yates
    for (int i = 0; i < length - 2; i++) {
        nb_aleatoire = genererNbAleatoire(nb_aleatoire);
        index = i + (nb_aleatoire % (length - i));

        swap(tableau_coordonnees[i], tableau_coordonnees[index]);
    }

    return tableau_coordonnees;
}


long long Monde::genererNbAleatoire(long long nb)
{
    return ((long long) a * nb) % N;
}

Monde::~Monde()
{
    for (int x = 0; x < nb_ligne; x++) {
        for (int y = 0; y < nb_colonne; y++) {
            for (int z = 0; z < HAUTEUR; z++) {
                delete tableau3D[x][y][z];  // Supprime chaque Chose*
            }
            delete[] tableau3D[x][y];  // Supprime chaque ligne
        }
        delete[] tableau3D[x];  // Supprime chaque colonne
    }
    delete[] tableau3D;  // Supprime le tableau principal
}



ostream& operator<<(ostream& os, const Monde& monde)
{
    monde.afficherNumeroColonne(os);
    monde.afficherInterLigne(os);

    for (int ligne = 0; ligne < monde.nb_ligne; ligne++) {
        monde.afficherLigne(os, ligne);
        monde.afficherInterLigne(os);
    }

    os << endl << "Tour : " << monde.nb_tour;
    os << " | " << "Mouton : " << Mouton::obtenirNbMouton() << " | " << "Loup : " << Loup::obtenirNbLoup();
    os << " | " << "Herbe : " << Herbe::obtenirNbHerbe() << " | " << "Sels : " << Sels_Mineraux::obtenirNbSels() << endl << endl;

    monde.afficherLogs(os);

    return os;
}

void Monde::afficherNumeroColonne(ostream& os) const
{
    os << endl << "   ";
    for (int colonne = 1; colonne <= nb_colonne; colonne++) {
        os << ajouterRemplissage(5, to_string(colonne));
    }
}

void Monde::afficherInterLigne(ostream& os) const
{
    os << endl << "   ";
    for (int colonne = 1; colonne <= nb_colonne; colonne++) {
        os << "+---+";
    }
}

void Monde::afficherLigne(ostream& os, int ligne) const
{
    os << endl << ajouterRemplissage(3, to_string(ligne + 1));
    for (int colonne = 0; colonne < nb_colonne; colonne++)
    {
        Chose* chose = nullptr;

        for (int hauteur = HAUTEUR-1; hauteur >= 0; hauteur--) {
            if (tableau3D[ligne][colonne][hauteur]) {
                chose = tableau3D[ligne][colonne][hauteur];
                break;
            }
        }

        if (chose) {
            os << "| " << *chose << " |";
        } else {
            os << "|   |";
        }
    }
}


string Monde::ajouterRemplissage(int taille_Remplissage, string chaine) const
{
    int longueur = chaine.length();

    int remplissage = taille_Remplissage - longueur;
    int remplissage_gauche = remplissage / 2;
    int remplissage_droite = remplissage - remplissage_gauche;

    chaine = string(remplissage_gauche, ' ') + chaine + string(remplissage_droite, ' ');

    return chaine;
}

void Monde::afficherLogs(ostream& os) const
{
    for(string log : Chose::logs)
    {
        os << log << endl;
    }
}



void Monde::tourSuivant()
{
    Chose::logs.clear();
    nb_tour++;
    reinitialiserAction();

    for(int ligne=0; ligne<nb_ligne; ligne++)
    {
        for(int colonne=0; colonne<nb_colonne; colonne++)
        {
            for(int hauteur=0; hauteur<HAUTEUR; hauteur++)
            {
                if(tableau3D[ligne][colonne][hauteur])
                {
                    if (!tableau3D[ligne][colonne][hauteur]->aJouerCeTour())
                    {
                        tableau3D[ligne][colonne][hauteur]->tourSuivant();
                    }
                }
            }
        }
    }
}

void Monde::reinitialiserAction()
{
    for(int ligne=0; ligne<nb_ligne; ligne++)
    {
        for(int colonne=0; colonne<nb_colonne; colonne++)
        {
            for(int hauteur=0; hauteur<HAUTEUR; hauteur++)
            {
                if(tableau3D[ligne][colonne][hauteur])
                {
                    tableau3D[ligne][colonne][hauteur]->reinitialiserAction();
                }
            }
        }
    }
}



Chose* Monde::obtenirChose(Coordonnees coordonnees)
{
    int x, y, z; tie(x, y, z) = coordonnees;
    return tableau3D[x][y][z];
}

void Monde::ajouterChose(Chose* chose)
{
    int x, y, z; tie(x, y, z) = chose->obtenirCoordonnees();
    tableau3D[x][y][z] = chose;
}

void Monde::supprimmerChose(Chose* chose)
{
    if (!chose) return;

    int x, y, z;
    tie(x, y, z) = chose->obtenirCoordonnees();

    if (tableau3D[x][y][z] == chose) {
        delete tableau3D[x][y][z];
        tableau3D[x][y][z] = nullptr;
    }
}

void Monde::deplacerChose(Chose* chose, Coordonnees coordonnees)
{
    int x, y, z; tie(x, y, z) = chose->obtenirCoordonnees();
    tableau3D[x][y][z] = nullptr;

    tie(x, y, z) = coordonnees;
    tableau3D[x][y][z] = chose;
    chose->changeCoordonnees(coordonnees);

}

vector<Coordonnees> Monde::caseAccessibles(Coordonnees coordonnees, short rayon)
{
    vector<Coordonnees> casesLibres;
    int x, y, z; tie(x, y, z) = coordonnees;
    casesLibres.push_back(coordonnees);

    for (int dx = -rayon; dx <= rayon; dx++) {
        for (int dy = -rayon; dy <= rayon; dy++) {
            Coordonnees nouvelleCase = {x + dx, y + dy, z};
            if (CaseValide(nouvelleCase) && CaseVide(nouvelleCase))
            {
                casesLibres.push_back(nouvelleCase);
            }
        }
    }

    return casesLibres;
}

vector<Coordonnees> Monde::casesAdjacentes(Coordonnees coordonnees)
{
    vector<Coordonnees> caseAdjacentes;
    int x, y, z; tie(x, y, z) = coordonnees;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            Coordonnees nouvelleCase = {x + dx, y + dy, z};
            if (CaseValide(nouvelleCase))
            {
                caseAdjacentes.push_back(nouvelleCase);
            }
        }
    }

    return caseAdjacentes;
}

bool Monde::CaseValide(Coordonnees coordonnees)
{
    int x, y, z; tie(x, y, z) = coordonnees;
    return x>=0 && y>=0 && z>=0 && x<nb_ligne && y<nb_colonne && z<HAUTEUR;
}

bool Monde::CaseVide(Coordonnees coordonnees)
{
    int x, y, z; tie(x, y, z) = coordonnees;
    return !tableau3D[x][y][z];
}

int Monde::compterTypeAdjacents(char type, Coordonnees coordonnees, short rayon, short hauteur)
{
    int cpt = 0, x, y, z; tie(x, y, z) = coordonnees;
    for(int i=x-rayon; i<=x+rayon; i++)
    {
        for(int j=y-rayon; j<=y+rayon; j++)
        {
            for(int k=z-hauteur; k<=z+hauteur; k++)
            {
                Coordonnees coord = {i, j, k};
                if(CaseValide(coord) && obtenirChose(coord))
                {
                    if(obtenirChose(coord)->estdeType(type)) cpt++;
                }
            }
        }
    }
    return cpt;
}
