#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "Bouton.h"
#include <string>

#define HAUTEUR 600
#define LARGEUR 1100

using namespace std;

void page_principale(SDL_Surface* screen)
{
    SDL_Surface *bouton_Principale=NULL;
    bouton_Principale=SDL_LoadBMP ("play.bmp");
    SDL_Rect positionB;
    positionB.x = 430;
    positionB.y = 300;
    SDL_SetColorKey(bouton_Principale, SDL_SRCCOLORKEY, SDL_MapRGB(bouton_Principale->format, 255, 0, 0));
    SDL_SetAlpha(bouton_Principale, SDL_SRCALPHA, 200);            // transparence du bouton play

    SDL_Rect *positionCarte=NULL;
    SDL_Surface *texte = NULL;
    TTF_Font *police = NULL;
    SDL_Color couleurBlanche = {255, 255, 255};
    police = TTF_OpenFont("monof56.ttf", 80);           // Chargement de la police
    texte = TTF_RenderText_Blended(police, "Bienvenue sur GRID WARS !", couleurBlanche);      // Écriture du texte dans la SDL_Surface texte en mode Blended (optimal)
    SDL_BlitSurface (bouton_Principale, NULL ,screen, &positionB);
    SDL_BlitSurface (texte, NULL ,screen, positionCarte);

}

void EventProcessing(SDL_Rect *ptr_position,SDL_Surface *ptr_screen)
{
    int continuer=1;
    SDL_Event event;
    //SDL_Surface *maSurface=NULL;
    //maSurface = SDL_LoadBMP("royau.bmp");

    SDL_Rect position3;
    position3.x = 0;
    position3.y = 0;
    while (continuer)
    {
        SDL_Flip(ptr_screen);
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
                    default :
                        break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                ptr_position->x = event.button.x;           ///postion de d'une carte
                ptr_position->y = event.button.y;

                if (event.button.y > 200
                  && event.button.y <= 200+HAUTEUR          // si clic sur boutton
                  && event.button.x > 150
                  && event.button.x <= 150+LARGEUR ){}
                     //SurfaceRect(ptr_position,ptr_screen);
                    //SDL_BlitSurface(maSurface, NULL, ptr_screen, &position3);
                    //SDL_Flip(ptr_screen);
                break;
            default:
                break;

        }
        //SDL_BlitSurface(ptr_rectangle, NULL, ptr_screen, ptr_position);
    }
    //SDL_FreeSurface(maSurface);
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
    TTF_Init();
}

void Bouton (SDL_Surface *ptr_bouton,SDL_Rect *ptr_positionB){

}
void initialiserImageCartes(SDL_Surface ** image_Cartes){
        string nom_Fichier;
        for (int i=0;i<52;i++)
        {
            if (i>=0 && i<=12)
            {
                //carreau
                nom_Fichier="Cartes/"+to_string(i+1)+"_carreau.bmp";
            }
            if (i>=13 && i<=25)
            {
                //coeur
                nom_Fichier=to_string(i-13+1)+"_coeur.bmp";
            }
            if (i>=26 && i<=38)
            {
                //pique
                nom_Fichier=to_string(i-26+1)+"_pique.bmp";
            }
            if (i>=39 && i<=51)
            {
                //trefle
                nom_Fichier=to_string(i-39+1)+"_trefle.bmp";
            }
            image_Cartes[i] = SDL_LoadBMP(nom_Fichier.c_str());
            fprintf(stderr ,"%s:", nom_Fichier.c_str());
            if (image_Cartes[i]==NULL)
            {
                fprintf(stderr ,"le fichier ne s ouvre pas \n");
            }
        }
}

