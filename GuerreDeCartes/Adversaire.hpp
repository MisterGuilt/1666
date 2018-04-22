#ifndef ADVERSAIRE
#define ADVERSAIRE

#include "Cartes.hpp"
#include "PaquetCartes.hpp"
#include "console.hpp"

class Adversaire
{
    private:
        Carte tete;
        Carte jeu[4];
        int points;
        bool ordinateurActif;
        std::vector<Carte> figuresGagnees;
        int tailleMemoireMax;
        std::vector<Carte> memoire;

        bool verifierFigure();
        bool verifierDesordre();
        void piocher(PaquetCartes& pioche, PaquetCartes& defausse);
        void recupererDefausse(PaquetCartes& defausse);
        void changerFigure(PaquetCartes& piocheFigures);
        void intervertirCartesVisibles();
        void intervertirCartesCachees();
        void revelerJeu(PaquetCartes& pioche, PaquetCartes& piocheFigures);
        void changerJeu(PaquetCartes& pioche);
        int getDate();
        Carte voirCarte(int numero);
        void changerCarte(int numero, Carte nouvelle);
        void echangerCarteDansMain(int numero1, int numero2);
    public:
        Adversaire(PaquetCartes& pioche, PaquetCartes& figures, bool ordinateur);
        void action(PaquetCartes& pioche, PaquetCartes& piocheFigures, PaquetCartes& defausse);
        int getPoints();
        void afficherTete();
        void afficherMain();
};

#endif // ADVERSAIRE
