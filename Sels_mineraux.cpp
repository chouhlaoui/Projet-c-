#include "Monde.h"
#include "Chose.h"
#include "Herbe.h"
#include "Sels_Mineraux.h"

int Sels_Mineraux::nbSels = 0;

Sels_Mineraux::Sels_Mineraux(Coordonnees coordonnees) : Chose(coordonnees, SYMBOLE_SELS)
{
    nbSels++;
}

Sels_Mineraux::~Sels_Mineraux()
{
    nbSels--;
}

void Sels_Mineraux::tourSuivant()
{
    monde->supprimmerChose(this);
    monde->ajouterChose(new Herbe(coordonnees));
}
