#ifndef ANIMAL_H
#define ANIMAL_H

#include "Chose.h"

class Animal : public Chose
{
    protected:
        bool sexe;
        short faim;
        short tour_sans_reproduction;
        short tour_reproduction;
        const short duree_vie;
        const short tours_sans_manger;
        const short age_min_reproduction;
        const short rythme_reproduction;
        const short temps_reproduction;
        const short* coefficients;

    public:
        Animal(Coordonnees, char, short, bool, short, short, short, const short, const short, const short, const short, const short, const short*);
        virtual ~Animal();

        void tourSuivant() override;

    public:
        void incrementerCompteurs();

        Coordonnees choisirCase();
        vector<short> evaluerCases(vector<Coordonnees>);
        short evaluerCase(Coordonnees);
        Coordonnees choisirMeilleureCase(vector<Coordonnees>, vector<short>);

        bool aFaim();
        virtual void manger();

        void seReproduire();
        bool peutSeReproduire();
        bool seReproduit();
        bool aFiniReproduction();
        Animal* trouverPartenaire();
        Coordonnees trouverCaseLibreAutour(Animal*);
        void creerBebe();
        virtual Animal* clone(Coordonnees coord) const = 0;

        bool verifierAge();
        bool verifierFaim();
        void mourir();
};

#endif // ANIMAL_H
