#include "Sprite.h"
#include "Mouton.h"

int Mouton::nbMouton = 0;

Mouton::Mouton() : Animal('M', 50)
{
    nbMouton++;
}

Mouton::~Mouton()
{
    nbMouton--;
}

int Mouton::getNbMouton() {
    return nbMouton;
}

void Mouton::tourSuivant()
{

}

