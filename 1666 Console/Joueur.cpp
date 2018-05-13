#include "Joueur.hpp"

using namespace std;

Joueur::Joueur(PaquetCartes& pioche, PaquetCartes& figures) : tete(), points(0), limiteFigure(2), cooldownSpecial(0), figuresGagnees()
{
    for(int i = 0; i < 4; i++) //Piocher 4 chiffres
    {
        jeu[i] = pioche.enleverCarteDessus();
    }
    tete = figures.enleverCarteDessus(); //Piocher une figure
}

vector<int> Joueur::verifierFigure()
{
    vector<int> correctVerifie;
    correctVerifie.push_back(0);
    correctVerifie.push_back(0);
    correctVerifie.push_back(0);
    correctVerifie.push_back(0);
    int dateTeteBase = tete.getDate();
    vector<int> dateJoueur;
    vector<int> dateTete;
    for(int i = 0; i < 4; i++) //Decomposition inverse
    {
        dateJoueur.push_back(jeu[i].getValeur()); //Non inverse
        dateTete.push_back(dateTeteBase % 10); //Inverse
        dateTeteBase = (dateTeteBase - (dateTeteBase % 10))/10;
    }
    for(int i = dateTete.size() - 1; i >=0; i--) //Remplit le vecteur de validite. Utile a l'IA pour savoir quelles cartes sont correctes.
    //Si seulement la premiere carte est correcte, le vecteur contiendra 1000
    //Si la main est correcte, le vecteur contiendra 1111
    {
        if(dateTete[i] == dateJoueur[3 - i]) correctVerifie[3 - i] = 1;
    }
    return correctVerifie;
}

vector<int> Joueur::verifierDesordre()
{
    vector<int> correctVerifieDesordre;
    correctVerifieDesordre.push_back(0);
    correctVerifieDesordre.push_back(0);
    correctVerifieDesordre.push_back(0);
    correctVerifieDesordre.push_back(0);
    int dateTeteBase = tete.getDate();
    vector<int> dateJoueur;
    vector<int> dateTete;
    for(int i = 0; i < 4; i++) //Decomposition inverse
    {
        dateJoueur.push_back(jeu[i].getValeur());
        dateTete.push_back(dateTeteBase % 10);
        dateTeteBase = (dateTeteBase - (dateTeteBase % 10))/10;
    }
    for(int i = dateTete.size() - 1; i >=0; i--) //On commence par verifier le premier chiffre de la figure, mais comme la decomposition est a l'envers on commence par la fin du vecteur
    {
        for(int j = 0; j < (int)dateJoueur.size(); j++)
        {
            if(dateTete[i] == dateJoueur[j])
            {
                dateTete[i] = -1;
                dateJoueur[j] = -1;
                correctVerifieDesordre[j] = 1;
                break;
            }
        }
    }
    return correctVerifieDesordre;
}

