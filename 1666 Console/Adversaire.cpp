#include "adversaire.hpp"
#include <windows.h>

using namespace std;

Adversaire::Adversaire(PaquetCartes& pioche, PaquetCartes& figures) : Joueur(pioche, figures), priorite(0), modeDiagnostic(false), cartesCachees(true), memoire(), correctVerifie(), correctVerifieDesordre(), correctJoker(), correctJokerDesordre(), correctVerifieDiableDesordre(), correctVerifieMaudite(), correctVerifieMauditeDesordre() {}

void Adversaire::piocher(PaquetCartes& pioche, PaquetCartes& defausse, int numeroCarte)
{
    defausse.ajouterCarteDessus(jeu[numeroCarte]);
    jeu[numeroCarte] = pioche.enleverCarteDessus();
}

void Adversaire::recupererDefausse(PaquetCartes& defausse, int numeroCarte)
{
    jeu[numeroCarte] = defausse.changerCarteDessus(jeu[numeroCarte]);;
}

int Adversaire::evaluerPriorite(Joueur& ennemi)
{
    if(points == ennemi.getPoints())
    {
        return 0;
    }
    else if(points < ennemi.getPoints())
    {
        return 1;
    }
    else if(points > ennemi.getPoints())
    {
        return 2;
    }
    return 0;
}

