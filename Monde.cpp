#include <Monde.h>
#include <Herbe.h>
#include <Mouton.h>
#include <Loup.h>

#include <iostream>
using namespace std;

Monde::Monde(int n, int m, int mouton, int loup) : nb_ligne(n), nb_colonne(m), nb_mouton(mouton), nb_loup(loup)
{
    nb_tour = 0;

    tab = new Sprite**[n];
    for (int i = 0; i < n; i++) {
        tab[i] = new Sprite*[m];

        for (int j = 0; j < m; j++) {
            tab[i][j] = new Herbe();
        }
    }

    PlacerAnimaux();
}

void Monde::PlacerAnimaux()
{
    InitFonction();

    int coord;
    for(int i=0; i<nb_mouton; i++)
    {
        coord = Monde::fonctionModulaire(i);
        Monde::ajouterSprite(new Mouton(), coord/nb_ligne, coord%nb_ligne);
    }

    for(int i=0; i<nb_loup; i++)
    {
        coord = Monde::fonctionModulaire(nb_mouton + i);
        Monde::ajouterSprite(new Loup(), coord/nb_ligne, coord%nb_ligne);
    }
}

void Monde::InitFonction()
{
    int nb_premiers[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

    N = nb_ligne*nb_colonne;

    int index_nb;
    for(int i=0; nb_premiers[i]<N/2; i++) index_nb++;

    for (int i=index_nb; i>0; i--)
    {
        if(!(N % nb_premiers[i] == 0))
        {
            a = nb_premiers[i];
            b = N/3;
            return;
        }
    }
    cout << "Erreur : trop de case / pas assez de nombres premiers !!!!";
}

int Monde::fonctionModulaire(int coord)
{
    return (a*coord + b) % N;
}

Monde::~Monde()
{
    for (int i = 0; i < nb_ligne; i++) {

        for (int j = 0; j < nb_colonne; j++) {
            delete tab[i][j];
        }
        delete[] tab[i];
    }
    delete[] tab;
}

int Monde::nombreDeLignes()
{
    return nb_ligne;
}
int Monde::nombreDeColonnes()
{
    return nb_colonne;
}
int Monde::nombreMouton()
{
    return nb_mouton;
}
int Monde::nombreLoup()
{
    return nb_loup;
}
int Monde::nombreTour()
{
    return nb_tour;
}

void Monde::ajouterSprite(Sprite *sprite, int x, int y)
{
    Monde::supprimmerSprite(x, y);
    if(!tab[x][y])
    {
        tab[x][y] = sprite;
    }
}
void Monde::supprimmerSprite(Sprite *sprite)
{
    for (int i = 0; i < nb_ligne; i++)
    {
        for (int j = 0; j < nb_colonne; j++)
        {

            if(tab[i][j] == sprite)
            {
                delete tab[i][j];
                tab[i][j] = nullptr;
            }

        }
    }
}
void Monde::supprimmerSprite(int x, int y)
{
    if(tab[x][y])
    {
        delete tab[x][y];
        tab[x][y] = nullptr;
    }
}



void Monde::afficher()
{
    Monde::afficherNumeroColonne();
    Monde::afficherInterLigne();

    for(int ligne=0; ligne<nb_ligne; ligne++)
    {
        Monde::afficherLigne(ligne);
        Monde::afficherInterLigne();
    }

    cout << endl << "Tour : " << nb_tour << endl << endl;
}

void Monde::afficherNumeroColonne()
{
    cout << endl << "   ";
    for(int colonne=1; colonne<=nb_colonne; colonne++)
    {
        cout << Monde::ajouterRemplissage(5, to_string(colonne));
    }
}

void Monde::afficherInterLigne()
{
    cout << endl << "   ";
    for(int colonne=1; colonne<=nb_colonne; colonne++)
    {
        cout << "+---+";
    }
}

void Monde::afficherLigne(int ligne)
{
    cout << endl << Monde::ajouterRemplissage(3, to_string(ligne+1));
    for(int colonne=0; colonne<nb_colonne; colonne++)
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

    for(int ligne=0; ligne<nb_ligne; ligne++)
    {
        for(int colonne=0; colonne<nb_colonne; colonne++)
        {
            if(tab[ligne][colonne])
            {
                tab[ligne][colonne]->tourSuivant();
            }
        }
    }
}