vector<int> Joueur::verifierDatesMaudites()
{
    ListeDates valides(1);
    vector<int> correctVerifieMaudite;
    vector<int> tmp;
    int dateMauditeBase;
    vector<int> dateJoueur;
    vector<int> dateTete;
    int record = 0;
    int nombreValide = 0;
    for(int i = 0; valides.getNombreDates(); i++) //On itere sur la liste des dates maudites. Elle se reduit a chaque appel pour donner l'element suivant au prochain
    {
        tmp.push_back(0);
        tmp.push_back(0);
        tmp.push_back(0);
        tmp.push_back(0);
        nombreValide = 0;
        dateMauditeBase = valides.getDate();
        tmp.push_back(dateMauditeBase);
        for(int j = 0; j < 4; j++) //Decomposition inverse
        {
            dateJoueur.push_back(jeu[j].getValeur());
            dateTete.push_back(dateMauditeBase % 10);
            dateMauditeBase = (dateMauditeBase - (dateMauditeBase % 10))/10;
        }
        for(int j = dateTete.size() - 1; j >= 0; j--)
        {
            if(dateTete[j] == dateJoueur[3 - j])
            {
                tmp[3 - j] = 1;
                nombreValide++;
            }
        }
        if(nombreValide != 0 && nombreValide >= record) //On cumule les meilleurs resultats
        {
            if(nombreValide > record) //Nouveau record, on ignore les resultats precedents
            {
                record = nombreValide;
                if(correctVerifieMaudite.empty() == false) correctVerifieMaudite.clear();
            }
            correctVerifieMaudite.insert(correctVerifieMaudite.end(), tmp.begin(), tmp.end());
        }
        tmp.clear();
        dateJoueur.clear();
        dateTete.clear();
    }
    if(correctVerifieMaudite.empty())
    {
        correctVerifieMaudite.push_back(0);
        correctVerifieMaudite.push_back(0);
        correctVerifieMaudite.push_back(0);
        correctVerifieMaudite.push_back(0);
    }
    return correctVerifieMaudite;
}
vector<int> Joueur::verifierDatesMauditesDesordre()
{
    ListeDates valides(1);
    vector<int> correctVerifieMauditeDesordre;
    vector<int> tmp;
    int dateMauditeBase = tete.getDate();
    vector<int> dateJoueur;
    vector<int> dateTete;
    int record = 0;
    int nombreValide = 0;
    for(int i = 0; valides.getNombreDates(); i++) //On itere sur la liste des dates maudites. Elle se reduit a chaque appel pour donner l'element suivant au prochain
    {
        tmp.push_back(0);
        tmp.push_back(0);
        tmp.push_back(0);
        tmp.push_back(0);
        nombreValide = 0;
        dateMauditeBase = valides.getDate();
        tmp.push_back(dateMauditeBase);
        for(int j = 0; j < 4; j++) //Decomposition inverse
        {
            dateJoueur.push_back(jeu[j].getValeur());
            dateTete.push_back(dateMauditeBase % 10);
            dateMauditeBase = (dateMauditeBase - (dateMauditeBase % 10))/10;
        }
        for(int j = dateTete.size() - 1; j >=0; j--) //On commence par verifier le premier chiffre, mais comme la decomposition est a l'envers on commence par la fin du vecteur
        {
            for(int k = 0; k < (int)dateJoueur.size(); k++)
            {
                if(dateTete[j] == dateJoueur[k])
                {
                    tmp[k] = 1;
                    nombreValide++;
                    dateTete[j] = -1;
                    dateJoueur[k] = -1;
                    break;
                }
            }
        }
        if(nombreValide != 0 && nombreValide >= record) //On cumule les meilleurs resultats
        {
            if(nombreValide > record) //Nouveau record, on ignore les resultats precedents
            {
                record = nombreValide;
                if(correctVerifieMauditeDesordre.empty() == false) correctVerifieMauditeDesordre.clear();
            }
            correctVerifieMauditeDesordre.insert(correctVerifieMauditeDesordre.end(), tmp.begin(), tmp.end());
        }
        tmp.clear();
        dateJoueur.clear();
        dateTete.clear();
    }
    if(correctVerifieMauditeDesordre.empty())
    {
        correctVerifieMauditeDesordre.push_back(0);
        correctVerifieMauditeDesordre.push_back(0);
        correctVerifieMauditeDesordre.push_back(0);
        correctVerifieMauditeDesordre.push_back(0);
    }
    return correctVerifieMauditeDesordre;
}

vector<int> Joueur::verifierDateDiableDesordre()
{
    vector<int> correctVerifieDiableDesordre;
    correctVerifieDiableDesordre.push_back(0);
    correctVerifieDiableDesordre.push_back(0);
    correctVerifieDiableDesordre.push_back(0);
    correctVerifieDiableDesordre.push_back(0);
    int dateMauditeBase = DIABLE;
    vector<int> dateJoueur;
    vector<int> dateTete;
    for(int i = 0; i < 4; i++) //Decomposition inverse
    {
        dateJoueur.push_back(jeu[i].getValeur());
        dateTete.push_back(dateMauditeBase % 10);
        dateMauditeBase = (dateMauditeBase - (dateMauditeBase % 10))/10;
    }
    for(int i = dateTete.size() - 1; i >=0; i--) //On commence par verifier le premier chiffre de la figure, mais comme la decomposition est a l'envers on commence par la fin du vecteur
    {
        for(int j = 0; j < (int)dateJoueur.size(); j++)
        {
            if(dateTete[i] == dateJoueur[j])
            {
                dateTete[i] = -1;
                dateJoueur[j] = -1;
                correctVerifieDiableDesordre[j] = 1;
                break;
            }
        }
    }
    return correctVerifieDiableDesordre;
}

