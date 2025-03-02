#include "Herbe.h"

int Herbe::nbHerbe = 0;

Herbe::Herbe() : Sprite('H', -1)
{
    nbHerbe++;
}

Herbe::~Herbe()
{
    nbHerbe--;
}

int Herbe::getNbHerbe() {
    return nbHerbe;
}