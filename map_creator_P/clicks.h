#include "constantes.h"

int click_bouton(SDL_Rect pos_bouton, SDL_Event event);

SDL_Rect enregistre_pos(int abscisse, int ordonnee);

int dans_ecart(int valeur, int debut_ecart, int fin_ecart);

int dans_ecart_2(int valeur, int debut_ecart, int fin_ecart);

void changer_valeur_case(int** ma_map, int ligne, int colonne, int valeur);
