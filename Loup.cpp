#include <iostream>
using namespace std;

#include "Monde.h"
#include "Loup.h"

#include "Constantes.h"
using namespace Constantes;

int Loup::nbLoup = 0;

Loup::Loup(Coordonnees coordonnees, bool sexe, short age, short faim, short tour_sans_reproduction, short tour_reproduction) :
    Animal(coordonnees, SYMBOLE_LOUP, sexe, age, faim, tour_sans_reproduction, tour_reproduction,
           DUREE_VIE_LOUP, TOURS_SANS_MANGER_LOUP, AGE_MIN_REPRODUCTION_LOUP, RYTHME_REPRODUCTION_LOUP, TEMPS_REPRODUCTION_LOUP, COEFFICIENTS_LOUP)
{
    nbLoup++;
}

Loup::~Loup()
{
    nbLoup--;
}

void Loup::manger()
{
    Mouton* mouton = rechercherMouton();
    if(mouton)
    {
        Chose::ajouterLog(coordonnees, "Un loup a mange un mouton");
        monde->supprimmerChose(mouton);
        mouton = nullptr;
        faim = 0;
    }
}

Mouton* Loup::rechercherMouton()
{
    vector<Coordonnees> casesAdjacentes = monde->casesAdjacentes(coordonnees);

    for (const Coordonnees& caseAdj : casesAdjacentes) {

        Chose* chose = monde->obtenirChose(caseAdj);
        if (chose && chose->obtenirSymbole() == SYMBOLE_MOUTON) {

            return dynamic_cast<Mouton*>(chose);
        }
    }
    return nullptr;
}
