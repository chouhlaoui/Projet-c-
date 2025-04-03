#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <tuple>
using namespace std;

namespace Constantes
{
    constexpr short HAUTEUR = 2;
    using Coordonnees = tuple<int, int, int>;

    // Param�tres du g�n�rateur pseudo-al�atoire
    constexpr int a = 48271;
    constexpr long long N = 2147483647;

    //Symboles
    constexpr char LISTE_SYMBOLES[] = {'_', 'S', 'M', 'L'};
    constexpr char SYMBOLE_HERBE = '_';
    constexpr char SYMBOLE_SELS = 'S';
    constexpr char SYMBOLE_MOUTON = 'M';
    constexpr char SYMBOLE_LOUP = 'L';

    // Param�tres des moutons
    constexpr short DUREE_VIE_MOUTON = 50;
    constexpr short TOURS_SANS_MANGER_MOUTON = 5;
    constexpr short AGE_MIN_REPRODUCTION_MOUTON = 5;
    constexpr short RYTHME_REPRODUCTION_MOUTON = 5;
    constexpr short TEMPS_REPRODUCTION_MOUTON = 1;
                                           //dessus, � cot�, � cot�(proportionnel)
    constexpr short COEFFICIENTS_MOUTON[] = {30, 2, 0,
                                             0, 1, 0,
                                             0, 20, -5,
                                             0, -100, -10};

    // Param�tres des loups
    constexpr short DUREE_VIE_LOUP = 60;
    constexpr short TOURS_SANS_MANGER_LOUP = 10;
    constexpr short AGE_MIN_REPRODUCTION_LOUP = 5;
    constexpr short RYTHME_REPRODUCTION_LOUP = 5;
    constexpr short TEMPS_REPRODUCTION_LOUP = 1;
    constexpr short COEFFICIENTS_LOUP[] = {0, 0, 0,
                                           0, 0, 0,
                                           0, 30, 0,
                                           0, 20, -5};

    // Param�tre de l'herbe
    constexpr short RYTHME_REPRODUCTION_HERBE = 10; //-1 -> pas de pousse // 0 -> pousse � chaque tour

    // Param�tre des sels min�raux
    constexpr short DUREE_VIE_SELS = 1;
}

#endif // CONSTANTES_H