vector<int> Joueur::verifierJoker() //Verifie si on a une date normale avec le joker (qui peut correspondre a n'importe quelle figure)
{
    ListeDates valides(0);
    vector<int> correctVerifieJoker;
    vector<int> tmp;
    int dateTeteBase;
    vector<int> dateJoueur;
    vector<int> dateTete;
    int record = 0;
    int nombreValide = 0;
    for(int i = 0; valides.getNombreDates(); i++) //On itere sur la liste des dates maudites. Elle se reduit a chaque appel pour donner l'element suivant au prochain
    {
        tmp.push_back(0);
        tmp.push_back(0);
        tmp.push_back(0);
        tmp.push_back(0);
        nombreValide = 0;
        dateTeteBase = valides.getDate();
        tmp.push_back(dateTeteBase);
        for(int j = 0; j < 4; j++) //Decomposition inverse
        {
            dateJoueur.push_back(jeu[j].getValeur());
            dateTete.push_back(dateTeteBase % 10);
            dateTeteBase = (dateTeteBase - (dateTeteBase % 10))/10;
        }
        for(int j = dateTete.size() - 1; j >= 0; j--)
        {
            if(dateTete[j] == dateJoueur[3 - j])
            {
                tmp[3 - j] = 1;
                nombreValide++;
            }
        }
        if(nombreValide != 0 && nombreValide >= record) //On cumule les meilleurs resultats
        {
            if(nombreValide > record) //Nouveau record, on ignore les resultats precedents
            {
                record = nombreValide;
                if(correctVerifieJoker.empty() == false) correctVerifieJoker.clear();
            }
            correctVerifieJoker.insert(correctVerifieJoker.end(), tmp.begin(), tmp.end());
        }
        tmp.clear();
        dateJoueur.clear();
        dateTete.clear();
    }
    if(correctVerifieJoker.empty())
    {
        correctVerifieJoker.push_back(0);
        correctVerifieJoker.push_back(0);
        correctVerifieJoker.push_back(0);
        correctVerifieJoker.push_back(0);
    }
    return correctVerifieJoker;
}

