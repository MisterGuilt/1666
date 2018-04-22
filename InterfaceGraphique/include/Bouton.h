#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef BOUTON_H
#define BOUTON_H


class Bouton
{
    public:
        SDL_Rect positionB;
        SDL_Surface *bouton;
    public:
        Bouton();
        ~Bouton();
        SDL_Surface getBouton();
        //setBouton();
    protected:


};

#endif // BOUTON_H


