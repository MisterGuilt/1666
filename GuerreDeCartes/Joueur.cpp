#include "Joueur.hpp"

using namespace std;

Joueur::Joueur(PaquetCartes& pioche, PaquetCartes& figures)
{
    points = 0;
    for(int i = 0; i < 4; i++)
    {
        jeu[i] = pioche.enleverCarteDessus();
    }
    tete = figures.enleverCarteDessus();
}

bool Joueur::verifierFigure()
{
    int dateTete = tete.getDate();
    int dateJoueur = jeu[0].getValeur() * 1000 + jeu[1].getValeur() * 100 + jeu[2].getValeur() * 10 + jeu[3].getValeur();
    if(dateTete == dateJoueur) return true;

    if(tete.getCouleur() == "Joker")
    {
        ListeDates valides(0);
        for(int i = 0; valides.getNombreDates(); i++)
        {
            if(dateJoueur == valides.getDate()) return true;
        }
    }
    return false;
}

bool Joueur::verifierDesordre()
{
    int dateTeteBase = tete.getDate();
    vector<int> dateJoueur;
    vector<int> dateTete;

    for(int i = 0; i < 4; i++)
    {
        dateJoueur.push_back(jeu[i].getValeur());
        dateTete.push_back(dateTeteBase % 10);
        dateTeteBase = (dateTeteBase - (dateTeteBase % 10))/10;
    }

    for(int i = 0; i < 4; i++)
    {
        int chiffre = dateJoueur[i];
        for(int j = 0; j < (int)dateTete.size(); j++)
        {
            if(chiffre == dateTete[j])
            {
                dateTete.erase(dateTete.begin() + j);
                j = 5;
            }
        }
    }
    if(dateTete.empty()) return true;
    if(dateTeteBase == DATEJOKER)
    {
        ListeDates valides(0);
        for(int x = 0; x < valides.getNombreDates(); x++)
        {
            dateTete.clear();
            for(int i = 0; i < 4; i++)
            {
                dateTete.push_back(valides.getDate());
            }

            for(int i = 0; i < 4; i++)
            {
                int chiffre = dateJoueur[i];
                for(int j = 0; j < (int)dateTete.size(); j++)
                {
                    if(chiffre == dateTete[j])
                    {
                        dateTete.erase(dateTete.begin() + j);
                        j = 5;
                    }
                }
            }
            if(dateTete.empty()) return true;
        }
    }
    return false;
}

void Joueur::piocher(PaquetCartes& pioche, PaquetCartes& defausse)
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
void Joueur::recupererDefausse(PaquetCartes& defausse)
{
    int numeroCarte;
    do
    {
        cout << " Quelle carte jeter (0 a 3) ? ";
        numeroCarte = saisie();
    }while(numeroCarte < 0 || numeroCarte >= 4);
    jeu[numeroCarte] = defausse.changerCarteDessus(jeu[numeroCarte]);
}
void Joueur::changerFigure(PaquetCartes& piocheFigures)
{
    Carte c = piocheFigures.enleverCarteDessus();
    piocheFigures.ajouterCarteDessous(tete);
    tete = c;
}
void Joueur::intervertirCartesVisibles()
{
    Carte c = jeu[0];
    jeu[0] = jeu[1];
    jeu[1] = c;
}
void Joueur::intervertirCartesCachees()
{
    Carte c = jeu[2];
    jeu[2] = jeu[3];
    jeu[3] = c;
}

void Joueur::changerJeu(PaquetCartes& pioche)
{
    for(int i = 0; i < 4; i++)
    {
        pioche.ajouterCarteDessous(jeu[i]);
        jeu[i] = pioche.enleverCarteDessus();
    }
}

void Joueur::revelerJeu(PaquetCartes& pioche, PaquetCartes& piocheFigures)
{
    if(verifierFigure()) points += tete.getValeur();
    else if(verifierDesordre()) points += tete.getValeur() - 3;
    figuresGagnees.push_back(tete);
    tete = piocheFigures.enleverCarteDessus();
    changerJeu(pioche);
}

bool Joueur::action(PaquetCartes& pioche, PaquetCartes& piocheFigures, PaquetCartes& defausse)
{
    int choix, nombreChoix = 5;
    bool reveleMain = verifierFigure();
    if(!reveleMain) reveleMain = verifierDesordre();
    if (reveleMain) nombreChoix++;
    do
    {
        cout << " 0) Quitter le jeu" << endl;
        cout << " 1) Piocher" << endl;
        if(!defausse.pileVide()) cout << " 2) Recuperer la derniere carte jetee" << endl;
        cout << " 3) Intervertir les cartes visibles" << endl;
        cout << " 4) Intervertir les cartes cachees" << endl;
        cout << " 5) Changer la figure" << endl;
        if(reveleMain) cout << " 6) Attaque !" << endl;
        cout << " Que faire ? ";
        choix = saisie();
    }while(choix < 0 || choix > nombreChoix || (defausse.pileVide() && choix == 2));

    if(choix == 0) return false;
    else if(choix == 1) piocher(pioche, defausse);
    else if(choix == 2) recupererDefausse(defausse);
    else if(choix == 3) intervertirCartesVisibles();
    else if(choix == 4) intervertirCartesCachees();
    else if(choix == 5) changerFigure(piocheFigures);
    else revelerJeu(pioche, piocheFigures);
    return true;
}

void Joueur::afficherMain()
{
    for(int i = 0; i < 4; i++)
    {
        jeu[i].afficher();
        if(i < 3) cout << ", ";
    }
}
void Joueur::afficherTete()
{
    tete.afficher();
    cout << " " << tete.getDate();
}

int Joueur::getPoints()
{
    return points;
}

Carte Joueur::voirCarte(int numero)
{
    return jeu[numero];
}

void Joueur::changerCarte(int numero, Carte nouvelle)
{
    jeu[numero] = nouvelle;
}

void Joueur::echangerCarteDansMain(int numero1, int numero2)
{
    Carte temporaire = jeu[numero1];
    jeu[numero1] = jeu[numero2];
    jeu[numero2] = temporaire;
}
