#ifndef PAQUETCARTES
#define PAQUETCARTES

#include "constantes.hpp"
#include "Cartes.hpp"

class PaquetCartes
{
    private:
        int type;//pioche t�tes, pioche chiffres
        std::vector<Carte> pile;
    public:
        PaquetCartes(int _type);
        void melange();
        Carte enleverCarteDessus();
        Carte retournerCarteDessus();
        void ajouterCarteDessous(Carte c);
        void ajouterCarteDessus(Carte c);
        bool pileVide();
        void afficher();
        Carte changerCarteDessus(Carte entrante);
        void afficherCarteDessus();
        void renouvelerPaquets(PaquetCartes& defausse);
        void viderPaquet();
        int getSize();
};

#endif // PAQUETCARTES
