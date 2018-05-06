#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL.h>
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


