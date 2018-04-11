#ifndef CARTES
#define CARTES

#include "constantes.hpp"

class Carte
{
    private:
        int valeur;
        int couleur;
        int points;
        int date;
    public:
        Carte(int _valeur, int _couleur);
        Carte();
        std::string getCouleur();
        int getPoints();
        int getValeur();
        int getDate();
        void afficher();
};

#endif // CARTES