void Adversaire::choisirAction(PaquetCartes& pioche, PaquetCartes& piocheFigures, PaquetCartes& defausse, Joueur& ennemi)
{
    int carteCible = 0;
    int scorePrecedent; //Dans les cas ou le nombre de cartes correctes avant le choix peut varier, permet de savoir si piocher dans la defausse donne une carte correcte
    vecteurVrai(correctVerifieMaudite);
    Carte copieJeu[4];
    Carte carteDefausse; //Represente la carte actuellement sur la defausse. Peut aussi servir de stockage temporaire lors d'un echange
    if(vecteurVrai(correctVerifie) || vecteurVrai(correctVerifieMaudite)) //Jouer la main si elle est valide et ordonnee
    {
        cout << " Attaque avec la main "; jeu[0].afficher(); cout << ", "; jeu[1].afficher(); cout << ", "; jeu[2].afficher(); cout << ", "; jeu[3].afficher(); cout << endl;
        revelerJeu(pioche, piocheFigures, ennemi);
        return;
    }
    else if((nombreCorrectVecteur(correctVerifie) < nombreCorrectVecteur(correctVerifieDesordre) && vecteurVrai(correctVerifieDesordre)) || (nombreCorrectVecteur(correctVerifieMaudite) < nombreCorrectVecteur(correctVerifieMauditeDesordre) && vecteurVrai(correctVerifieMauditeDesordre))) //Possibilite de transformer une main desordre valide en main ordre valide par echange
    {
        if(modeDiagnostic) cout << "Test echange" << endl;
        for(int i = 0; i < 4; i++)
        {
            copieJeu[i] = jeu[i];
        }
        carteDefausse = jeu[0];
        jeu[0] = jeu[1];
        jeu[1] = carteDefausse;
        if(vecteurVrai(verifierFigure()) || vecteurVrai(correctVerifieMaudite)) //Les cartes 0 et 1 donnent une main ordonnee valide si inversees
        {
            for(int i = 0; i < 4; i++)
            {
                jeu[i] = copieJeu[i];
            }
            intervertirCartesVisibles();
            return;
        }
        else
        {
            for(int i = 0; i < 4; i++)
            {
                jeu[i] = copieJeu[i];
            }
            carteDefausse = jeu[2];
            jeu[2] = jeu[3];
            jeu[3] = carteDefausse;
            if(vecteurVrai(verifierFigure()) || vecteurVrai(correctVerifieMaudite)) //Les cartes 2 et 3 donnent une main ordonnee valide si inversees
            {
                for(int i = 0; i < 4; i++)
                {
                    jeu[i] = copieJeu[i];
                }
                intervertirCartesCachees();
                return;
            }
            else
            {
                for(int i = 0; i < 4; i++)
                {
                    jeu[i] = copieJeu[i];
                }
                cout << " Attaque avec la main "; jeu[0].afficher(); cout << ", "; jeu[1].afficher(); cout << ", "; jeu[2].afficher(); cout << ", "; jeu[3].afficher(); cout << endl;
                revelerJeu(pioche, piocheFigures, ennemi); //Jouer la main desordre
                return;
            }
        }
    }
    else if(tete.estJoker() && nombreCorrectVecteur(correctVerifie) == 3) //Proche de 1666
    {
        if(modeDiagnostic) cout << "Proche de 1666" << endl;
        for(int i = 0; i < 4; i++)
        {
            copieJeu[i] = jeu[i];
        }
        carteDefausse = defausse.retournerCarteDessus();
        correctVerifie = verifierFigure();
        for(unsigned int i = 0; i < 4; i++) //Choisir quelle carte on veut remplacer
        {
            if(correctVerifie[i] == 0)
            {
                carteCible = i;
            }
        }
        jeu[carteCible] = carteDefausse;
        if(vecteurVrai(correctVerifie)) //La defausse permet de completer la main
        {
            for(int i = 0; i < 4; i++)
            {
                jeu[i] = copieJeu[i];
            }
            cout << " Pioche dans la defausse, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
            recupererDefausse(defausse, carteCible);
            return;
        }
        else
        {
            for(int i = 0; i < 4; i++)
            {
                jeu[i] = copieJeu[i];
            }
            cout << " Pioche, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
            piocher(pioche, defausse, carteCible);
            return;
        }
    }
    switch(priorite)
    {
        case 0: //Priorite aux mains sans valeur ou l'on remplace la figure, puis aux mains tres proches (3 valides), puis aux mains proches (2 valides), puis aux mains lointaines (1 ou 0 valides)
        {
            if(nombreCorrectVecteur(correctVerifie) == 0 && nombreCorrectVecteur(correctVerifieDesordre) == 0) //On est le plus eloigne d'une main valide
            {
                if(modeDiagnostic) cout << "Main sans valeur" << endl;
                if(limiteFigure > 0)
                {
                    cout << " Changement de figure" << endl;
                    changerFigure(piocheFigures);
                    return;
                }
                else
                {
                    for(int i = 0; i < 4; i++)
                    {
                        copieJeu[i] = jeu[i];
                    }
                    carteDefausse = defausse.retournerCarteDessus();
                    for(unsigned int i = 0; i < 4; i++) //Choisir quelle carte on veut remplacer
                    {
                        if(correctVerifieDesordre[i] == 0)
                        {
                            carteCible = i;
                        }
                    }
                    scorePrecedent = nombreCorrectVecteur(correctVerifieDesordre);
                    jeu[carteCible] = carteDefausse;
                    correctVerifieDesordre = verifierDesordre();
                    if(nombreCorrectVecteur(correctVerifieDesordre) > scorePrecedent) //La defausse permet d'avoir une carte valide
                    {
                        for(int i = 0; i < 4; i++)
                        {
                            jeu[i] = copieJeu[i];
                        }
                        cout << " Pioche dans la defausse, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                        recupererDefausse(defausse, carteCible);
                        return;
                    }
                    else
                    {
                        for(int i = 0; i < 4; i++)
                        {
                            jeu[i] = copieJeu[i];
                        }
                        cout << " Pioche, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                        piocher(pioche, defausse, carteCible);
                        return;
                    }
                }
            }
            else if(nombreCorrectVecteur(correctVerifie) == 3) //Tres proche d'une main ordre
            {
                if(modeDiagnostic) cout << "Verifie ordre = 3" << endl;
                for(int i = 0; i < 4; i++)
                {
                    copieJeu[i] = jeu[i];
                }
                carteDefausse = defausse.retournerCarteDessus();
                correctVerifie = verifierFigure();
                for(unsigned int i = 0; i < 4; i++) //Choisir quelle carte on veut remplacer
                {
                    if(correctVerifie[i] == 0)
                    {
                        carteCible = i;
                    }
                }
                jeu[carteCible] = carteDefausse;
                if(vecteurVrai(correctVerifie)) //La defausse permet de completer la main
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche dans la defausse, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    recupererDefausse(defausse, carteCible);
                    return;
                }
                else
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    piocher(pioche, defausse, carteCible);
                    return;
                }
            }
            else if(nombreCorrectVecteur(correctVerifieDesordre) == 3) //Tres proche d'une main desordre
            {
                if(modeDiagnostic) cout << "Verifie desordre = 3" << endl;
                for(int i = 0; i < 4; i++)
                {
                    copieJeu[i] = jeu[i];
                }
                carteDefausse = defausse.retournerCarteDessus();
                for(unsigned int i = 0; i < 4; i++) //Choisir quelle carte on veut remplacer
                {
                    if(correctVerifieDesordre[i] == 0)
                    {
                        carteCible = i;
                    }
                }
                jeu[carteCible] = carteDefausse;
                correctVerifieDesordre = verifierDesordre();
                if(vecteurVrai(correctVerifieDesordre)) //La defausse permet de completer la main
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche dans la defausse, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    recupererDefausse(defausse, carteCible);
                    return;
                }
                else
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    piocher(pioche, defausse, carteCible);
                    return;
                }
            }
            else if(nombreCorrectVecteur(correctVerifie) == 2) //Proche d'une main ordre
            {
                if(modeDiagnostic) cout << "Verifie ordre = 2" << endl;
                for(int i = 0; i < 4; i++)
                {
                    copieJeu[i] = jeu[i];
                }
                carteDefausse = defausse.retournerCarteDessus();
                for(unsigned int i = 0; i < 4; i++) //Choisir quelle carte on veut remplacer
                {
                    if(correctVerifie[i] == 0)
                    {
                        carteCible = i;
                    }
                }
                jeu[carteCible] = carteDefausse;
                correctVerifie = verifierFigure();
                if(nombreCorrectVecteur(correctVerifie) > 2) //La defausse permet d'avoir une carte valide
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche dans la defausse, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    recupererDefausse(defausse, carteCible);
                    return;
                }
                else
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    piocher(pioche, defausse, carteCible);
                    return;
                }
            }
            else if(nombreCorrectVecteur(correctVerifieDesordre) == 2) //Proche d'une main desordre
            {
                if(modeDiagnostic) cout << "Verifie desordre = 2" << endl;
                for(int i = 0; i < 4; i++)
                {
                    copieJeu[i] = jeu[i];
                }
                carteDefausse = defausse.retournerCarteDessus();
                for(unsigned int i = 0; i < 4; i++) //Choisir quelle carte on veut remplacer
                {
                    if(correctVerifieDesordre[i] == 0)
                    {
                        carteCible = i;
                    }
                }
                jeu[carteCible] = carteDefausse;
                correctVerifieDesordre = verifierDesordre();
                if(nombreCorrectVecteur(correctVerifieDesordre) > 2) //La defausse permet d'avoir une carte valide
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche dans la defausse, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    recupererDefausse(defausse, carteCible);
                    return;
                }
                else
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    piocher(pioche, defausse, carteCible);
                    return;
                }
            }
            else if(nombreCorrectVecteur(correctVerifie) == 1) //Loin d'une main ordre
            {
                if(modeDiagnostic) cout << "Verifie ordre = 1" << endl;
                for(int i = 0; i < 4; i++)
                {
                    copieJeu[i] = jeu[i];
                }
                carteDefausse = defausse.retournerCarteDessus();
                for(unsigned int i = 0; i < 4; i++) //Choisir quelle carte on veut remplacer
                {
                    if(correctVerifie[i] == 0)
                    {
                        carteCible = i;
                    }
                }
                jeu[carteCible] = carteDefausse;
                correctVerifie = verifierFigure();
                if(nombreCorrectVecteur(correctVerifie) > 1) //La defausse permet d'avoir une carte valide
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche dans la defausse, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    recupererDefausse(defausse, carteCible);
                    return;
                }
                else
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    piocher(pioche, defausse, carteCible);
                    return;
                }
            }
            else //Loin d'une main desordre
            {
                if(modeDiagnostic) cout << "Verifie desordre = 1" << endl;
                for(int i = 0; i < 4; i++)
                {
                    copieJeu[i] = jeu[i];
                }
                carteDefausse = defausse.retournerCarteDessus();
                for(unsigned int i = 0; i < 4; i++) //Choisir quelle carte on veut remplacer
                {
                    if(correctVerifieDesordre[i] == 0)
                    {
                        carteCible = i;
                    }
                }
                jeu[carteCible] = carteDefausse;
                correctVerifieDesordre = verifierDesordre();
                if(nombreCorrectVecteur(correctVerifieDesordre) > 1) //La defausse permet d'avoir une carte valide
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche dans la defausse, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    recupererDefausse(defausse, carteCible);
                    return;
                }
                else
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    piocher(pioche, defausse, carteCible);
                    return;
                }
            }
            break;
        }
        case 1: //Priorite aux dates maudites proches, puis aux mains sans valeur, puis aux mains proches
        {
            if(nombreCorrectVecteur(correctVerifieMaudite) >= 2) //Proche d'une date maudite ordre
            {
                if(modeDiagnostic) cout << "Verifie maudite ordre = 2+" << endl;
                for(int i = 0; i < 4; i++)
                {
                    copieJeu[i] = jeu[i];
                }
                carteDefausse = defausse.retournerCarteDessus();
                for(unsigned int i = 0; i < 4; i++) //Choisir quelle carte on veut remplacer
                {
                    if(correctVerifieMaudite[i] == 0)
                    {
                        carteCible = i;
                    }
                }
                scorePrecedent = nombreCorrectVecteur(correctVerifieMaudite);
                jeu[carteCible] = carteDefausse;
                correctVerifieMaudite = verifierDatesMaudites();
                if(nombreCorrectVecteur(correctVerifieMaudite) > scorePrecedent) //La defausse permet d'avoir une carte valide
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche dans la defausse, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    recupererDefausse(defausse, carteCible);
                    return;
                }
                else
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    piocher(pioche, defausse, carteCible);
                    return;
                }
            }
            else if(nombreCorrectVecteur(correctVerifieMauditeDesordre) >= 2) //Proche d'une date maudite desordre
            {
                if(modeDiagnostic) cout << "Verifie maudite desordre = 2+" << endl;
                for(int i = 0; i < 4; i++)
                {
                    copieJeu[i] = jeu[i];
                }
                carteDefausse = defausse.retournerCarteDessus();
                for(unsigned int i = 0; i < 4; i++) //Choisir quelle carte on veut remplacer
                {
                    if(correctVerifieMauditeDesordre[i] == 0)
                    {
                        carteCible = i;
                    }
                }
                scorePrecedent = nombreCorrectVecteur(correctVerifieMauditeDesordre);
                jeu[carteCible] = carteDefausse;
                correctVerifieMauditeDesordre = verifierDatesMauditesDesordre();
                if(nombreCorrectVecteur(correctVerifieMauditeDesordre) > scorePrecedent) //La defausse permet d'avoir une carte valide
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche dans la defausse, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    recupererDefausse(defausse, carteCible);
                    return;
                }
                else
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    piocher(pioche, defausse, carteCible);
                    return;
                }
            }
            else if(nombreCorrectVecteur(correctVerifie) == 0 && nombreCorrectVecteur(correctVerifieDesordre) == 0) //On est le plus eloigne d'une main valide
            {
                if(modeDiagnostic) cout << "Main sans valeur" << endl;
                if(limiteFigure > 0)
                {
                    cout << " Changement de figure" << endl;
                    changerFigure(piocheFigures);
                    return;
                }
                else
                {
                    for(int i = 0; i < 4; i++)
                    {
                        copieJeu[i] = jeu[i];
                    }
                    carteDefausse = defausse.retournerCarteDessus();
                    for(unsigned int i = 0; i < 4; i++) //Choisir quelle carte on veut remplacer
                    {
                        if(correctVerifieDesordre[i] == 0)
                        {
                            carteCible = i;
                        }
                    }
                    scorePrecedent = nombreCorrectVecteur(correctVerifieDesordre);
                    jeu[carteCible] = carteDefausse;
                    correctVerifieDesordre = verifierDesordre();
                    if(nombreCorrectVecteur(correctVerifieDesordre) > scorePrecedent) //La defausse permet d'avoir une carte valide
                    {
                        for(int i = 0; i < 4; i++)
                        {
                            jeu[i] = copieJeu[i];
                        }
                        cout << " Pioche dans la defausse, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                        recupererDefausse(defausse, carteCible);
                        return;
                    }
                    else
                    {
                        for(int i = 0; i < 4; i++)
                        {
                            jeu[i] = copieJeu[i];
                        }
                        cout << " Pioche, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                        piocher(pioche, defausse, carteCible);
                        return;
                    }
                }
            }
            else if(nombreCorrectVecteur(correctVerifie) >= 2) //Proche d'une main ordre
            {
                if(modeDiagnostic) cout << "Verifie ordre = 2" << endl;
                for(int i = 0; i < 4; i++)
                {
                    copieJeu[i] = jeu[i];
                }
                carteDefausse = defausse.retournerCarteDessus();
                for(unsigned int i = 0; i < 4; i++) //Choisir quelle carte on veut remplacer
                {
                    if(correctVerifie[i] == 0)
                    {
                        carteCible = i;
                    }
                }
                scorePrecedent = nombreCorrectVecteur(correctVerifie);
                jeu[carteCible] = carteDefausse;
                correctVerifie = verifierFigure();
                if(nombreCorrectVecteur(correctVerifie) > scorePrecedent) //La defausse permet d'avoir une carte valide
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche dans la defausse, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    recupererDefausse(defausse, carteCible);
                    return;
                }
                else
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    piocher(pioche, defausse, carteCible);
                    return;
                }
            }
            else //Loin d'une main desordre
            {
                if(modeDiagnostic) cout << "Verifie desordre = 2-" << endl;
                for(int i = 0; i < 4; i++)
                {
                    copieJeu[i] = jeu[i];
                }
                carteDefausse = defausse.retournerCarteDessus();
                for(unsigned int i = 0; i < 4; i++) //Choisir quelle carte on veut remplacer
                {
                    if(correctVerifieDesordre[i] == 0)
                    {
                        carteCible = i;
                    }
                }
                scorePrecedent = nombreCorrectVecteur(correctVerifieDesordre);
                jeu[carteCible] = carteDefausse;
                correctVerifieDesordre = verifierDesordre();
                if(nombreCorrectVecteur(correctVerifieDesordre) > scorePrecedent) //La defausse permet d'avoir une carte valide
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche dans la defausse, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    recupererDefausse(defausse, carteCible);
                    return;
                }
                else
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    piocher(pioche, defausse, carteCible);
                    return;
                }
            }
            break;
        }
        case 2: //Priorites aux mains tres proches, peu importe leur effet. Sinon, esssayer de defausser une figure. Si changements epuises, assumer l'ordre de la priorite 0
        {
            if(nombreCorrectVecteur(correctVerifie) == 3) //Tres proche d'une main ordre, donc on peut facilement se debarasser d'une figure avec des benefices
            {
                if(modeDiagnostic) cout << "Verifie ordre = 3" << endl;
                for(int i = 0; i < 4; i++)
                {
                    copieJeu[i] = jeu[i];
                }
                carteDefausse = defausse.retournerCarteDessus();
                correctVerifie = verifierFigure();
                for(unsigned int i = 0; i < 4; i++) //Choisir quelle carte on veut remplacer
                {
                    if(correctVerifie[i] == 0)
                    {
                        carteCible = i;
                    }
                }
                jeu[carteCible] = carteDefausse;
                if(vecteurVrai(correctVerifie)) //La defausse permet de completer la main
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche dans la defausse, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    recupererDefausse(defausse, carteCible);
                    return;
                }
                else
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    piocher(pioche, defausse, carteCible);
                    return;
                }
            }
            else if(nombreCorrectVecteur(correctVerifieDesordre) == 3) //Tres proche d'une main desordre
            {
                if(modeDiagnostic) cout << "Verifie desordre = 3" << endl;
                for(int i = 0; i < 4; i++)
                {
                    copieJeu[i] = jeu[i];
                }
                carteDefausse = defausse.retournerCarteDessus();
                for(unsigned int i = 0; i < 4; i++) //Choisir quelle carte on veut remplacer
                {
                    if(correctVerifieDesordre[i] == 0)
                    {
                        carteCible = i;
                    }
                }
                jeu[carteCible] = carteDefausse;
                correctVerifieDesordre = verifierDesordre();
                if(vecteurVrai(correctVerifieDesordre)) //La defausse permet de completer la main
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche dans la defausse, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    recupererDefausse(defausse, carteCible);
                    return;
                }
                else
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    piocher(pioche, defausse, carteCible);
                    return;
                }
            }
            else if(nombreCorrectVecteur(correctVerifieMauditeDesordre) == 3) //Tres proche d'une date maudite desordre
            {
                if(modeDiagnostic) cout << "Verifie maudit desordre = 3" << endl;
                for(int i = 0; i < 4; i++)
                {
                    copieJeu[i] = jeu[i];
                }
                carteDefausse = defausse.retournerCarteDessus();
                for(unsigned int i = 0; i < 4; i++) //Choisir quelle carte on veut remplacer
                {
                    if(correctVerifieMauditeDesordre[i] == 0)
                    {
                        carteCible = i;
                    }
                }
                jeu[carteCible] = carteDefausse;
                correctVerifieMauditeDesordre = verifierDesordre();
                if(vecteurVrai(correctVerifieMauditeDesordre)) //La defausse permet de completer la main
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche dans la defausse, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    recupererDefausse(defausse, carteCible);
                    return;
                }
                else
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    piocher(pioche, defausse, carteCible);
                    return;
                }
            }
            else if(limiteFigure > 0) //Gaspillage de figure
            {
                if(modeDiagnostic) cout << " Changement de figure" << endl;
                changerFigure(piocheFigures);
                return;
            }
            else if(nombreCorrectVecteur(correctVerifie) == 2) //Proche d'une main ordre
            {
                if(modeDiagnostic) cout << "Verifie ordre = 2" << endl;
                for(int i = 0; i < 4; i++)
                {
                    copieJeu[i] = jeu[i];
                }
                carteDefausse = defausse.retournerCarteDessus();
                for(unsigned int i = 0; i < 4; i++) //Choisir quelle carte on veut remplacer
                {
                    if(correctVerifie[i] == 0)
                    {
                        carteCible = i;
                    }
                }
                jeu[carteCible] = carteDefausse;
                correctVerifie = verifierFigure();
                if(nombreCorrectVecteur(correctVerifie) > 2) //La defausse permet d'avoir une carte valide
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche dans la defausse, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    recupererDefausse(defausse, carteCible);
                    return;
                }
                else
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    piocher(pioche, defausse, carteCible);
                    return;
                }
            }
            else if(nombreCorrectVecteur(correctVerifieDesordre) == 2) //Proche d'une main desordre
            {
                if(modeDiagnostic) cout << "Verifie deordre = 2" << endl;
                for(int i = 0; i < 4; i++)
                {
                    copieJeu[i] = jeu[i];
                }
                carteDefausse = defausse.retournerCarteDessus();
                for(unsigned int i = 0; i < 4; i++) //Choisir quelle carte on veut remplacer
                {
                    if(correctVerifieDesordre[i] == 0)
                    {
                        carteCible = i;
                    }
                }
                jeu[carteCible] = carteDefausse;
                correctVerifieDesordre = verifierDesordre();
                if(nombreCorrectVecteur(correctVerifieDesordre) > 2) //La defausse permet d'avoir une carte valide
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche dans la defausse, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    recupererDefausse(defausse, carteCible);
                    return;
                }
                else
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    piocher(pioche, defausse, carteCible);
                    return;
                }
            }
            else if(nombreCorrectVecteur(correctVerifie) == 1) //Loin d'une main ordre
            {
                if(modeDiagnostic) cout << "Verifie ordre = 1" << endl;
                for(int i = 0; i < 4; i++)
                {
                    copieJeu[i] = jeu[i];
                }
                carteDefausse = defausse.retournerCarteDessus();
                for(unsigned int i = 0; i < 4; i++) //Choisir quelle carte on veut remplacer
                {
                    if(correctVerifie[i] == 0)
                    {
                        carteCible = i;
                    }
                }
                jeu[carteCible] = carteDefausse;
                correctVerifie = verifierFigure();
                if(nombreCorrectVecteur(correctVerifie) > 1) //La defausse permet d'avoir une carte valide
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche dans la defausse, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    recupererDefausse(defausse, carteCible);
                    return;
                }
                else
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    piocher(pioche, defausse, carteCible);
                    return;
                }
            }
            else //Loin d'une main desordre
            {
                if(modeDiagnostic) cout << "Verifie desordre = 0" << endl;
                for(int i = 0; i < 4; i++)
                {
                    copieJeu[i] = jeu[i];
                }
                carteDefausse = defausse.retournerCarteDessus();
                for(unsigned int i = 0; i < 4; i++) //Choisir quelle carte on veut remplacer
                {
                    if(correctVerifieDesordre[i] == 0)
                    {
                        carteCible = i;
                    }
                }
                jeu[carteCible] = carteDefausse;
                correctVerifieDesordre = verifierDesordre();
                if(nombreCorrectVecteur(correctVerifieDesordre) > 1) //La defausse permet d'avoir une carte valide
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche dans la defausse, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    recupererDefausse(defausse, carteCible);
                    return;
                }
                else
                {
                    for(int i = 0; i < 4; i++)
                    {
                        jeu[i] = copieJeu[i];
                    }
                    cout << " Pioche, la carte "; jeu[carteCible].afficher(); cout << " est defaussee" << endl;
                    piocher(pioche, defausse, carteCible);
                    return;
                }
            }
            break;
        }
    }
}

