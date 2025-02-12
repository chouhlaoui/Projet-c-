#include "Monde.h"

#include <iostream>
using namespace std;

Monde::Monde(int n, int m) : n(n), m(m) {}

Monde::~Monde()
{

}

void Monde::afficher()
{
    Monde::afficherNumeroColonne();
    Monde::afficherInterLigne();

    for(int ligne=1; ligne<=n; ligne++)
    {
        Monde::afficherLigne(ligne);
        Monde::afficherInterLigne();
    }

    cout << endl;
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
    cout << endl << Monde::ajouterRemplissage(3, to_string(ligne));
    for(int colonne=1; colonne<=m; colonne++)
    {
        cout << "|   |";
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
