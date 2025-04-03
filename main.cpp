// pour compiler g++ -Wall -Wextra -g3 *.cpp -o output/main
// pour lancer cd output puis ./main

#include <iostream>
#include <fstream>
#include <limits>
#include <thread>
#include <chrono>
using namespace std;

#include "Monde.h"
#include "Chose.h"
#include "Herbe.h"
#include "Mouton.h"
#include "Loup.h"

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

void chercherMeilleureRatio(int nb_ligne, int nb_colonne)
{
    int meilleur_tour=0, tour;
    ofstream fichier;
    string nom = to_string(nb_ligne) + "_" + to_string(nb_colonne) + ".csv";
    fichier.open (nom);

    vector<double> ratios = {1.0, 2.0, 5.0, 10.0};  // Moutons par loup

    for (double ratio : ratios) {
        for (int loup = 2; loup < nb_ligne * nb_colonne / (1 + ratio); loup++) {
            int mouton = static_cast<int>(loup * ratio);

            if (mouton + loup > (nb_ligne * nb_colonne)) continue;

            Monde* monde = new Monde(nb_ligne, nb_colonne, mouton, loup);
            Chose::setMonde(monde);
            tour = monde->finirSimulation();
            delete monde;

            fichier << mouton << "," << loup << "," << tour << endl;

            if (tour >= meilleur_tour) {
                meilleur_tour = tour;
                cout << "\r Nouveau record ! "
                     << "Taille: " << nb_colonne << "x" << nb_ligne
                     << " |  Moutons: " << mouton
                     << " |  Loups: " << loup
                     << " -> " << tour << " cycles" << endl;
            }

            cout << "\r Taille: " << nb_colonne << "x" << nb_ligne
                 << " |  Moutons: " << mouton
                 << " |  Loups: " << loup
                 << " -> " << tour << " cycles" << std::flush;
        }
    }

    cout << endl << "Regarder dans " << nom << endl;
    fichier.close();
}

void enregistrerStats(int nb_ligne, int nb_colonne, int nb_mouton, int nb_loup)
{
    ofstream fichier;
    string nom = "Stats" + to_string(nb_ligne) + "_" + to_string(nb_colonne) + "_" + to_string(nb_mouton) + "_" + to_string(nb_loup) + ".csv";
    fichier.open (nom);

    Monde *monde = new Monde(nb_ligne, nb_colonne, nb_mouton, nb_loup);
    Chose::setMonde(monde);

    for (int i = 0; i < 1000; i++){
        cout << "\r " << i << " cycles |  Moutons: " << Mouton::obtenirNbMouton() << " |  Loups: " << Loup::obtenirNbLoup() << std::flush;
        fichier << Herbe::obtenirNbHerbe() << "," << Mouton::obtenirNbMouton() << "," << Loup::obtenirNbLoup() << endl;

        monde->tourSuivant();
        if (monde->simulationFini()) break;
    }
    cout << endl << "Simulation finie apres " << monde->obtenirNbTour() << " tours" << endl;
    cout << endl << "Regarder dans " << nom << endl;
    fichier.close();
}


int main(int argc, char **argv)
{
	cout << "#####     Simulation d'ecosysteme     #####" << endl;

    int nb_ligne, nb_colonne, nb_mouton, nb_loup;

    nb_ligne = demanderEntier("Nombre de Ligne du monde : ");
    nb_colonne = demanderEntier("Nombre de Colonne du monde : ");
    nb_mouton = demanderEntier("Nombre de Mouton : ");
    nb_loup = demanderEntier("Nombre de Loup : ");

    while(nb_mouton+nb_loup > nb_ligne*nb_colonne)
    {
        cout << "Il y a trop d'animaux pour ce monde !!!" << endl;
        nb_mouton = demanderEntier("Nombre de Mouton : ");
        nb_loup = demanderEntier("Nombre de Loup : ");
    }

    Monde *monde = new Monde(nb_ligne, nb_colonne, nb_mouton, nb_loup);
    Chose::setMonde(monde);

    for (int i = 0; i < 1000; i++){
        monde->tourSuivant();
        cout << *monde;
        if (monde->simulationFini()) break;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    cout << "Simulation finie apres " << monde->obtenirNbTour() << " tours";

    //chercherMeilleureRatio(50, 50);
    //enregistrerStats(50, 50, 506, 253);
	return 0;
}



