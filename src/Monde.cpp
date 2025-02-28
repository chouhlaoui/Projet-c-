#include <Monde.h>
#include <Herbe.h>
#include <Mouton.h>
#include <Loup.h>

#include <iostream>
using namespace std;

Monde::Monde(int n, int m, int mouton, int loup) : nb_ligne(n), nb_colonne(m), nb_mouton(mouton), nb_loup(loup)
{
    nb_tour = 0;

    tab = new Sprite***[n];
    for (int x = 0; x < n; x++) {
        tab[x] = new Sprite**[m];

        for (int y = 0; y < m; y++) {
            tab[x][y] = new Sprite*[2];

            tab[x][y][0] = new Herbe();// Herbe en bas/au sol
            for (int z = 1; z < 2; z++) {
                tab[x][y][z] = nullptr;
            }
        }
    }

    PlacerAnimaux();
}

void Monde::PlacerAnimaux()
{
    Monde::InitTableauCoordonnees();

    int coord;
    for(int i=0; i<nb_mouton; i++)
    {
        coord = tableau_coordonees[i];
        Monde::ajouterSprite(new Mouton(), coord/nb_colonne, coord%nb_colonne, 1);
    }

    for(int i=0; i<nb_loup; i++)
    {
        coord = tableau_coordonees[nb_mouton + i];
        Monde::ajouterSprite(new Loup(), coord/nb_colonne, coord%nb_colonne, 1);
    }
}

void Monde::InitTableauCoordonnees()
{
    int buffer, length = nb_ligne*nb_colonne, random_index, random_number = ((long long) 48271 * (nb_mouton + nb_loup)) % 2147483647;

    tableau_coordonees = new int[length];
    for(int i=0; i<length; i++) tableau_coordonees[i] = i;

    for(int i=0; i<length-2; i++)
    {
        random_number = ((long long) 48271 * random_number) % 2147483647;
        random_index = i+(random_number%(length-i));

        buffer = tableau_coordonees[i];
        tableau_coordonees[i] = tableau_coordonees[random_index];
        tableau_coordonees[random_index] = buffer;
    }


}


Monde::~Monde()
{
    for (int x = 0; x < nb_ligne; x++) {
        for (int y = 0; y < nb_colonne; y++) {
            for (int z = 0; z < 2; z++) {
                delete tab[x][y][z];  // Supprime chaque Sprite*
            }
            delete[] tab[x][y];  // Supprime chaque ligne Z
        }
        delete[] tab[x];  // Supprime chaque colonne Y
    }
    delete[] tab;  // Supprime le tableau principal

    delete[] tableau_coordonees;
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

void Monde::ajouterSprite(Sprite *sprite, int x, int y, int z)
{
    Monde::supprimmerSprite(x, y, z);
    tab[x][y][z] = sprite;
}
void Monde::supprimmerSprite(Sprite *sprite)
{
    for (int i=0; i<nb_ligne; i++)
    {
        for (int j=0; j<nb_colonne; j++)
        {
            for(int k=0; k<2; k++)
            {
                if(tab[i][j][k] == sprite)
                {
                    delete tab[i][j][k];
                    tab[i][j][k] = nullptr;
                }
            }
        }
    }
}
void Monde::supprimmerSprite(int x, int y, int z)
{
    if(tab[x][y][z])
    {
        delete tab[x][y][z];
        tab[x][y][z] = nullptr;
    }
}



ostream& operator<<(ostream& os, const Monde& monde)
{
    monde.afficherNumeroColonne(os);
    monde.afficherInterLigne(os);

    for (int ligne = 0; ligne < monde.nb_ligne; ligne++) {
        monde.afficherLigne(os, ligne);
        monde.afficherInterLigne(os);
    }

    os << endl << "Tour : " << monde.nb_tour << endl << endl;
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
        Sprite* sprite = nullptr;

        for (int hauteur = 1; hauteur >= 0; hauteur--) {
            if (tab[ligne][colonne][hauteur]) {
                sprite = tab[ligne][colonne][hauteur];
                break;
            }
        }

        if (sprite) {
            os << "| " << *sprite << " |";
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



void Monde::tourSuivant()
{
    nb_tour++;

    for(int ligne=0; ligne<nb_ligne; ligne++)
    {
        for(int colonne=0; colonne<nb_colonne; colonne++)
        {
            for(int hauteur=0; hauteur<2; hauteur++)
            {
                if(tab[ligne][colonne][hauteur])
                {
                    tab[ligne][colonne][hauteur]->tourSuivant();
                }
            }
        }
    }
}
