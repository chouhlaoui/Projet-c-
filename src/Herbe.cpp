#include "Monde.h"
#include "Herbe.h"

#include "Constantes.h"
using namespace Constantes;

int Herbe::nbHerbe = 0;

Herbe::Herbe(Coordonnees coordonnees, short age) : Chose(coordonnees, SYMBOLE_HERBE, age)
{
    nbHerbe++;
}

Herbe::~Herbe()
{
    nbHerbe--;
}

void Herbe::tourSuivant()
{
    if (age++ == RYTHME_REPRODUCTION_HERBE)
    {
        age = 0;

        vector<Coordonnees> caseLibres = monde->casesAdjacentes(coordonnees);
        if (caseLibres.empty()) return;

        int indexChoisi = age % caseLibres.size();
        Coordonnees caseChoisie = caseLibres[indexChoisi];
        if(!monde->CaseVide(caseChoisie)) return;

        ajouterLog(caseChoisie, "De l'herbe a pousse");
        monde->ajouterChose(new Herbe(caseChoisie, 0));
    }
}
