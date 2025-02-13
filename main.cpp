#include <iostream>
#include <limits>
using namespace std;

#include <Monde.h>
#include <Sprite.h>
#include <Sels_mineraux.h>
#include <Herbe.h>
#include <Animal.h>
#include <Mouton.h>
#include <Loup.h>

int getEntier(string message)
{
    int i;

    cout << message;
    while(!(cin >> i))
    {
        cout << "Erreur de saisie. Recommencez : ";
        cin.clear();
        cin.ignore( numeric_limits<streamsize>::max(), '\n' );
    }

    return i;
}

int main(int argc, char **argv)
{
	cout << "#####     Simulation d'ecosysteme     #####" << endl;

    int n, m;
    char continuer;

    n = 10;//getEntier("Nombre de Ligne du monde : ");
    m = 10;//getEntier("Nombre de Colonne du monde : ");

    Monde monde(n, m);
    monde.tab[0][0] = new Mouton();
    monde.tab[0][1] = new Loup();
    monde.tab[1][0] = new Herbe();
    monde.tab[1][1] = new Sels_mineraux();

    do
    {
        monde.afficher();
        monde.tourSuivant();

        cout << "Voulez-vous continuer ? (o/n) : ";
        cin >> continuer;
    } while (continuer == 'o');

	return 0;
}
