#ifndef ADVERSAIRE
#define ADVERSAIRE

#include "Joueur.hpp"

class Adversaire : public Joueur{
    private:
        int tailleMemoireMax;
        std::vector<Carte> memoire;

        //Fonctions redefinies pour un choix automatique
        /*void piocher(PaquetCartes& pioche, PaquetCartes& defausse, int numeroCarte);
        void recupererDefausse(PaquetCartes& defausse, int numeroCarte);
        perturberRangsEnnemis(Joueur& ennemi);
        echangerUnites(Joueur& ennemi);
        assassinat(Joueur& ennemi, PaquetCartes& pioche, PaquetCartes& defausse)*/
    public:
        Adversaire(PaquetCartes& pioche, PaquetCartes& figures);
        bool action(PaquetCartes& pioche, PaquetCartes& piocheFigures, PaquetCartes& defausse, Joueur& ennemi);
};

#endif // ADVERSAIRE
