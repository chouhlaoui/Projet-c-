#include "Mouton.h"

#include <iostream>
using namespace std;

Mouton::Mouton() : Animal('M', 50) {}

void Mouton::tourSuivant()
{
    cout << "Tour Mouton" << endl;
}

