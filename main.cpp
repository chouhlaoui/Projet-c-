// pour compiler g++ -Wall -Wextra -g3 *.cpp -o output/main
// pour lancer cd output puis ./main

#include <iostream>
#include <limits>
#include <vector>
#include <tuple>
#include <thread>
#include <chrono>
using namespace std;

#include "Monde.h"
#include "Chose.h"
#include "Mouton.h"

#include "Constantes.h"
using namespace Constantes;

int demanderEntier(string message) {
    int valeur;

    while (true) {
        cout << message;
        cin >> valeur;

        if (cin.fail() || valeur <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Évite les caractères résiduels
            cout << "Entree invalide. Veuillez entrer un nombre entier positif.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valeur;
        }
    }
}


int main(int argc, char **argv)
{
	cout << "#####     Simulation d'ecosysteme     #####" << endl;

    int nb_ligne, nb_colonne, nb_mouton, nb_loup;

    nb_ligne = 10;//demanderEntier("Nombre de Ligne du monde : ");
    nb_colonne = 10;//demanderEntier("Nombre de Colonne du monde : ");
    nb_mouton = 60;//demanderEntier("Nombre de Mouton : ");
    nb_loup = 30;//demanderEntier("Nombre de Loup : ");

    while(nb_mouton+nb_loup > nb_ligne*nb_colonne)
    {
        cout << "Il y a trop d'animaux pour ce monde !!!" << endl;
        nb_mouton = demanderEntier("Nombre de Mouton : ");
        nb_loup = demanderEntier("Nombre de Loup : ");
    }

    Monde *monde = new Monde(nb_ligne, nb_colonne, nb_mouton, nb_loup);
    Chose::setMonde(monde);

    for (int i = 0; i < 100; i++){
        monde->tourSuivant();
        cout << *monde;
        if (monde->simulationFini()) break;
        this_thread::sleep_for(chrono::milliseconds(0));
    }
    cout << "Simulation finie apres " << monde->obtenirNbTour() << " tours";


	return 0;
}