int Adversaire::nombreCorrectVecteur(vector<int> vec)
{
    int nombreCorrect = 0;
    for(int i = 0; i < 4; i++)
    {
        if(vec[i] == 1) nombreCorrect++;
    }
    return nombreCorrect;
}

bool Adversaire::action(PaquetCartes& pioche, PaquetCartes& piocheFigures, PaquetCartes& defausse, Joueur& ennemi)
{
    //bool boucleWhile = true;
    bool reveleMain = false, peutAssassiner = verifierAssassinat();
    bool peutPerturberRangsEnnemis = verifierPerturberRangsEnnemis(), peutEchangerUnites = verifierEchangerUnites();
    bool possedeDateMaudite = false;

    correctVerifie = verifierFigure();
    if(modeDiagnostic)
    {
        cout << "Donnees a disposition de l'ordinateur:" << endl << endl;

        cout << "Verifier Ordre : ";
        for(unsigned int i = 0; i < 4; i++)
        {
            cout << correctVerifie[i] << ", ";
        }
        cout << endl;
    }
    reveleMain = vecteurVrai(correctVerifie);

    if(!reveleMain)
    {
        correctVerifieDesordre = verifierDesordre();
        if(modeDiagnostic)
        {
            cout << "Verifier Desordre : ";
            for(unsigned int i = 0; i < 4; i++)
            {
                cout << correctVerifieDesordre[i] << ", ";
            }
            cout << endl;
        }
        reveleMain = vecteurVrai(correctVerifieDesordre);
    }

    if(!reveleMain && tete.estJoker())
    {
        correctJoker = verifierJoker();
        if(modeDiagnostic)
        {
            cout << "Verifier Joker Ordre : ";
            for(unsigned int i = 0; i < 4; i++)
            {
                cout << correctJoker[i] << ", ";
            }
            cout << endl;
        }
        if(vecteurVrai(correctJoker) == true) reveleMain = true;
        else
        {
            correctJokerDesordre = verifierJokerDesordre();
            if(modeDiagnostic)
            {
                cout << "Verifier Joker Desordre : ";
                for(unsigned int i = 0; i < 4; i++)
                {
                    cout << correctJokerDesordre[i] << ", ";
                }
                cout << endl;
            }
            if(vecteurVrai(correctJokerDesordre) == true) reveleMain = true;
        }
    }
    if(!reveleMain)
    {
        correctVerifieMaudite = verifierDatesMaudites();
        if(modeDiagnostic)
        {
            cout << "Verifier Maudite Ordre : ";
            for(unsigned int i = 0; i < 4; i++)
            {
                cout << correctVerifieMaudite[i] << ", ";
            }
            cout << endl;
        }
        possedeDateMaudite = vecteurVrai(correctVerifieMaudite);
        if(!possedeDateMaudite)
        {
            correctVerifieMauditeDesordre = verifierDatesMauditesDesordre();
            if(modeDiagnostic)
            {
                cout << "Verifier Maudite Desordre : ";
                for(unsigned int i = 0; i < 4; i++)
                {
                    cout << correctVerifieMauditeDesordre[i] << ", ";
                }
                cout << endl;
            }
            possedeDateMaudite = vecteurVrai(correctVerifieMauditeDesordre);
        }
    }
    if(cooldownSpecial != 0) cooldownSpecial--;
    cout << " 0) Quitter le jeu" << endl;
    cout << " 1) Piocher" << endl;
    if(!defausse.pileVide()) cout << " 2) Recuperer la derniere carte jetee" << endl;
    cout << " 3) Intervertir les cartes visibles" << endl;
    cout << " 4) Intervertir les cartes cachees" << endl;
    cout << " 5) Changer la figure (Changements restants: " << limiteFigure << ")" << endl;
    if(reveleMain || possedeDateMaudite) cout << " 6) Attaque !" << endl;
    if(peutPerturberRangsEnnemis) cout << " 7) Perturbe les rangs ennemis (Cooldown: " << cooldownSpecial << ")!" << endl;
    if(peutEchangerUnites) cout << " 8) Echange une de tes cartes avec ton adversaire (Cooldown: " << cooldownSpecial << ")!" << endl;
    if(peutAssassiner) cout << " 9) Force ton adversaire a jeter une carte (Cooldown: " << cooldownSpecial << ")!" << endl;
    priorite = evaluerPriorite(ennemi);
    cout << " L'ordinateur choisit..." << endl;
    if(modeDiagnostic) cout << "Priorite = " << priorite << endl;
    Sleep(3000);
    choisirAction(pioche, piocheFigures, defausse, ennemi);
    return true;
}

void Adversaire::afficherMain()
{
    for(int i = 0; i < 4; i++)
    {
        if(i >= 2 && cartesCachees) cout << "????";
        else jeu[i].afficher();
        if(i < 3) cout << ", ";
    }
}
