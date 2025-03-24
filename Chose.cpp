#include "Chose.h"

#include <iostream>
#include <tuple>
#include <vector>
#include <string>
using namespace std;

#include "Monde.h"
#include "Chose.h"

#include "Constantes.h"
using namespace Constantes;

Monde* Chose::monde = nullptr;
vector<string> Chose::logs;

void Chose::ajouterLog(Coordonnees coordonnees, const string& message)
{
    int x, y, z; tie(x, y, z) = coordonnees;
    string log = "[" + to_string(x) + "][" + to_string(y) + "] " + message;
    Chose::logs.push_back(log);
}

Chose::Chose(Coordonnees coordonnees, char symbole) : coordonnees(coordonnees), symbole(symbole) {}

Chose::~Chose() {}

ostream& operator<<(ostream& os, const Chose& chose)
{
    os << chose.symbole;
    return os;
}

void Chose::tourSuivant(){}
