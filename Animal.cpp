#include <algorithm>
#include <vector>
#include <tuple>
#include <iostream>
using namespace std;

#include "Monde.h"
#include "Animal.h"
#include "Sels_mineraux.h"

Animal::Animal(Coordonnees coordonnees, char symbole, bool sexe,
               short age, short faim, short tour_sans_reproduction, short tour_reproduction,
               const short duree_vie, const short tours_sans_manger, const short age_min_reproduction,
               const short rythme_reproduction, const short temps_reproduction, const short* coefficients) :

               Chose(coordonnees, symbole),
               sexe(sexe), age(age), faim(faim), tour_sans_reproduction(tour_sans_reproduction), tour_reproduction(tour_reproduction),
               duree_vie(duree_vie), tours_sans_manger(tours_sans_manger), age_min_reproduction(age_min_reproduction),
               rythme_reproduction(rythme_reproduction), temps_reproduction(temps_reproduction), coefficients(coefficients) {}

Animal::~Animal() {}

void Animal::tourSuivant()
{
    incrementerCompteurs();

    if (!seReproduit())
    {
        if (aFiniReproduction() && sexe)
        {
            //creerBebe();
        }
        else if (Coordonnees caseChoisie = choisirCase(); caseChoisie != coordonnees)
        {
            monde->deplacerChose(this, caseChoisie);
            action = true;
        }
        else if(aFaim())
        {
            manger();
        }
        else if(peutSeReproduire())
        {
            //seReproduire();
        }
    }

    if (verifierFaim()) return;
    if (verifierAge()) return;
}

void Animal::incrementerCompteurs()
{
    age++;
    faim++;
    tour_sans_reproduction++;
    tour_reproduction++;
}

bool Animal::seReproduit()
{
    return tour_reproduction <= temps_reproduction;
}

bool Animal::aFiniReproduction()
{
    return tour_reproduction == temps_reproduction+1;
}

Coordonnees Animal::choisirCase()
{
    vector<Coordonnees> caseAccessibles = monde->caseAccessibles(coordonnees);
    vector<short> scores = Animal::evaluerCases(caseAccessibles);
    return Animal::choisirMeilleureCase(caseAccessibles, scores);
}

vector<short> Animal::evaluerCases(vector<Coordonnees> cases)
{
    vector<short> scores;

    for(const Coordonnees& Case : cases)
    {
        scores.push_back(Animal::evaluerCase(Case));
    }

    return scores;
}

short Animal::evaluerCase(Coordonnees coordonnees)
{
    short score = 0, index = 0;

    for(const char& type : LISTE_SYMBOLES)
    {
        score += monde->compterTypeAdjacents(type, coordonnees, 0) * coefficients[index];
        score += monde->compterTypeAdjacents(type, coordonnees, 1) * coefficients[index + 1];
        index += 2;
    }
    return score;
}

Coordonnees Animal::choisirMeilleureCase(vector<Coordonnees> cases, vector<short> scores)
{
    short meilleurScore = *max_element(scores.begin(), scores.end());

    vector<Coordonnees> meilleuresCases;
    for (size_t i = 0; i < scores.size(); i++)
    {
        if (scores[i] == meilleurScore)
        {
            int x, y, z; tie(x, y, z) = cases[i];
            meilleuresCases.push_back(cases[i]);
        }
    }

    int indexChoisi = monde->obtenirNbTour() % meilleuresCases.size();

    return meilleuresCases[indexChoisi];
}

bool Animal::aFaim()
{
    return faim > tours_sans_manger / 2;
}

void Animal::manger() {}

bool Animal::peutSeReproduire()
{
    return age >= age_min_reproduction && tour_reproduction >= rythme_reproduction;
}

void Animal::seReproduire()
{
    if (!peutSeReproduire()) return;

    Animal* partenaire = trouverPartenaire();
    if (partenaire)
    {
        Chose::ajouterLog(coordonnees, "partenaire trouve");
        tour_reproduction = 0;
        partenaire->tour_reproduction = 0;

        partenaire->action = true;
    }
}

Animal* Animal::trouverPartenaire()
{
    vector<Coordonnees> casesAdjacentes = monde->casesAdjacentes(coordonnees);

    for (const Coordonnees& caseAdj : casesAdjacentes) {

        Chose* chose = monde->obtenirChose(caseAdj);
        if (chose && chose->obtenirSymbole() == symbole) {

            Animal* partenaire = dynamic_cast<Animal*>(chose);
            if (partenaire && partenaire->sexe != sexe && partenaire->peutSeReproduire()) {
                return partenaire;
            }
        }
    }
    return nullptr;
}

Coordonnees Animal::trouverCaseLibreAutour(Animal* femelle) {
    vector<Coordonnees> casesLibres;

    vector<Coordonnees> casesAutour = monde->caseAccessibles(femelle->coordonnees);
    for (const Coordonnees& caseLibre : casesAutour)
        {
        if (monde->obtenirChose(caseLibre) == nullptr)
        {
            casesLibres.push_back(caseLibre);
        }
    }

    if (!casesLibres.empty()) {
        return casesLibres[monde->obtenirNbTour() % casesLibres.size()];
    }

    return make_tuple(-1, -1, -1); // Aucun espace libre
}

void Animal::creerBebe()
{
    tour_sans_reproduction = 0;

    Coordonnees caseNaissance = trouverCaseLibreAutour(this);
    if (caseNaissance == make_tuple(-1, -1, -1))
    {
        Chose::ajouterLog(coordonnees, "pas de place");
        return;
    }

    Chose::ajouterLog(caseNaissance, "un bebe est ne");
    monde->ajouterChose(this->clone(caseNaissance));
}

bool Animal::verifierAge()
{
    if (age > duree_vie)
    {
        Chose::ajouterLog(coordonnees, "Un animal est mort de viellesse");
        mourir();
        return true;
    }
    return false;
}

bool Animal::verifierFaim()
{
    if (faim > tours_sans_manger)
    {
        Chose::ajouterLog(coordonnees, "Un animal est mort de faim");
        mourir();
        return true;
    }
    return false;
}

void Animal::mourir()
{
    int x, y, z; tie(x, y, z) = coordonnees;
    if(monde->CaseVide({x, y, 0}))
    {
        monde->ajouterChose(new Sels_Mineraux({x, y, 0}));
    }
    monde->supprimmerChose(this);
}
