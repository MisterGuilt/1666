#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#define POS_TERRAIN_X 150
#define POS_TERRAIN_Y 50
#define TAILLE_TERRAIN 25
#define TAILLE_BOUTON 30

#define TAILLE_SAVE_X 100
#define TAILLE_SAVE_Y 50

#define NB_TERRAINS 3

#ifndef ENUMERATION
#define ENUMERATION
enum territoires{T_INCONNU, T_EAU, T_HERBE};
typedef struct image_fixe
{
    SDL_Surface *img;
    SDL_Rect pos;
}image_fixe;

typedef struct image_fixe_4
{
    SDL_Surface *img;
    SDL_Rect pos_1;//1=haut puis horloge
    SDL_Rect pos_2;
    SDL_Rect pos_3;
    SDL_Rect pos_4;
}image_fixe_4;
#endif // ENUM
