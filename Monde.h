#ifndef MONDE_H
#define MONDE_H

#include <string>
#include <vector>
using namespace std;

class Monde
{
    public:
        int n, m;
        vector<vector<char>> tab;

        Monde(int , int);
        ~Monde();

        void afficher();

    private:
        void afficherNumeroColonne();
        void afficherInterLigne();
        void afficherLigne(int);
        string ajouterRemplissage(int , string);

};

#endif // MONDE_H
