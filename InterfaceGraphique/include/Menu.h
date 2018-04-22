#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <SDL.h>;
#include "Surface.h";
#ifndef MENU_H
#define MENU_H


struct menuElement {
    SDL_Surface* surfaceNormal;
    SDL_Surface* surfaceHover;
};

class Menu
{
    public:
        Menu();

        virtual ~Menu();

    protected:

    private:

};

#endif // MENU_H



