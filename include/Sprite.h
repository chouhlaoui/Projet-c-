#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
using namespace std;

class Sprite{
    protected:
        char symbole;
        int temps_vie;

    public:
        Sprite(char, int);
        virtual ~Sprite();

        friend ostream& operator<<(ostream& os, const Sprite& sprite);
        virtual void tourSuivant();
};
#endif // SPRITE_H
