#include "Monde.h"
#include "Chose.h"
#include "Herbe.h"
#include "Sels_Mineraux.h"

int Sels_Mineraux::nbSels = 0;

Sels_Mineraux::Sels_Mineraux(Coordonnees coordonnees) : Chose(coordonnees, SYMBOLE_SELS, 0)
{
    nbSels++;
}

Sels_Mineraux::~Sels_Mineraux()
{
    nbSels--;
}

void Sels_Mineraux::tourSuivant()
{
    if (age++ >= DUREE_VIE_SELS)
    {
        Chose::ajouterLog(coordonnees, "De l'herbe a pousse");
        monde->supprimmerChose(this);
        monde->ajouterChose(new Herbe(coordonnees, 0));
    }
}
