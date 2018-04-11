#include "PaquetCartes.hpp"

using namespace std;

PaquetCartes::PaquetCartes(int _type)
{
    type = _type;
    if(type == 0)//tetes
    {
        for(int i = 1; i < 1 + NOMBRE_COULEURS; i++)
        {
            for(int j = 10 + VALET; j <= 10 + ROI; j++)
            {
                Carte c(j, i);
                pile.push_back(c);
            }
        }
        Carte c(-1, JOKER);
        pile.push_back(c);
        pile.push_back(c);
    }
    else if(type == 1)//chiffres
    {
        for(int i = 1; i < 1 + NOMBRE_COULEURS; i++)
        {
            for(int j = 0; j < 10; j++)
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
void PaquetCartes::ajouterCarteDessous(Carte c)
{
    pile.push_back(c);
}

void PaquetCartes::ajouterCarteDessus(Carte c)
{
    pile.insert(pile.begin(), c);
}

Carte PaquetCartes::changerCarteDessus(Carte entrante)
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
    }
}

bool PaquetCartes::pileVide()
{
    if(pile.empty()) return true;
    else return false;
}

void PaquetCartes::renouvelerPaquets(PaquetCartes& defausse)
{
    Carte derniereJetee = defausse.enleverCarteDessus();
    while(!defausse.pileVide())
    {
        ajouterCarteDessous(defausse.enleverCarteDessus());
    }
    defausse.ajouterCarteDessus(derniereJetee);
    melange();
}


