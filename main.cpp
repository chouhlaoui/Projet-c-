#include <iostream>
#include <limits>
using namespace std;

#include <Monde.h>

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

    n = 10;//getEntier("Nombre de Ligne du monde : ");
    m = 10;//getEntier("Nombre de Colonne du monde : ");

    Monde monde(n, m);

    monde.afficher();

	return 0;
}
