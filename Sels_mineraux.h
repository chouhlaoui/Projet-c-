#ifndef SELS_MINERAUX_H
#define SELS_MINERAUX_H

#include <Sprite.h>

class Sels_mineraux : public Sprite
{
    public:
        Sels_mineraux();

        void tourSuivant() override;
};

#endif // SELS_MINERAUX_H
