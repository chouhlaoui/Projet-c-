#include "Herbe.h"

#include "Constantes.h"
using namespace Constantes;

int Herbe::nbHerbe = 0;

Herbe::Herbe(Coordonnees coordonnees) : Chose(coordonnees, SYMBOLE_HERBE)
{
    nbHerbe++;
}

Herbe::~Herbe()
{
    nbHerbe--;
}
