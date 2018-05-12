#include "adversaire.hpp"

using namespace std;

Adversaire::Adversaire(PaquetCartes& pioche, PaquetCartes& figures) : Joueur(pioche, figures), tailleMemoireMax(40), memoire() {}

/*void Adversaire::piocher(PaquetCartes& pioche, PaquetCartes& defausse, int numeroCarte)
{
    defausse.ajouterCarteDessus(jeu[numeroCarte]);
    jeu[numeroCarte] = pioche.enleverCarteDessus();
}

void Adversaire::recupererDefausse(PaquetCartes& defausse, int numeroCarte)
{
    jeu[numeroCarte] = defausse.changerCarteDessus(jeu[numeroCarte]);;
}*/

bool Adversaire::action(PaquetCartes& pioche, PaquetCartes& piocheFigures, PaquetCartes& defausse, Joueur& ennemi)
{
    int choix;
    vector<int> correctVerfie, correctVerifieDesordre, correctJoker, correctJokerDesordre, correctVerifieDiableDesordre, correctVerfieMaudite, correctVerfieMauditeDesordre;
    bool boucleWhile = true;
    bool reveleMain = false, peutAssassiner = verifierAssassinat();
    bool peutPerturberRangsEnnemis = verifierPerturberRangsEnnemis(), peutEchangerUnites = verifierEchangerUnites();
    bool possedeDateMaudite = false;

    correctVerfie = verifierFigure();
    cout << "Verfier Ordre : ";
    for(unsigned int i = 0; i < correctVerfie.size(); i++)
    {
        cout << correctVerfie[i] << ", ";
    }
    cout << endl;
    reveleMain = vecteurVrai(correctVerfie);


    if(!reveleMain)
    {
        correctVerifieDesordre = verifierDesordre();
        cout << "Verfier Desordre : ";
        for(unsigned int i = 0; i < correctVerifieDesordre.size(); i++)
        {
            cout << correctVerifieDesordre[i] << ", ";
        }
        cout << endl;
        reveleMain = vecteurVrai(correctVerifieDesordre);
    }

    if(!reveleMain && tete.estJoker())
    {
        correctJoker = verifierJoker();
        cout << "Verfier Joker Ordre : ";
        for(unsigned int i = 0; i < correctJoker.size(); i++)
        {
            cout << correctJoker[i] << ", ";
        }
        cout << endl;
        if(vecteurVrai(correctJoker) == true) reveleMain = true;
        else
        {
            correctJokerDesordre = verifierJokerDesordre();
            cout << "Verfier Joker Desordre : ";
            for(unsigned int i = 0; i < correctJokerDesordre.size(); i++)
            {
                cout << correctJokerDesordre[i] << ", ";
            }
            cout << endl;
            if(vecteurVrai(correctJokerDesordre) == true) reveleMain = true;
        }
    }
    if(!reveleMain)
    {
        correctVerfieMaudite = verifierDatesMaudites();
        cout << "Verfier Maudite Ordre : ";
        for(unsigned int i = 0; i < correctVerfieMaudite.size(); i++)
        {
            cout << correctVerfieMaudite[i] << ", ";
        }
        cout << endl;
        possedeDateMaudite = vecteurVrai(correctVerfieMaudite);
        if(!possedeDateMaudite)
        {
            correctVerfieMauditeDesordre = verifierDatesMauditesDesordre();
            cout << "Verfier Maudite Desordre : ";
            for(unsigned int i = 0; i < correctVerfieMauditeDesordre.size(); i++)
            {
                cout << correctVerfieMauditeDesordre[i] << ", ";
            }
            cout << endl;
            possedeDateMaudite = vecteurVrai(correctVerfieMauditeDesordre);
        }
    }
    do
    {
        cout << " 0) Quitter le jeu" << endl;
        cout << " 1) Piocher" << endl;
        if(!defausse.pileVide()) cout << " 2) Recuperer la derniere carte jetee" << endl;
        cout << " 3) Intervertir les cartes visibles" << endl;
        cout << " 4) Intervertir les cartes cachees" << endl;
        cout << " 5) Changer la figure" << endl;
        if(reveleMain || possedeDateMaudite) cout << " 6) Attaque !" << endl;
        if(peutPerturberRangsEnnemis) cout << " 7) Perturbe les rangs ennemis !" << endl;
        if(peutEchangerUnites) cout << " 8) Echange une de tes cartes avec ton adversaire !" << endl;
        if(peutAssassiner) cout << " 9) Force ton adversaire a jeter une carte !" << endl;
        cout << " Que faire ? ";
        choix = saisie();
        if(choix >= 0 && choix <= 5) boucleWhile = false;
        if(choix == 2 && defausse.pileVide()) boucleWhile = true;
        if(choix == 6 && (reveleMain || possedeDateMaudite)) boucleWhile = false;
        if(choix == 7 && peutPerturberRangsEnnemis) boucleWhile = false;
        if(choix == 8 && peutEchangerUnites) boucleWhile = false;
        if(choix == 9 && peutAssassiner) boucleWhile = false;
    }while(boucleWhile);

    if(choix == 0) return false;
    else if(choix == 1) piocher(pioche, defausse);
    else if(choix == 2) recupererDefausse(defausse);
    else if(choix == 3) intervertirCartesVisibles();
    else if(choix == 4) intervertirCartesCachees();
    else if(choix == 5) changerFigure(piocheFigures);
    else if(choix == 6) revelerJeu(pioche, piocheFigures, ennemi);
    else if(choix == 7) perturberRangsEnnemis(ennemi);
    else if(choix == 8) echangerUnites(ennemi);
    else if(choix == 9) assassinat(ennemi, pioche, defausse);
    return true;
}
