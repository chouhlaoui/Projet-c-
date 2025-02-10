
class Sprite{
    private:
        char symbole;
        int lifetime;
    public:
        Sprite(char type, int lifetime);
        void afficher();
        void update();
        void mourir();
        void getCoord();
};