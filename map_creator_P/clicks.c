#include "constantes.h"

int click_bouton(SDL_Rect pos_bouton, SDL_Event event)
{
    if(event.button.x > pos_bouton.x && event.button.y > pos_bouton.y && event.button.x < pos_bouton.x + TAILLE_BOUTON && event.button.y < pos_bouton.y + TAILLE_BOUTON)
        return 1;
    else
        return 0;
}

SDL_Rect enregistre_pos(int abscisse, int ordonnee)
{
    SDL_Rect pos;
    pos.x = abscisse;
    pos.y = ordonnee;
    return pos;
}

int dans_ecart(int valeur, int debut_ecart, int fin_ecart)
{
    if(debut_ecart <= valeur && valeur <= fin_ecart)
        return 1;
    return 0;
}

int dans_ecart_2(int valeur, int debut_ecart, int fin_ecart)
{
    fin_ecart += debut_ecart;
    if(debut_ecart <= valeur && valeur <= fin_ecart)
        return 1;
    return 0;
}

void changer_valeur_case(int** ma_map, int ligne, int colonne, int valeur)
{
    if (valeur == 1)
        *(*(ma_map + ligne) + colonne) = (*(*(ma_map + ligne) + colonne) + 1) % NB_TERRAINS;
    if (valeur == -1)
    {
        *(*(ma_map + ligne) + colonne) = *(*(ma_map + ligne) + colonne) - 1;
        if(*(*(ma_map + ligne) + colonne) < 0)
            *(*(ma_map + ligne) + colonne) = NB_TERRAINS - 1;
    }
}
