#ifndef ADVERSAIRE
#define ADVERSAIRE

#include "Joueur.hpp"

class Adversaire : public Joueur{
    private:
        int priorite;
        //Les priorites sont:
        /*
            0: Obtenir des points pour obtenir un avantage. L'IA va donc chercher a completer la main la plus proche qui rapporte des points. Choisie lorsque les scores sont egaux
            1: Obtenir des points pour rattrapper le joueur. L'IA va essayer de completer une main qui n'est ni trop loin ni trop faible pour rattrapper son deficit.
            Elle peut aussi essayer des mains qui retirent des points au joueur si elles sont faisables.
            Choisie lorsque le joueur a plus de points que l'IA
            2: Expedier le jeu. L'IA va essayer de reduire le nombre de figures afin de terminer le jeu plus vite. Choisie lorsque l'IA a un avantage de points
            3: Perturber le joueur. L'IA va essayer d'obtenir des combinaisons donnant acces a des coups speciaux qui perturbent le joueur. Choisie lorsque le joueur est susceptible de completer une main dangereuse
        */
        bool modeDiagnostic;
        bool cartesCachees;
        std::vector<Carte> memoire; //La memoire contient les cartes qui ont ete defaussees
        std::vector<int> correctVerifie, correctVerifieDesordre, correctJoker, correctJokerDesordre, correctVerifieDiableDesordre, correctVerifieMaudite, correctVerifieMauditeDesordre;
        //Fonctions redefinies pour un choix automatique
        void piocher(PaquetCartes& pioche, PaquetCartes& defausse, int numeroCarte);
        void recupererDefausse(PaquetCartes& defausse, int numeroCarte);
        /*perturberRangsEnnemis(Joueur& ennemi);
        echangerUnites(Joueur& ennemi);
        assassinat(Joueur& ennemi, PaquetCartes& pioche, PaquetCartes& defausse)*/
        int nombreCorrectVecteur(std::vector<int> vec);

    public:
        Adversaire(PaquetCartes& pioche, PaquetCartes& figures);
        bool action(PaquetCartes& pioche, PaquetCartes& piocheFigures, PaquetCartes& defausse, Joueur& ennemi);
        int evaluerPriorite(Joueur& ennemi);
        void choisirAction(PaquetCartes& pioche, PaquetCartes& piocheFigures, PaquetCartes& defausse, Joueur& ennemi);
        void afficherMain();
};

#endif // ADVERSAIRE
