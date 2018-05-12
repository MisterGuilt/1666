#ifndef CONSTANTES
#define CONSTANTES

#include <iostream>
#include <stdio.h>
#include <vector>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <limits>

#define TYPE_TETES 3
enum{VALET, DAME, ROI}; //Enum avec type int par defaut
enum datesValides
{
    ROICOEUR = 800,
    DAMECOEUR = 1152,
    VALETCOEUR = 1232,
    ROIPIQUE = 481,
    DAMEPIQUE = 657,
    VALETPIQUE = 778,
    ROICARREAU = 996,
    DAMECARREAU = 1491,
    VALETCARREAU = 1357,
    ROITREFLE = 1285,
    DAMETREFLE = 1223,
    VALETTREFLE = 1504,
    DATEJOKER = 1666
};
enum datesMaudites
{
    UN = 1315,
    DEUX = 1415,
    TROIS = 1515,
    QUATRE = 1615,
    CINQ = 1715,
    SIX = 1815,
    SEPT = 1915,
    DIABLE = 1666
};

#define NOMBRE_COULEURS 4
#define CARTE_VIDE -5
enum{JOKER, COEUR, PIQUE, CARREAU, TREFLE};

#endif // CONSTANTES
