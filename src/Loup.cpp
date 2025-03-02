#include "Loup.h"

int Loup::nbLoup = 0;

Loup::Loup() : Animal('L', 60)
{
    nbLoup++;
}

Loup::~Loup()
{
    nbLoup--;
}

int Loup::getNbLoup() {
    return nbLoup;
}

void Loup::tourSuivant()
{

}
