#ifndef JOUEUR
#define JOUEUR

#include "constantes.hpp"
#include "Cartes.hpp"
#include "PaquetCartes.hpp"
#include "console.hpp"
#include "ListeDates.hpp"

class Joueur
{
    protected:
        Carte tete; //La figure
        Carte jeu[4]; //Les chiffres
        int points;
        std::vector<Carte> figuresGagnees;

        int getDateEnMain();
        std::vector<int> verifierFigure();
        std::vector<int> verifierDesordre();
        std::vector<int> verifierJoker();
        std::vector<int> verifierJokerDesordre();
        std::vector<int> verifierDatesMaudites();
        std::vector<int> verifierDatesMauditesDesordre();
        std::vector<int> verifierDateDiableDesordre();
        void piocher(PaquetCartes& pioche, PaquetCartes& defausse);
        void recupererDefausse(PaquetCartes& defausse);
        void changerFigure(PaquetCartes& piocheFigures);
        void intervertirCartesVisibles();
        void intervertirCartesCachees();
        void revelerJeu(PaquetCartes& pioche, PaquetCartes& piocheFigures, Joueur& ennemi);
        void changerJeu(PaquetCartes& pioche);
        void echangerCarteDansMain(int numero1, int numero2);
        int nombreCartesMemeCouleur(int couleur);
        bool verifierPerturberRangsEnnemis();
        bool verifierEchangerUnites();
        bool verifierAssassinat();
        void perturberRangsEnnemis(Joueur& ennemi);
        void echangerUnites(Joueur& ennemi);
        void assassinat(Joueur& ennemi, PaquetCartes& pioche, PaquetCartes& defausse);
        bool vecteurVrai(std::vector<int> vec);
    public:
        Carte getCarte(int numero);
        Joueur(PaquetCartes& pioche, PaquetCartes& figures);
        bool action(PaquetCartes& pioche, PaquetCartes& piocheFigures, PaquetCartes& defausse, Joueur& ennemi);
        void afficherTete();
        void afficherMain();
        int getPoints();
        void soitMaudit(bool ordre, bool diable);
        void changerCarte(int numero, Carte nouvelle);
        virtual ~Joueur() {}
};

#endif // JOUEUR