vector<int> Joueur::verifierJokerDesordre()
{
    ListeDates valides(0);
    vector<int> correctVerifieJokerDesordre;
    vector<int> tmp;
    int dateTeteBase = tete.getDate();
    vector<int> dateJoueur;
    vector<int> dateTete;
    int record = 0;
    int nombreValide = 0;
    for(int i = 0; valides.getNombreDates(); i++) //On itere sur la liste des dates maudites. Elle se reduit a chaque appel pour donner l'element suivant au prochain
    {
        tmp.push_back(0);
        tmp.push_back(0);
        tmp.push_back(0);
        tmp.push_back(0);
        nombreValide = 0;
        dateTeteBase = valides.getDate();
        tmp.push_back(dateTeteBase);
        for(int j = 0; j < 4; j++) //Decomposition inverse
        {
            dateJoueur.push_back(jeu[j].getValeur());
            dateTete.push_back(dateTeteBase % 10);
            dateTeteBase = (dateTeteBase - (dateTeteBase % 10))/10;
        }
        for(int j = dateTete.size() - 1; j >=0; j--) //On commence par verifier le premier chiffre, mais comme la decomposition est a l'envers on commence par la fin du vecteur
        {
            for(int k = 0; k < (int)dateJoueur.size(); k++)
            {
                if(dateTete[j] == dateJoueur[k])
                {
                    tmp[k] = 1;
                    nombreValide++;
                    dateTete[j] = -1;
                    dateJoueur[k] = -1;
                    break;
                }
            }
        }
        if(nombreValide != 0 && nombreValide >= record) //On cumule les meilleurs resultats
        {
            if(nombreValide > record) //Nouveau record, on ignore les resultats precedents
            {
                record = nombreValide;
                if(correctVerifieJokerDesordre.empty() == false) correctVerifieJokerDesordre.clear();
            }
            correctVerifieJokerDesordre.insert(correctVerifieJokerDesordre.end(), tmp.begin(), tmp.end());
        }
        tmp.clear();
        dateJoueur.clear();
        dateTete.clear();
    }
    if(correctVerifieJokerDesordre.empty())
    {
        correctVerifieJokerDesordre.push_back(0);
        correctVerifieJokerDesordre.push_back(0);
        correctVerifieJokerDesordre.push_back(0);
        correctVerifieJokerDesordre.push_back(0);
    }
    return correctVerifieJokerDesordre;
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
    tete = c;
    limiteFigure--;
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

int Joueur::getDateEnMain()
{
    return jeu[0].getValeur()*1000 + jeu[1].getValeur()*100 + jeu[2].getValeur()*10 + jeu[3].getValeur();
}

void Joueur::revelerJeu(PaquetCartes& pioche, PaquetCartes& piocheFigures, Joueur& ennemi) //Lorsque le joueur a une main valide il peut invoquer cette fonction
{
    if(tete.estJoker())
    {
        if(vecteurVrai(verifierFigure()))
        {
            points += 100; //Gain de la partie
            piocheFigures.viderPaquet();
        }
        else if(vecteurVrai(verifierDesordre()))
        {
            ennemi.soitMaudit(false, true);
            figuresGagnees.push_back(tete);
        }
    }
    else if(!tete.estJoker())
    {
        if(vecteurVrai(verifierFigure())) points += tete.getPoints();
        else if(vecteurVrai(verifierDesordre())) points += tete.getPoints() - 3;
        figuresGagnees.push_back(tete);
    }
    else if(vecteurVrai(verifierDatesMaudites()))
    {
        if(getDateEnMain() == DIABLE)
            ennemi.soitMaudit(true, true);
        else
            ennemi.soitMaudit(true, false);
    }
    else if(vecteurVrai(verifierDatesMauditesDesordre()))
    {
        if(getDateEnMain() == DIABLE)
            ennemi.soitMaudit(false, true);
        else
            ennemi.soitMaudit(false, false);
    }
    tete = piocheFigures.enleverCarteDessus();
    changerJeu(pioche);
    limiteFigure++;
}

bool Joueur::action(PaquetCartes& pioche, PaquetCartes& piocheFigures, PaquetCartes& defausse, Joueur& ennemi)
{
    int choix;
    bool boucleWhile = true;
    bool reveleMain = false, peutAssassiner = verifierAssassinat();
    bool peutPerturberRangsEnnemis = verifierPerturberRangsEnnemis(), peutEchangerUnites = verifierEchangerUnites();
    bool possedeDateMaudite = false;
    reveleMain = vecteurVrai(verifierFigure());
    if(!reveleMain) reveleMain = vecteurVrai(verifierDesordre());
    if(!reveleMain && tete.estJoker())
    {
        if(vecteurVrai(verifierJoker()) == true) reveleMain = true;
        else if(vecteurVrai(verifierJokerDesordre()) == true) reveleMain = true;
    }
    if(!reveleMain)
    {
        possedeDateMaudite = vecteurVrai(verifierDatesMaudites());
        if(!possedeDateMaudite) possedeDateMaudite = vecteurVrai(verifierDatesMauditesDesordre());
    }
    if(cooldownSpecial != 0) cooldownSpecial--;
    do
    {
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
        cout << " Que faire ? ";
        choix = saisie();
        if(choix >= 0 && choix <= 5) boucleWhile = false;
        if(choix == 2 && defausse.pileVide()) boucleWhile = true;
        if(choix == 5 && limiteFigure == 0) boucleWhile = true;
        if(choix == 6 && (reveleMain || possedeDateMaudite)) boucleWhile = false;
        if(choix == 7 && peutPerturberRangsEnnemis && cooldownSpecial == 0) boucleWhile = false;
        if(choix == 8 && peutEchangerUnites && cooldownSpecial == 0) boucleWhile = false;
        if(choix == 9 && peutAssassiner && cooldownSpecial == 0) boucleWhile = false;
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
    if(tete.getDate() < 1000) cout << " 0";
    else cout << " ";
    cout << tete.getDate();
}

int Joueur::getPoints()
{
    return points;
}

Carte Joueur::getCarte(int numero)
{
    return jeu[numero];
}

void Joueur::changerCarte(int numero, Carte nouvelle)
{
    jeu[numero] = nouvelle;
}

void Joueur::changerFigure(Carte nouvelle)
{
    tete = nouvelle;
}

void Joueur::echangerCarteDansMain(int numero1, int numero2)
{
    Carte temporaire = jeu[numero1];
    jeu[numero1] = jeu[numero2];
    jeu[numero2] = temporaire;
}

void Joueur::soitMaudit(bool ordre, bool diable)
{
    if(!diable)
    {
        if(ordre) points -= 5;
        else points -= 3;
    }
    else
    {
        if(ordre) points -= 7;
        else points -= 5;
    }
}

int Joueur::nombreCartesMemeCouleur(int couleur)
{
    int nombreCarteValides = 0;
    for(int i = 0; i < 4; i++)
    {
        if(jeu[i].getCouleurValeurNumerique() == couleur) nombreCarteValides++;
    }
    return nombreCarteValides;
}

bool Joueur::verifierPerturberRangsEnnemis() //Change de place deux cartes dans le jeu adverse. Necessite 3 couleurs identiques
{
    if(nombreCartesMemeCouleur(COEUR) >= 3) return true; //changer de place une carte dans le jeu adverse
    if(nombreCartesMemeCouleur(PIQUE) >= 3) return true;
    if(nombreCartesMemeCouleur(CARREAU) >= 3) return true;
    if(nombreCartesMemeCouleur(TREFLE) >= 3) return true;

    return false;
}

bool Joueur::verifierEchangerUnites() //Echange une carte de son jeu avec l'ennemi. Necessite un valet et deux cartes de couleur correspondante
{
    if(tete.getValeur() == 10 + VALET)
    {
        if(tete.getCouleurValeurNumerique() == COEUR && nombreCartesMemeCouleur(COEUR) >= 2) return true;
        if(tete.getCouleurValeurNumerique() == PIQUE && nombreCartesMemeCouleur(PIQUE) >= 2) return true;
        if(tete.getCouleurValeurNumerique() == CARREAU && nombreCartesMemeCouleur(CARREAU) >= 2) return true;
        if(tete.getCouleurValeurNumerique() == TREFLE && nombreCartesMemeCouleur(TREFLE) >= 2) return true;
    }
    return false;
}

bool Joueur::verifierAssassinat() //Defausse une carte chiffre de l'adversaire. Necessite deux paires de couleurs
{
    if(nombreCartesMemeCouleur(COEUR) == 2)
    {
        if(nombreCartesMemeCouleur(PIQUE) == 2) return true;
        if(nombreCartesMemeCouleur(CARREAU) == 2) return true;
        if(nombreCartesMemeCouleur(TREFLE) == 2) return true;
    }
    if(nombreCartesMemeCouleur(PIQUE) == 2)
    {
        if(nombreCartesMemeCouleur(COEUR) == 2) return true;
        if(nombreCartesMemeCouleur(CARREAU) == 2) return true;
        if(nombreCartesMemeCouleur(TREFLE) == 2) return true;
    }
    if(nombreCartesMemeCouleur(CARREAU) == 2)
    {
        if(nombreCartesMemeCouleur(COEUR) == 2) return true;
        if(nombreCartesMemeCouleur(PIQUE) == 2) return true;
        if(nombreCartesMemeCouleur(TREFLE) == 2) return true;
    }
    if(nombreCartesMemeCouleur(TREFLE) == 2)
    {
        if(nombreCartesMemeCouleur(COEUR) == 2) return true;
        if(nombreCartesMemeCouleur(PIQUE) == 2) return true;
        if(nombreCartesMemeCouleur(CARREAU) == 2) return true;
    }
    return false;
}

void Joueur::perturberRangsEnnemis(Joueur& ennemi)
{
    int carte1, carte2;
    do
    {
        cout << "Quelle carte voulez-vous deplacer (0 a 3) ? ";
        cin >> carte1;
    }while(carte1 > 3 || carte1 < 0);
    do
    {
        cout << "A la place de quelle carte (0 a 3) ? ";
        cin >> carte2;
    }while(carte2 > 3 || carte2 < 0 || carte2 == carte1);

    Carte c = ennemi.getCarte(carte1);
    ennemi.changerCarte(carte1, ennemi.getCarte(carte2));
    ennemi.changerCarte(carte2, c);
    cooldownSpecial = 3;
}

void Joueur::echangerUnites(Joueur& ennemi)
{
    int carte1, carte2;
    do
    {
        cout << "Quelle carte voulez-vous obtenir (0 a 3) ? ";
        cin >> carte1;
    }while(carte1 > 3 || carte1 < 0);
    cout << "La carte " << carte1 << " sera recuperee." << endl;
    do
    {
        cout << "Quelle carte voulez-vous donner (0 a 3) ? ";
        cin >> carte2;
    }while(carte2 > 3 || carte2 < 0);

    Carte c = ennemi.getCarte(carte1);
    ennemi.changerCarte(carte1, jeu[carte2]);
    jeu[carte2] = c;
    cooldownSpecial = 3;
}

void Joueur::assassinat(Joueur& ennemi, PaquetCartes& pioche, PaquetCartes& defausse)
{
    int carte;
    do
    {
        cout << "Quelle carte voulez-vous jeter (0 a 3) ? ";
        cin >> carte;
    }while(carte > 3 || carte < 0);

    defausse.ajouterCarteDessus(ennemi.getCarte(carte));
    ennemi.changerCarte(carte, pioche.enleverCarteDessus());
    cooldownSpecial = 3;
}

bool Joueur::vecteurVrai(vector<int> vec)
{
    for(unsigned int i = 0; i < vec.size(); i++)
    {
        if(vec[i] == 0) return false;
    }
    return true;
}
