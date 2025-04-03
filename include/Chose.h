#ifndef CHOSE_H
#define CHOSE_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "Constantes.h"
using namespace Constantes;

class Monde;

class Chose{
    public:
        static Monde* monde;
        static vector<string> logs;

    protected:
        Coordonnees coordonnees;
        char symbole;
        short age;
        bool action;

    public:
        static void setMonde(Monde* m) { monde = m;}
        static void ajouterLog(Coordonnees, const string&);

        Chose(Coordonnees, char, short);
        virtual ~Chose();

        const Coordonnees obtenirCoordonnees() const {return coordonnees;}
        void changeCoordonnees(Coordonnees coordonnees) {this->coordonnees = coordonnees;}
        const char obtenirSymbole() const {return symbole;}
        bool estdeType(char type) {return symbole == type;}
        const bool aJouerCeTour() {return action;}
        void reinitialiserAction() {action = false;}

        friend ostream& operator<<(ostream& os, const Chose&);
        virtual void tourSuivant();
};

#endif // CHOSE_H
