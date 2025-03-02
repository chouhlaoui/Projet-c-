#ifndef HERBE_H
#define HERBE_H

#include "Sprite.h"

class Herbe : public Sprite
{
    public:
        static int nbHerbe;
        static int getNbHerbe();
        
        Herbe();
        ~Herbe();
};

#endif // HERBE_H
