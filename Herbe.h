#ifndef HERBE_H
#define HERBE_H

#include "Sprite.h"

class Herbe : public Sprite
{
    public:
        Herbe();

        void tourSuivant() override;
};

#endif // HERBE_H
