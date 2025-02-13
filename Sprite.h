#ifndef SPRITE_H
#define SPRITE_H

class Sprite{
    protected:
        char symbole;
        int temps_vie;

    public:
        Sprite();
        Sprite(char, int);
        virtual ~Sprite();

        char getSymbole();
        virtual void tourSuivant();
};
#endif // SPRITE_H
