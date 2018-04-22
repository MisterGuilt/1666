#include "Bouton.h"




Bouton::Bouton()
{
    this->bouton=SDL_LoadBMP ("play.bmp");
    SDL_SetColorKey(bouton, SDL_SRCCOLORKEY, SDL_MapRGB(bouton->format, 255, 0, 0));
    SDL_SetAlpha(bouton, SDL_SRCALPHA, 130);            // transparence du bouton play
    positionB.x = 150;
    positionB.y = 200;
    //this->conteneurTextures.ajouter("bouton_pas_survole.bmp");
    //this->conteneurTextures.ajouter("bouton_survole.bmp");
    //this->conteneurTextures.ajouter("bouton_enfonce.bmp");
}


SDL_Surface Bouton::getBouton()
{
    return *this->bouton;
}

Bouton::~Bouton()
{
}

