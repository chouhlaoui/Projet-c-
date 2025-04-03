#include "InterfaceGraphique.h"
#include "Monde.h"

int main(int argc, char** argv) {
    
    int nb_ligne, nb_colonne, nb_mouton, nb_loup;
    nb_ligne = 50;
    nb_colonne = 50;
    nb_mouton = 506;
    nb_loup = 253;
    
    Initialise(argc, argv, nb_ligne, nb_colonne, nb_mouton, nb_loup);
    LancerSimulation();
    Terminate();

    return 0;
}