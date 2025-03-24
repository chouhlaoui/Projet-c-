#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <tuple>
using namespace std;

namespace Constantes
{
    constexpr short HAUTEUR = 2;
    using Coordonnees = tuple<int, int, int>;

    // Paramètres du générateur pseudo-aléatoire
    constexpr int a = 48271;
    constexpr long long N = 2147483647;

    //Symboles
    constexpr char LISTE_SYMBOLES[] = {'_', 'S', 'M', 'L'};
    constexpr char SYMBOLE_HERBE = '_';
    constexpr char SYMBOLE_SELS = 'S';
    constexpr char SYMBOLE_MOUTON = 'M';
    constexpr char SYMBOLE_LOUP = 'L';

    // Paramètres des moutons
    constexpr short DUREE_VIE_MOUTON = 50;
    constexpr short TOURS_SANS_MANGER_MOUTON = 5;
    constexpr short AGE_MIN_REPRODUCTION_MOUTON = 5;
    constexpr short RYTHME_REPRODUCTION_MOUTON = 2;
    constexpr short TEMPS_REPRODUCTION_MOUTON = 5;
    constexpr short COEFFICIENTS_MOUTON[] = {20, 2, 0, 0, 0, 1, 0, -50};

    // Paramètres des loups
    constexpr short DUREE_VIE_LOUP = 60;
    constexpr short TOURS_SANS_MANGER_LOUP = 10;
    constexpr short AGE_MIN_REPRODUCTION_LOUP = 5;
    constexpr short RYTHME_REPRODUCTION_LOUP = 2;
    constexpr short TEMPS_REPRODUCTION_LOUP = 5;
    constexpr short COEFFICIENTS_LOUP[] = {0, 0, 0, 0, 0, 20, 0, 1};

    // Paramètres des sels minéraux
    constexpr short DUREE_VIE_SELS = 1;
}

#endif // CONSTANTES_H
