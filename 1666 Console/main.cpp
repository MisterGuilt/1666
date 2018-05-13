#include "constantes.hpp"
#include "Cartes.hpp"
#include "PaquetCartes.hpp"
#include "Joueur.hpp"
#include "Adversaire.hpp"
#include "console.hpp"

using namespace std;

int main()
{

    PaquetCartes figures(0), chiffres(1), defausse(2);
    figures.melange();
    chiffres.melange();
    Joueur utilisateur(chiffres, figures);
    Adversaire ordinateur(chiffres, figures);
    int nombreTours = 1;
    bool jeuEnCours = true;
    int tourJoueur = 0;

    //Pour les scenarios personnalises
    /*Carte c0(0, COEUR);
    ordinateur.changerCarte(0, c0);
    Carte c1(1, COEUR);
    ordinateur.changerCarte(1, c1);
    Carte c2(2, COEUR);
    ordinateur.changerCarte(2, c2);
    Carte c3(3, COEUR);
    ordinateur.changerCarte(3, c3);
    Carte fig(10 + VALET, COEUR);
    ordinateur.changerFigure(fig);*/
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    do
    {
        system("cls");
        SetConsoleTextAttribute(hConsole, 15);
        gotoxy(20, 0);
        cout << " Bienvenue dans 1666 ! " << endl;
        SetConsoleTextAttribute(hConsole, 10);
        gotoxy(0, 1);
        cout << " Joueur :" << endl;
        gotoxy(1, 2);
        utilisateur.afficherTete();
        gotoxy(1, 3);
        utilisateur.afficherMain();
        gotoxy(1, 4);
        cout << "Points: " << utilisateur.getPoints();
        gotoxy(30, 1);
        SetConsoleTextAttribute(hConsole, 11);
        cout << "Ordinateur :";
        gotoxy(30, 2);
        ordinateur.afficherTete();
        gotoxy(30, 3);
        ordinateur.afficherMain();
        gotoxy(30, 4);
        cout << "Points: " << ordinateur.getPoints();
        gotoxy(0, 6);
        SetConsoleTextAttribute(hConsole, 15);
        cout << " Defausse : ";
        if(defausse.pileVide()) cout << "_";
        else defausse.afficherCarteDessus();
        gotoxy(0, 7);
        cout << " Chiffres restants: " << chiffres.getSize() << " - Figures restantes: " << figures.getSize();
        gotoxy(0, 9);
        if(nombreTours % 2 == tourJoueur)
        {
            SetConsoleTextAttribute(hConsole, 10);
            cout << " A toi de jouer !" << endl;
            jeuEnCours = utilisateur.action(chiffres, figures, defausse, (Joueur&)ordinateur);
        }
        else
        {
            SetConsoleTextAttribute(hConsole, 11);
            cout << " Tour de l'ordinateur" << endl;
            jeuEnCours = ordinateur.action(chiffres, figures, defausse, utilisateur);
            Sleep(3000);
        }
        cout << endl;
        nombreTours++;
        if(chiffres.pileVide()) chiffres.renouvelerPaquets(defausse);
    }while(!figures.pileVide() && jeuEnCours);
    SetConsoleTextAttribute(hConsole, 15);
    cout << " Fin du jeu" << endl;
    if(utilisateur.getPoints() > ordinateur.getPoints()) cout << " Victoire !!" << endl;
    else if(utilisateur.getPoints() == ordinateur.getPoints()) cout << " Egalite !" << endl;
    else cout << " Defaite" << endl;
    return 0;
}
