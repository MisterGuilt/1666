#include "Cartes.hpp"

using namespace std;

Carte::Carte(int _valeur, int _couleur)
{
    valeur = _valeur;
    couleur = _couleur;
    if(valeur < 10 + VALET)
    {
        points = 0;
        date = 0;
    }
    if(couleur == JOKER)
    {
        points = 0;
        date = DATEJOKER;
    }
    else if(valeur >= 10 + VALET)
    {
        if(valeur == 10 + VALET) points = 4;
        else if(valeur == 10 + DAME) points = 5;
        else if(valeur == 10 + ROI) points = 6;
        switch(couleur)
        {
            case COEUR:
                if(valeur == 10 + VALET) date = VALETCOEUR;
                else if(valeur == 10 + DAME) date = DAMECOEUR;
                else if(valeur == 10 + ROI) date = ROICOEUR;
                break;
            case PIQUE:
                if(valeur == 10 + VALET) date = VALETPIQUE;
                else if(valeur == 10 + DAME) date = DAMEPIQUE;
                else if(valeur == 10 + ROI) date = ROIPIQUE;
                break;
            case CARREAU:
                if(valeur == 10 + VALET) date = VALETCARREAU;
                else if(valeur == 10 + DAME) date = DAMECARREAU;
                else if(valeur == 10 + ROI) date = ROICARREAU;
                break;
            case TREFLE:
                if(valeur == 10 + VALET) date = VALETTREFLE;
                else if(valeur == 10 + DAME) date = DAMETREFLE;
                else if(valeur == 10 + ROI) date = ROITREFLE;
                break;
        }
    }
}

Carte::Carte()
{
    valeur = CARTE_VIDE;
    couleur = CARTE_VIDE;
    date = CARTE_VIDE;
    points = 0;
}

int Carte::getDate()
{
    return date;
}

string Carte::getCouleur()
{
    switch(couleur)
    {
        case 1:
            return "Co";
            break;
        case 2:
            return "P";
            break;
        case 3:
            return "Ca";
            break;
        case 4:
            return "T";
            break;
        default:
            return "Joker";
    }
}

int Carte::getPoints()
{
    return points;
}

int Carte::getValeur()
{
    return valeur;
}

void Carte::afficher()
{
    if(getCouleur() != "Joker")
    {
        switch(valeur)
        {
            case 10 + VALET:
                cout << "V";
                break;
            case 10 + DAME:
                cout << "D";
                break;
            case 10 + ROI:
                cout << "R";
                break;
            default:
                cout << valeur;
        }
    cout << " ";
    }
    cout << getCouleur();
}
