#include "Sprite.h"

Sprite::Sprite() : Sprite(' ', -1) {}

Sprite::Sprite(char symbole, int temps_vie) : symbole(symbole), temps_vie(temps_vie) {}

Sprite::~Sprite() {}

char Sprite::getSymbole()
{
    return symbole;
}

void Sprite::tourSuivant(){}
