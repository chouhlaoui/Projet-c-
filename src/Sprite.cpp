#include "Sprite.h"

#include <iostream>
using namespace std;

Sprite::Sprite(char symbole, int temps_vie) : symbole(symbole), temps_vie(temps_vie) {}

Sprite::~Sprite() {}

char Sprite::getSymbole()
{
    return symbole;
}

ostream& operator<<(ostream& os, const Sprite& sprite)
{
    os << sprite.symbole;
    return os;
}

void Sprite::tourSuivant(){}
