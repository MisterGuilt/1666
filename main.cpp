#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL_ttf.h>


using namespace std;

void EventProcessing(SDL_Rect *ptr_position,SDL_Surface *ptr_screen,SDL_Surface *ptr_rectangle)
{
    int continuer=1;
    SDL_Event event;
    while (continuer)
    {
        SDL_WaitEvent(&event); // On attend un événement qu'on récupère dans event
        switch(event.type) // On teste le type d'événement
        {
            case SDL_QUIT: // Si c'est un événement QUITTER
                continuer = 0; //On met le booléen à 0, donc la boucle va s'arrêter
                break;
            case SDL_KEYDOWN: // Si appui sur une touche
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // Appui sur la touche Echap, on arrête le programme
                        continuer = 0;
                        break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                ptr_position->x = event.button.x;
                ptr_position->y = event.button.y;
                break;
        }
        //SDL_FillRect(ptr_screen, NULL, SDL_MapRGB(ptr_screen->format, 255, 255, 255));
        SDL_BlitSurface(ptr_rectangle, NULL, ptr_screen, ptr_position);
        SDL_Flip(ptr_screen);
    }
}
SDL_Surface SurfaceRect (SDL_Rect *ptr_position,SDL_Surface *ptr_screen){
    int nb_carte=1;
    SDL_Surface *rectangle=NULL;
    for (int i=0;i<nb_carte;i++){
        rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 200, 150, 32, 0, 0, 0, 0);       // Allocation de la surface
        SDL_FillRect(rectangle, NULL, SDL_MapRGB(ptr_screen->format, 150, 206, 255));
        SDL_BlitSurface(rectangle, NULL, ptr_screen, ptr_position);
    }
    return *rectangle;
}

void quit() {
    TTF_Quit();
    SDL_Quit();
}
void init(){
    //SDL_Init(SDL_INIT_VIDEO);
    if (SDL_Init(SDL_INIT_VIDEO) == -1) // Démarrage de la SDL. Si erreur :
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
        exit(EXIT_FAILURE); // On quitte le programme
    }
    SDL_WM_SetIcon(SDL_LoadBMP("joker.bmp"), NULL);
    SDL_WM_SetCaption("****  Jeu de Carte  ****", NULL);
}


int main(int argc, char **argv)
{
    //police = TTF_OpenFont("BlackStreamer.ttf", 25);
    init();
    SDL_Surface *screen=NULL, *maSurface=NULL;
    screen = SDL_SetVideoMode(1100,600,16,SDL_HWSURFACE| SDL_RESIZABLE | SDL_DOUBLEBUF|SDL_FULLSCREEN);
    maSurface = SDL_LoadBMP("royau.bmp");

   if (screen == NULL)      // Si l'ouverture a échoué, on le note et on arrête
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_Rect *positionCarte;

    SDL_Surface *texte = NULL;
    SDL_Rect position3;
    //SDL_Event event;
    TTF_Font *police = NULL;
    SDL_Color couleurBlanche = {255, 255, 255};

    TTF_Init();

    police = TTF_OpenFont("monof56.ttf", 65);           // Chargement de la police
    texte = TTF_RenderText_Blended(police, "Bienvenue sur GRID WARS !", couleurBlanche);      // Écriture du texte dans la SDL_Surface texte en mode Blended (optimal)

    SDL_Rect position;
    position.x = 0;
    position.y = 0;
    SDL_BlitSurface(maSurface, NULL, screen, &position);        // Collage de la surface sur l'écran
   // SDL_BlitSurface(rectangle, NULL, screen, positionCarte);

    SDL_Surface rectangle2= SurfaceRect(positionCarte,screen);
    position3.x = 60;
    position3.y = 370;
    SDL_BlitSurface(texte, NULL, screen, &position3);       // Blit du texte
    SDL_Flip(screen);

    EventProcessing(positionCarte,screen,&rectangle2);

    SDL_FreeSurface(maSurface);
    SDL_FreeSurface(&rectangle2); // Libération de la surface
    TTF_CloseFont(police);          // Doit être avant TTF_Quit()
    quit();
    return EXIT_SUCCESS;
}

