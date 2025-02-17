#include "Herbe.h"

#include <iostream>
using namespace std;

Herbe::Herbe() : Sprite('H', -1) {}

void Herbe::tourSuivant()
{
    cout << "Tour Herbe" << endl;
}