void affichageCartes(SDL_Surface **image_Cartes, SDL_Surface *screen)
{
    SDL_Surface *face_Retourne=NULL;
    SDL_Rect position;
    position.x = 50;
    position.y = 50;
    //SDL_SetColorKey(image_Cartes[2], SDL_SRCCOLORKEY, SDL_MapRGB(image_Cartes[2]->format, 0, 0, 255));    /// transparence
    //SDL_SetAlpha(image_Cartes[2], SDL_SRCALPHA, 255);
    for (int i=0;i<5;i++)       ///joueur 1
    {
        if (i==0)
        {
            SDL_BlitSurface(image_Cartes[10], NULL, screen, &position);
            position.x=position.x+200;
        }
        else if(i==3||i==4)
        {
            face_Retourne = SDL_LoadBMP("Cartes/mystere.bmp");
            SDL_BlitSurface(face_Retourne, NULL, screen, &position);
            position.x=position.x+100;
        }
        else
        {
            SDL_BlitSurface(image_Cartes[i], NULL, screen, &position);
            position.x=position.x+100;
        }

    }
    position.x=300;
    position.y=position.y+180;
    for (int i=0;i<3;i++)   ///pioche, defausse
    {
        if (i==0)
            {
            SDL_BlitSurface(image_Cartes[i], NULL, screen, &position);
            position.x=position.x+190;
            }
        else if(i==1||i==2)
        {
            face_Retourne = SDL_LoadBMP("Cartes/mystere.bmp");
            SDL_BlitSurface(face_Retourne, NULL, screen, &position);
            position.x=position.x+190;
        }
    }
    position.x=950;
    position.y=position.y+180;
    for (int i=0;i<5;i++)
    {
        if (i==0)
        {
            SDL_BlitSurface(image_Cartes[11], NULL, screen, &position);
            position.x=position.x-200;
        }
        else
        {
            SDL_BlitSurface(image_Cartes[i], NULL, screen, &position);      ///joueur 2
            position.x=position.x-100;
        }
    }
    SDL_Flip(screen);
}


int main(int argc, char **argv)
{
    init();
    SDL_Rect position;
    position.x = 0;
    position.y = 0;
    SDL_Surface *screen=NULL;
    SDL_Surface *image_Cartes[52];
    screen = SDL_SetVideoMode(1100,600,16,SDL_HWSURFACE| SDL_RESIZABLE | SDL_DOUBLEBUF|SDL_FULLSCREEN);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 210, 0));

    page_principale(screen);
    EventProcessing(&position,screen);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 210, 0));
    initialiserImageCartes(image_Cartes);
    affichageCartes(image_Cartes,screen);
    EventProcessing(&position,screen);

    if (screen == NULL)      // Si l'ouverture a échoué, on le note et on arrête
    {
        fprintf(stderr, "Impossible de charger le mode vidéo 2  : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }



    //Bouton(bouton, positionB);
    //SDL_BlitSurface(bouton, NULL, screen, &positionB);


    //SDL_BlitSurface(rectangle, NULL, screen, positionCarte);
    //SDL_Surface rectangle2= SurfaceRect(positionCarte,screen);

    //SDL_BlitSurface(maSurface, NULL, screen, &position3);         ///image royaume collage



         //SDL_Surface *rectangle=image_Cartes[i];
        //rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 200, 150, 32, 0, 0, 0, 0);       // Allocation de la surface
        //SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 150, 206, 255));



/*SDL_Surface SurfaceRect (SDL_Rect *ptr_position,SDL_Surface *ptr_screen){
    int nb_carte=1;
    SDL_Surface *rectangle=NULL;
    for (int i=0;i<nb_carte;i++){
        rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 200, 150, 32, 0, 0, 0, 0);       // Allocation de la surface
        SDL_FillRect(rectangle, NULL, SDL_MapRGB(ptr_screen->format, 150, 206, 255));
        SDL_BlitSurface(rectangle, NULL, ptr_screen, ptr_position);
    }
    return *rectangle;
}*/


    //SDL_FreeSurface(&rectangle2); // Libération de la surface


    //TTF_CloseFont(police);          // Doit être avant TTF_Quit()
    quit();
    return EXIT_SUCCESS;
}

