#ifndef PAQUETCARTES
#define PAQUETCARTES

#include "constantes.hpp"
#include "Cartes.hpp"

class PaquetCartes
{
    private:
        int type;//pioche têtes, pioche chiffres
        std::vector<Carte> pile;
    public:
        PaquetCartes(int _type);
        void melange();
        Carte enleverCarteDessus();
        void ajouterCarteDessous(Carte c);
        void ajouterCarteDessus(Carte c);
        bool pileVide();
        void afficher();
        Carte changerCarteDessus(Carte entrante);
        void afficherCarteDessus();
        void renouvelerPaquets(PaquetCartes& defausse);
};

#endif // PAQUETCARTES
