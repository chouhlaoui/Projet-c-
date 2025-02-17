// pour compiler g++ -Wall -Wextra -g3 *.cpp -o output/main
// pour lancer cd output puis ./main

#include <iostream>
#include <limits>
using namespace std;

#include "Monde.h"
#include "Sprite.h"
#include "Sels_mineraux.h"
#include "Herbe.h"
#include "Animal.h"
#include "Mouton.h"
#include "Loup.h"

int demanderEntier(string message) {
    int valeur;

    while (true) {
        std::cout << message;
        std::cin >> valeur;

        if (std::cin.fail() || valeur <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Évite les caractères résiduels
            std::cout << "Entree invalide. Veuillez entrer un nombre entier positif.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valeur;
        }
    }
}



int main(int argc, char **argv)
{
	cout << "#####     Simulation d'ecosysteme     #####" << endl;

    int nb_ligne, nb_colonne, nb_mouton, nb_loup;
    char continuer;

    nb_ligne = 10;//demanderEntier("Nombre de Ligne du monde : ");
    nb_colonne = 10;//demanderEntier("Nombre de Colonne du monde : ");
    nb_mouton = 10;//demanderEntier("Nombre de Mouton : ");
    nb_loup = 10;//demanderEntier("Nombre de Loup : ");

    while(nb_mouton+nb_loup > nb_ligne*nb_colonne)
    {
        cout << "Il y a trop d'animaux pour ce monde !!!" << endl;
        nb_mouton = demanderEntier("Nombre de Mouton : ");
        nb_loup = demanderEntier("Nombre de Loup : ");
    }

    Monde monde(nb_ligne, nb_colonne, nb_mouton, nb_loup);

    do
    {
        monde.afficher();
        monde.tourSuivant();

        cout << "Voulez-vous continuer ? (o/n) : ";
        cin >> continuer;
    } while (continuer == 'o' || continuer=='O');

	return 0;
}
