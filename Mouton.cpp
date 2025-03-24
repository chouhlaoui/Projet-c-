#include "Monde.h"
#include "Mouton.h"

#include "Constantes.h"
using namespace Constantes;

int Mouton::nbMouton = 0;

Mouton::Mouton(Coordonnees coordonnees, bool sexe, short age, short faim, short tour_sans_reproduction, short tour_reproduction) :
    Animal(coordonnees, SYMBOLE_MOUTON, sexe, age, faim, tour_sans_reproduction, tour_reproduction,
           DUREE_VIE_MOUTON, TOURS_SANS_MANGER_MOUTON, AGE_MIN_REPRODUCTION_MOUTON, RYTHME_REPRODUCTION_MOUTON, TEMPS_REPRODUCTION_MOUTON, COEFFICIENTS_MOUTON)
{
    nbMouton++;
}

Mouton::~Mouton()
{
    nbMouton--;
}

void Mouton::manger()
{
    int x, y, z;
    tie(x, y, z) = coordonnees;
    Coordonnees coordonneesSol = make_tuple(x, y, 0);

    Chose* chose = monde->obtenirChose(coordonneesSol);

    if (chose && chose->estdeType(SYMBOLE_HERBE))
    {
        Chose::ajouterLog(coordonneesSol, "Un mouton a mange de l'herbe");
        monde->supprimmerChose(chose);
        faim = 0;
    }
}
