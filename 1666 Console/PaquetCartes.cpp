#include "PaquetCartes.hpp"

using namespace std;

PaquetCartes::PaquetCartes(int _type) : type(-1), pile()
{
    type = _type;
    if(type == 0)//tetes
    {
        for(int i = 1; i < 1 + NOMBRE_COULEURS; i++) //Pour chaque couleur
        {
            for(int j = 10 + VALET; j <= 10 + ROI; j++) //Creer un valet, reine et roi
            {
                Carte c(j, i);
                pile.push_back(c);
            }
        }
        Carte c(-1, JOKER); //Creer deux jokers
        pile.push_back(c);
        pile.push_back(c);
    }
    else if(type == 1)//chiffres
    {
        for(int i = 1; i < 1 + NOMBRE_COULEURS; i++) //Pour chaque couleur
        {
            for(int j = 0; j < 10; j++) //Creer 10 cartes
            {
                Carte c(j,i);
                pile.push_back(c);
            }
        }
    }
}
void PaquetCartes::melange()
{
    srand(time(NULL));
    int nombreAleatoire;
    for(int i = 0; i < 100; i++)
    {
        nombreAleatoire = rand()% pile.size();
        Carte bouge = pile[nombreAleatoire];
        pile.erase(pile.begin() + nombreAleatoire);
        pile.push_back(bouge);
    }
}
Carte PaquetCartes::enleverCarteDessus()
{
    Carte c = pile[0];
    pile.erase(pile.begin());
    return c;
}

Carte PaquetCartes::retournerCarteDessus()
{
    if(pile.size() != 0)
    {
        Carte c = pile[0];
        return c;
    }
    Carte c2;
    return c2;
}

void PaquetCartes::ajouterCarteDessous(Carte c)
{
    pile.push_back(c);
}

void PaquetCartes::ajouterCarteDessus(Carte c)
{
    pile.insert(pile.begin(), c);
}

Carte PaquetCartes::changerCarteDessus(Carte entrante) //Echange avec le dessus du paquet
{
    Carte recup = pile[0];
    pile.erase(pile.begin());
    ajouterCarteDessus(entrante);
    return recup;
}

void PaquetCartes::afficherCarteDessus()
{
    pile[0].afficher();
}

void PaquetCartes::afficher()
{
    if(type == 0) cout << "Pioche des tetes" << endl;
    else if(type == 1) cout << "Pioche chiffres" << endl;
    for(int i = 0; i < (int)pile.size(); i++)
    {
        pile[i].afficher();
        cout << ", ";
    }
}

bool PaquetCartes::pileVide()
{
    if(pile.empty()) return true;
    else return false;
}

void PaquetCartes::renouvelerPaquets(PaquetCartes& defausse) //Remet toute la defausse dans la pioche
{
    Carte derniereJetee = defausse.enleverCarteDessus();
    while(!defausse.pileVide())
    {
        ajouterCarteDessous(defausse.enleverCarteDessus());
    }
    defausse.ajouterCarteDessus(derniereJetee);
    melange();
}

void PaquetCartes::viderPaquet()
{
    pile.clear();
}

int PaquetCartes::getSize()
{
    return pile.size();
}
