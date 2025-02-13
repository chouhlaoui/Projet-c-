#include <Loup.h>

#include <iostream>
using namespace std;


Loup::Loup() : Animal('L', 60) {}

void Loup::tourSuivant()
{
    cout << "Tour Loup" << endl;
}
