#ifndef JOUEUR
#define JOUEUR

#include "constantes.hpp"
#include "Cartes.hpp"
#include "PaquetCartes.hpp"
#include "console.hpp"
#include "ListeDates.hpp"

class Joueur
{
    private:
        Carte tete;
        Carte jeu[4];
        int points;
        std::vector<Carte> figuresGagnees;

        bool verifierFigure();
        bool verifierDesordre();
        void piocher(PaquetCartes& pioche, PaquetCartes& defausse);
        void recupererDefausse(PaquetCartes& defausse);
        void changerFigure(PaquetCartes& piocheFigures);
        void intervertirCartesVisibles();
        void intervertirCartesCachees();
        void revelerJeu(PaquetCartes& pioche, PaquetCartes& piocheFigures);
        void changerJeu(PaquetCartes& pioche);
        Carte voirCarte(int numero);
        void changerCarte(int numero, Carte nouvelle);
        void echangerCarteDansMain(int numero1, int numero2);
    public:
        Joueur(PaquetCartes& pioche, PaquetCartes& figures);
        bool action(PaquetCartes& pioche, PaquetCartes& piocheFigures, PaquetCartes& defausse);
        void afficherTete();
        void afficherMain();
        int getPoints();
};

#endif // JOUEUR
