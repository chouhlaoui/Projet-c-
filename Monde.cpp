#include "Monde.h"

#include <iostream>
using namespace std;

Monde::Monde(int n, int m) : n(n), m(m)
{
    nb_tour = 0;

    tab = new Sprite**[n];
    for (int i = 0; i < n; i++) {
        tab[i] = new Sprite*[m];

        for (int j = 0; j < m; j++) {
            tab[i][j] = nullptr;
        }
    }
}

Monde::~Monde()
{
    for (int i = 0; i < n; i++) {

        for (int j = 0; j < m; j++) {
            delete tab[i][j];
        }
        delete[] tab[i];
    }
    delete[] tab;
}

void Monde::afficher()
{
    Monde::afficherNumeroColonne();
    Monde::afficherInterLigne();

    for(int ligne=0; ligne<n; ligne++)
    {
        Monde::afficherLigne(ligne);
        Monde::afficherInterLigne();
    }

    cout << endl << "Tour : " << nb_tour << endl << endl;
}

void Monde::afficherNumeroColonne()
{
    cout << endl << "   ";
    for(int colonne=1; colonne<=m; colonne++)
    {
        cout << Monde::ajouterRemplissage(5, to_string(colonne));
    }
}

void Monde::afficherInterLigne()
{
    cout << endl << "   ";
    for(int colonne=1; colonne<=m; colonne++)
    {
        cout << "+---+";
    }
}

void Monde::afficherLigne(int ligne)
{
    cout << endl << Monde::ajouterRemplissage(3, to_string(ligne+1));
    for(int colonne=0; colonne<m; colonne++)
    {
        if(tab[ligne][colonne])
        {
            cout << "| " << tab[ligne][colonne]->getSymbole() << " |";
        }
        else
        {
            cout << "|   |";
        }

    }
}

string Monde::ajouterRemplissage(int taille_Remplissage, string chaine)
{
    int longueur = chaine.length();

    int remplissage = taille_Remplissage - longueur;
    int remplissage_gauche = remplissage / 2;
    int remplissage_droite = remplissage - remplissage_gauche;

    chaine = string(remplissage_gauche, ' ') + chaine + string(remplissage_droite, ' ');

    return chaine;
}


void Monde::tourSuivant()
{
    nb_tour++;

    for(int ligne=0; ligne<n; ligne++)
    {
        for(int colonne=0; colonne<n; colonne++)
        {
            if(tab[ligne][colonne])
            {
                tab[ligne][colonne]->tourSuivant();
            }
        }
    }
}
