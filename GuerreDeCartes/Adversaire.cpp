#include "adversaire.hpp"

using namespace std;

Adversaire::Adversaire(PaquetCartes& pioche, PaquetCartes& figures)
{
    points = 0;
    tailleMemoireMax = 40;
    for(int i = 0; i < 4; i++)
    {
        jeu[i] = pioche.enleverCarteDessus();
    }
    tete = figures.enleverCarteDessus();
}

bool Adversaire::verifierFigure()
{
    int dateTete = tete.getDate();
    int date = jeu[0].getValeur() * 1000 + jeu[1].getValeur() * 100 + jeu[2].getValeur() * 10 + jeu[3].getValeur();
    if(tete.getCouleur() != "Joker")
    {
        if(dateTete == date)
        {
            return true;
        }
    }
    else if(date == ROICARREAU || date == ROICOEUR || date == ROIPIQUE || date == ROITREFLE || date == DAMECARREAU || date == DAMECOEUR || date == DAMEPIQUE || date == DAMETREFLE || date == VALETCARREAU || date == VALETCOEUR || date == VALETPIQUE || date == VALETTREFLE)
        return true;
    return false;
}

bool Adversaire::verifierDesordre()
{
    Adversaire copie = *this;
    bool presenceDesordre = false;
    for(int i = 0; i < 4; i++)
    {
        copie.changerCarte(0, voirCarte(i));
        copie.changerCarte(i, voirCarte(0));
        for(int j = 1; j < 4; j++)
        {
            if(i != j)
            {
                copie.echangerCarteDansMain(i, j);
                presenceDesordre = copie.verifierFigure();
                if(presenceDesordre == true) return true;
                copie.echangerCarteDansMain(i, j);
            }
        }
        copie.echangerCarteDansMain(1, 2);
        copie.echangerCarteDansMain(2, 3);
        presenceDesordre = copie.verifierFigure();
        if(presenceDesordre == true) return true;
        copie.echangerCarteDansMain(2, 3);
        copie.echangerCarteDansMain(1, 3);
        presenceDesordre = copie.verifierFigure();
        if(presenceDesordre == true) return true;
        copie.echangerCarteDansMain(1, 2);
        copie.echangerCarteDansMain(1, 3);
    }
    return false;
}

void Adversaire::piocher(PaquetCartes& pioche, PaquetCartes& defausse)
{
    int numeroCarte;
    do
    {
        cout << " Quelle carte jeter (0 a 3) ? ";
        numeroCarte = saisie();
    }while(numeroCarte < 0 || numeroCarte >= 4);
    defausse.ajouterCarteDessus(jeu[numeroCarte]);
    jeu[numeroCarte] = pioche.enleverCarteDessus();
}
void Adversaire::recupererDefausse(PaquetCartes& defausse)
{
    int numeroCarte;
    do
    {
        cout << " Quelle carte jeter (0 a 3) ? ";
        numeroCarte = saisie();
    }while(numeroCarte < 0 || numeroCarte >= 4);
    jeu[numeroCarte] = defausse.changerCarteDessus(jeu[numeroCarte]);;
}
void Adversaire::changerFigure(PaquetCartes& piocheFigures)
{
    Carte c = piocheFigures.enleverCarteDessus();
    piocheFigures.ajouterCarteDessous(tete);
    tete = c;
}
void Adversaire::intervertirCartesVisibles()
{
    Carte c = jeu[0];
    jeu[0] = jeu[1];
    jeu[1] = c;
}
void Adversaire::intervertirCartesCachees()
{
    Carte c = jeu[2];
    jeu[2] = jeu[3];
    jeu[3] = c;
}

void Adversaire::changerJeu(PaquetCartes& pioche)
{
    for(int i = 0; i < 4; i++)
    {
        pioche.ajouterCarteDessous(jeu[i]);
        jeu[i] = pioche.enleverCarteDessus();
    }
}

void Adversaire::revelerJeu(PaquetCartes& pioche, PaquetCartes& piocheFigures)
{
    int date = tete.getDate();
    if(date == (jeu[0].getValeur() * 1000 + jeu[1].getValeur() * 100 + jeu[2].getValeur() * 10 + jeu[3].getValeur()))
    {
        points += tete.getValeur();
        figuresGagnees.push_back(tete);
        tete = piocheFigures.enleverCarteDessus();
        changerJeu(pioche);
    }
}

void Adversaire::action(PaquetCartes& pioche, PaquetCartes& piocheFigures, PaquetCartes& defausse)
{
    int choix, nombreChoix = 5;
    bool reveleMain = verifierFigure();
    if (reveleMain) choix = 6;
    else
    {
        do
        {
            cout << " 1) Piocher" << endl;
            if(!defausse.pileVide()) cout << " 2) Recuperer la derniere carte jetee" << endl;
            cout << " 3) Intervertir les cartes visibles" << endl;
            cout << " 4) Intervertir les cartes cachees" << endl;
            cout << " 5) Changer la figure" << endl;
            cout << " Que faire ? ";
            choix = saisie();
        }while(choix < 1 || choix > nombreChoix || (defausse.pileVide() && choix == 2));
    }
    if(choix == 1) piocher(pioche, defausse);
    else if(choix == 2) recupererDefausse(defausse);
    else if(choix == 3) intervertirCartesVisibles();
    else if(choix == 4) intervertirCartesCachees();
    else if(choix == 5) changerFigure(piocheFigures);
    else revelerJeu(pioche, piocheFigures);
}

void Adversaire::afficherMain()
{
    for(int i = 0; i < 4; i++)
    {
        jeu[i].afficher();
        cout << ", ";
    }
}
void Adversaire::afficherTete()
{
    tete.afficher();
    cout << " " << tete.getDate();
}

int Adversaire::getPoints()
{
    return points;
}

int Adversaire::getDate()
{
    return jeu[0].getValeur() * 1000 + jeu[1].getValeur() * 100 + jeu[2].getValeur() * 10 + jeu[3].getValeur();
}

Carte Adversaire::voirCarte(int numero)
{
    return jeu[numero];
}

void Adversaire::changerCarte(int numero, Carte nouvelle)
{
    jeu[numero] = nouvelle;
}

void Adversaire::echangerCarteDansMain(int numero1, int numero2)
{
    Carte temporaire = jeu[numero1];
    jeu[numero1] = jeu[numero2];
    jeu[numero2] = temporaire;
}
