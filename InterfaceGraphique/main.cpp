#include <iostream>
#include <sstream>
#include <stdlib.h>
//#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include <string>
#define HAUTEUR 600
#define LARGEUR 1100



using namespace std;

void main_du_joueur(int * ,int *,int *, int *,int *);
void initialiserImageCartes(SDL_Surface **);
void affichageCartes(SDL_Surface **,SDL_Rect *, SDL_Surface *,int *,int *, int *);
void affichage_Plateau(SDL_Surface *);
int page_principale_processing(SDL_Rect *,SDL_Surface*, int*, int*,int*, int*);

int page_principale(SDL_Surface* screen,int event2)
{
    //int event;        ///si on click sur un bouton on change d'image
    SDL_Rect position_B2;
    position_B2.x=0;
    position_B2.y=0;
    SDL_Surface *bouton_Principal=NULL;
    SDL_Surface *bouton_Exit=NULL;
    if (event2 ==1){
        bouton_Principal=SDL_LoadBMP ("play2.bmp");
        SDL_SetColorKey(bouton_Principal, SDL_SRCCOLORKEY, SDL_MapRGB(bouton_Principal->format, 255, 201, 14));
    }
    else
    {
        //SDL_FreeSurface(&bouton_Principal);
        bouton_Principal=SDL_LoadBMP ("play.bmp");
        SDL_SetColorKey(bouton_Principal, SDL_SRCCOLORKEY, SDL_MapRGB(bouton_Principal->format, 255, 174, 201));
    }

    SDL_Rect positionB;                      //affichage de l'image de fond sur l'ecran de démarrage du jeu
    SDL_Surface *maSurface=NULL;
    maSurface = SDL_LoadBMP("royau.bmp");
    SDL_BlitSurface (maSurface, NULL ,screen, &position_B2);
    positionB.x = 0;
    positionB.y = 0;

    bouton_Exit=SDL_LoadBMP ("Exit.bmp");
    positionB.x = 50;
    positionB.y = 190;
    SDL_SetColorKey(bouton_Exit, SDL_SRCCOLORKEY, SDL_MapRGB(bouton_Principal->format, 255, 127, 39));  ///transparence bouton de jeu


    SDL_Rect position_Titre;
    position_Titre.x= 150;
    SDL_Surface *texte = NULL;
    TTF_Font *police = NULL;
    SDL_Color couleurBlanche = {255, 255, 255};
    police = TTF_OpenFont("monof56.ttf", 80);           // Chargement de la police
    texte = TTF_RenderText_Blended(police, "Bienvenue sur 1666 !", couleurBlanche);      // Écriture du texte dans la SDL_Surface texte en mode Blended (optimal)
    SDL_BlitSurface (bouton_Principal, NULL ,screen, &positionB);
    positionB.x = 50;
    positionB.y = 320;
    SDL_BlitSurface (bouton_Exit, NULL ,screen, &positionB);
    SDL_BlitSurface (texte, NULL ,screen, &position_Titre);
    //EventProcessing(&position,screen);
    SDL_Flip(screen);

        return 1;
}
int random_Card(int index,int *cpt)     //ca genere une carte aléatoirement
{
    int j;
    /*j=rand()%10+1;*/
   static int tab[50];
   static int first = 0;
   if (first == 0)
       {
          int i;
          srand (time (NULL));
          for (i = 0; i < 50; i++)
          {
                tab[i] =rand()%51+1;
          }
          first = 1;
       }
   //index = (int)(rand() / RAND_MAX * (50 - 1));
    do
        {
            j = tab[index+(*cpt)];
            index=index+1;
        }    while (j==10||j==11||j==12||j==23||j==24||j==25||j==36||j==37||j==38||j==49||j==50||j==51);
   //tab[index] = rand();
   return j;
}
int random_Card_Figure(int index,int *cpt)     //ca genere une carte aléatoirement
{
    int j;
    /*j=rand()%10+1;*/
   static int tab[50];
   static int first = 0;
   if (first == 0)
       {
          int i;
          srand (time (NULL));
          for (i = 0; i < 50; i++)
          {
                tab[i] =rand()%51+1;
          }
          first = 1;
       }
   //index = (int)(rand() / RAND_MAX * (50 - 1));
   int ok=0;
    do
        {
            j = tab[index+(*cpt)];
            index=index+1;
           if  (j==10||j==11||j==12||j==23||j==24||j==25||j==36||j==37||j==38||j==49||j==50||j==51)
           {
                ok=1;
           }
        } while (ok==0);
   return j;
}

int EventProcessing(SDL_Rect *ptr_position,SDL_Surface *ptr_screen,int *carte_precedente,int *carte_actuel,int *carte_pioche, int *tour)
{

    SDL_Surface *texte_Cpt_NbTour;
    TTF_Font *police3 = NULL;
    police3 = TTF_OpenFont("monof55.ttf", 24);           // Chargement de la police
    SDL_Rect position_cpt_NbTour;
    position_cpt_NbTour.x=240;
    position_cpt_NbTour.y=420;
    ostringstream oss;
    int switch1=0;

    SDL_Surface *image_Cartes[52];
    initialiserImageCartes(image_Cartes);
    int continuer=1;
    SDL_Event event;
    int continuerTour=1;
    affichage_Plateau(ptr_screen);
    affichageCartes(image_Cartes,ptr_position, ptr_screen, carte_precedente, carte_actuel, tour);
    texte_Cpt_NbTour = TTF_RenderText_Blended(police3, oss.str().c_str(),  {255, 255, 255});
    oss<<"Tour : "<<(*tour);
    texte_Cpt_NbTour = TTF_RenderText_Blended(police3, oss.str().c_str(),  {255, 255, 255});
    SDL_BlitSurface (texte_Cpt_NbTour, NULL ,ptr_screen, &position_cpt_NbTour);
    while (continuer)
    {
        SDL_WaitEvent(&event); // On attend un événement qu'on récupère dans event
        switch(event.type) // On teste le type d'événement
        {
            case SDL_QUIT: // Si c'est un événement QUITTER
                //continuer = 0; //On met le booléen à 0, donc la boucle va s'arrêter
                return 0;
                break;
            case SDL_KEYDOWN: // Si appui sur une touche
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // Appui sur la touche Echap, on arrête le programme
                        return 0;
                        break;
                    case SDLK_s:
                        ptr_position->x=0;
                        ptr_position->y=0;
                        while (continuer)
                        {
                            continuer=page_principale_processing(ptr_position,ptr_screen,carte_precedente,carte_actuel,carte_pioche,tour);
                        }
                        //return 0;
                        break;
                    default :
                        break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                ptr_position->x = event.button.x;           ///postion de d'une carte
                ptr_position->y = event.button.y;
// si clic sur boutton
                if (event.button.y > 20 && event.button.y <= 50  && event.button.x > 1000 && event.button.x <= 1090)    //bouton arrrêt
                    {
                        //SDL_Delay(500);
                        return 0;
                        //continuer = 0;
                    }
                while (continuerTour)
                    {
                        continuerTour=1;
                        SDL_WaitEvent(&event);
                        ptr_position->x = event.button.x;
                        ptr_position->y = event.button.y;
                        if(event.type == SDL_MOUSEBUTTONUP)//SDL_MOUSEMOTION)
                        {
                            if (SDL_MOUSEBUTTONUP&&(ptr_position->x>750&&ptr_position->x<820&&ptr_position->y>410&&ptr_position->y<530))   ///le joueur a cliqué sur la carte à jouer
                            {
                                *tour=1;
                                switch1=0;
                                //oss<<"Tour : "<<(*tour);
                                //texte_Cpt_NbTour = TTF_RenderText_Blended(police3, oss.str().c_str(),  {255, 255, 255});
                                SDL_BlitSurface (texte_Cpt_NbTour, NULL ,ptr_screen, &position_cpt_NbTour);
                                main_du_joueur(carte_precedente, carte_actuel, carte_pioche, tour,&switch1);
                                affichageCartes(image_Cartes,ptr_position,  ptr_screen, carte_precedente, carte_actuel, tour);
                                //SDL_Flip(ptr_screen);
                                SDL_PollEvent(&event);
                                continuerTour=0;
                            }
                            else if (SDL_MOUSEBUTTONUP&&(ptr_position->x>650&&ptr_position->x<745&&ptr_position->y>410&&ptr_position->y<530))
                            {
                                *tour=1;
                                switch1=1;
                                //oss<<"Tour : "<<(*tour);
                                //texte_Cpt_NbTour = TTF_RenderText_Blended(police3, oss.str().c_str(),  {255, 255, 255});
                                SDL_BlitSurface (texte_Cpt_NbTour, NULL ,ptr_screen, &position_cpt_NbTour);
                                main_du_joueur(carte_precedente, carte_actuel, carte_pioche, tour,&switch1);
                                affichageCartes(image_Cartes,ptr_position,  ptr_screen, carte_precedente, carte_actuel, tour);
                                //SDL_Flip(ptr_screen);
                                continuerTour=0;
                            }
                            else if (SDL_MOUSEBUTTONUP&&(ptr_position->x>930&&ptr_position->x<1050&&ptr_position->y>410&&ptr_position->y<530))
                            {
                                *tour=1;
                                switch1=2;
                                SDL_BlitSurface (texte_Cpt_NbTour, NULL ,ptr_screen, &position_cpt_NbTour);
                                main_du_joueur(carte_precedente, carte_actuel, carte_pioche, tour,&switch1);
                                affichageCartes(image_Cartes,ptr_position,  ptr_screen, carte_precedente, carte_actuel, tour);
                                continuerTour=0;
                            }
                            else if (ptr_position->x>930&&ptr_position->x<1050&&ptr_position->y>20&&ptr_position->y<100)
                            {
                                continuerTour=1;
                            }
                        }
                        //SDL_PollEvent(&event);
                        SDL_Flip(ptr_screen);
                    }
                    break;
            default :
                break;
            }
            continuerTour=1;
        }
    return 1;
}



void affichage_Plateau(SDL_Surface *screen)
{
    SDL_Surface *bouton_Exit2=NULL;
    bouton_Exit2=SDL_LoadBMP ("Exit2.bmp");
    SDL_Rect positionB2;
    positionB2.x=1030;
    positionB2.y=20;

    SDL_Surface *bouton_Date=NULL;
    bouton_Date=SDL_LoadBMP ("date.bmp");
    SDL_Rect position_Date;
    position_Date.x=980;
    position_Date.y=20;

    SDL_Rect position_texte_menu;
    position_texte_menu.x=920;
    position_texte_menu.y=120;
    SDL_Surface *texte_Menu=NULL;
    TTF_Font *police2 = NULL;
    police2 = TTF_OpenFont("monof55.ttf", 40);           // Chargement de la police
    texte_Menu= TTF_RenderText_Blended(police2, "SCORE : ",  {255, 255, 255});

    SDL_SetColorKey(bouton_Date, SDL_SRCCOLORKEY, SDL_MapRGB(bouton_Date->format, 255, 201, 14));
    //SDL_SetColorKey(bouton_Exit, SDL_SRCCOLORKEY, SDL_MapRGB(bouton_Principal->format, 255, 127, 39));
    SDL_SetAlpha(bouton_Exit2, SDL_SRCALPHA, 220);            // transparence du bouton play
    SDL_SetAlpha(bouton_Date, SDL_SRCALPHA, 240);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 210, 0));
    SDL_BlitSurface (bouton_Exit2, NULL ,screen, &positionB2);
    SDL_BlitSurface (bouton_Date, NULL ,screen, &position_Date);

    SDL_Rect position_Rect;
    position_Rect.x=910;
    position_Rect.y=110;
    SDL_Surface *rectangle=NULL;
    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 180, 210, 32, 0, 0, 0, 0);       // Allocation de la surface
    SDL_FillRect(rectangle, NULL, SDL_MapRGB(screen->format, 160, 0, 80));
    SDL_BlitSurface(rectangle, NULL, screen, &position_Rect);
    SDL_BlitSurface (texte_Menu, NULL ,screen, &position_texte_menu);

}


void quit()
{
    TTF_Quit();
    SDL_Quit();
}

void init()
{
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
                nom_Fichier="Cartes/"+to_string(i-13+1)+"_coeur.bmp";
            }
            if (i>=26 && i<=38)
            {
                //pique
                nom_Fichier="Cartes/"+to_string(i-26+1)+"_pique.bmp";
            }
            if (i>=39 && i<=51)
            {
                //trefle
                nom_Fichier="Cartes/"+to_string(i-39+1)+"_trefle.bmp";
            }
            image_Cartes[i] = SDL_LoadBMP(nom_Fichier.c_str());
            fprintf(stderr ,"%s:", nom_Fichier.c_str());
            if (image_Cartes[i]==NULL)
            {
                fprintf(stderr ,"le fichier ne s ouvre pas \n");
            }
        }
}


void affichageCartes(SDL_Surface **image_Cartes, SDL_Rect *pos, SDL_Surface *screen, int *carte_precedente,int *carte_actuel,int *tour)
{
    SDL_Surface *texte_pioche[3];
    SDL_Surface *face_Retourne=NULL;
    SDL_Rect position;
    position.x = 50;
    position.y = 50;
    TTF_Font *police2 = NULL;
    SDL_Rect position_pioche;
    police2 = TTF_OpenFont("monof56.ttf", 18);           // Chargement de la police
    texte_pioche[0] = TTF_RenderText_Blended(police2, "Pioche",  {0, 0, 0});
    texte_pioche[1] = TTF_RenderText_Blended(police2, "Defausse",  {0, 0, 0});
    texte_pioche[2] = TTF_RenderText_Blended(police2, "Figure",  {0, 0, 0});
    for (int i=0;i<5;i++)       ///joueur 1
    {
        if (i==0)
        {
            SDL_SetColorKey(image_Cartes[carte_actuel[10]], SDL_SRCCOLORKEY, SDL_MapRGB(image_Cartes[10]->format, 63, 72, 204));    /// transparence
            SDL_BlitSurface(image_Cartes[carte_actuel[10]], NULL, screen, &position);
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
            SDL_SetColorKey(image_Cartes[carte_actuel[i+3]], SDL_SRCCOLORKEY, SDL_MapRGB(image_Cartes[i]->format, 63, 72, 204));    /// transparence
            SDL_BlitSurface(image_Cartes[carte_actuel[i+3]], NULL, screen, &position);
            position.x=position.x+100;
        }
    }
    position.x=300;
    position.y=position.y+180;

    for (int i=0;i<3;i++)            ///pioche, defausse
    {
        if (i==0)           // la defausse
        {   position_pioche.x=position.x+10;
            position_pioche.y=position.y+130;
            SDL_SetColorKey(image_Cartes[carte_actuel[8]], SDL_SRCCOLORKEY, SDL_MapRGB(image_Cartes[i]->format, 63, 72, 204));    /// transparence
            SDL_BlitSurface(image_Cartes[carte_actuel[8]], NULL, screen, &position);
            SDL_BlitSurface (texte_pioche[1], NULL ,screen, &position_pioche);
            position.x=position.x+190;
        }
        else if(i==1||i==2)
        {
            face_Retourne = SDL_LoadBMP("Cartes/mystere.bmp");
            SDL_BlitSurface(face_Retourne, NULL, screen, &position);
            if (i==1)
            {
                position_pioche.x=position.x+20;
                position_pioche.y=position.y+130;
                SDL_BlitSurface (texte_pioche[2], NULL ,screen, &position_pioche);
                position.x=position.x+190;
            }
            else
            {
                position_pioche.x=position.x+20;
                position_pioche.y=position.y+130;
                SDL_BlitSurface (texte_pioche[0], NULL ,screen, &position_pioche);
                position.x=position.x+190;
            }
        }
    }
    position.x=950;
    position.y=position.y+180;
    for (int i=0;i<5;i++)
    {
        if (i==0)       /// carte figure
        {
            SDL_SetColorKey(image_Cartes[carte_actuel[9]], SDL_SRCCOLORKEY, SDL_MapRGB(image_Cartes[11]->format, 63, 72, 204));    /// transparence
            SDL_BlitSurface(image_Cartes[carte_actuel[9]], NULL, screen, &position);
            position.x=position.x-200;
        }
        if (i==1)
        {
            SDL_SetColorKey(image_Cartes[carte_actuel[i-1]], SDL_SRCCOLORKEY, SDL_MapRGB(image_Cartes[i]->format, 63, 72, 204));    /// transparence
            SDL_BlitSurface(image_Cartes[carte_actuel[i-1]], NULL, screen, &position);      ///joueur 2
            position.x=position.x-100;
        }
        if (i==2)
        {
            SDL_SetColorKey(image_Cartes[carte_actuel[i-1]], SDL_SRCCOLORKEY, SDL_MapRGB(image_Cartes[i]->format, 63, 72, 204));    /// transparence
            SDL_BlitSurface(image_Cartes[carte_actuel[i-1]], NULL, screen, &position);      ///joueur 2
            position.x=position.x-100;
        }
        if (i==3)
        {
            SDL_SetColorKey(image_Cartes[carte_actuel[i-1]], SDL_SRCCOLORKEY, SDL_MapRGB(image_Cartes[i]->format, 63, 72, 204));    /// transparence
            SDL_BlitSurface(image_Cartes[carte_actuel[i-1]], NULL, screen, &position);      ///joueur 2
            position.x=position.x-100;
        }
        if (i==4)
        {
            SDL_SetColorKey(image_Cartes[carte_actuel[i-1]], SDL_SRCCOLORKEY, SDL_MapRGB(image_Cartes[i]->format, 63, 72, 204));    /// transparence
            SDL_BlitSurface(image_Cartes[carte_actuel[i-1]], NULL, screen, &position);      ///joueur 2
            position.x=position.x-100;
        }
    }
    SDL_Flip(screen);
}


void main_du_joueur(int *carte_precedente,int *carte_actuel,int *carte_pioche, int *tour, int *switch1)       /// initialise les cartes des joueurs en fonction du tour
{
        if (*tour==0)
        {
            for (int i=0;i<=8;i++)
            {
               carte_actuel[i]=random_Card(i,tour);
               carte_precedente[i]=carte_actuel[i];     //on récupere la main des joueurs pour permettre le retour en arriere
            }
            for (int i=9;i<=10;i++)
            {
               carte_actuel[i]=random_Card_Figure(i,tour);
               carte_precedente[i]=carte_actuel[i];
            }
        }
        if (*tour==1)
        {
            (*tour)=(*tour)+1;
                if (*switch1==0)
                {
                    carte_actuel[8]=carte_actuel[0];   ///la 11eme carte du plateau correspond a la defausse
                    for (int i=0;i<=rand()%15;i++){
                        carte_actuel[0]=random_Card(i,tour);
                    }
                }
                else if (*switch1==1)       ///le joueur a cliqué sur sa 2eme carte => il veut switché ces cartes
                {
                    carte_actuel[1]=carte_actuel[0];
                    carte_actuel[0]=carte_precedente[1];
                    carte_precedente[1]=carte_actuel[1];
                    carte_precedente[0]=carte_actuel[0];
                }
                else if (*switch1==2)   ///on change de figure
                {
                    for (int i=0;i<=rand()%15;i++)
                    {
                            carte_actuel[9]=random_Card_Figure(i,tour);
                            carte_precedente[9]=carte_actuel[9];
                    }
                }
        }
}

int page_principale_processing(SDL_Rect *position,SDL_Surface *screen,int *carte_precedente,int *carte_actuel,int *carte_pioche,int *tour)
{
        main_du_joueur(carte_precedente, carte_actuel, carte_pioche, tour,0);
        page_principale(screen,0);
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                return 0;
                break;
            case SDL_KEYDOWN:                        // Si appui sur une touche
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:               // Appui sur la touche Echap, on arrête le programme
                        return 0;
                        break;
                    default :
                        break;
                }
                break;
            case SDL_MOUSEBUTTONUP:             // si clic sur boutton
                if (event.button.y > 190 && event.button.y <= 280  && event.button.x > 100 && event.button.x <= 300)
                    {
                        page_principale(screen,1);
                        SDL_Delay(500);
                        EventProcessing(position,screen, carte_precedente, carte_actuel,carte_pioche, tour);
                        //SDL_SetAlpha(bouton_floute, SDL_SRCALPHA, 150);
                        return 0;
                    }
                else if (event.button.y >350 && event.button.y <= 410  && event.button.x > 100 && event.button.x <= 300)
                    {
                        return 0;
                    }
                break;
            default:
                break;
        }
        return 1;
}

int main(int argc, char **argv)
{
    init();

    SDL_Rect position;
    position.x = 0;
    position.y = 0;
    SDL_Surface *screen=NULL;

    int tour;
    int carte_actuel[11];
    int carte_precedente[11];
    int carte_pioche[35];       // 44 cartes de numero - 8 cartes sur le plateau
    tour=0;
    /*for (int j=0;j<=8;j++)
    {
        carte_actuel[j]=NULL;
        carte_precedente[j]=NULL;
    }*/
    //main_du_joueur(carte_precedente, carte_actuel, carte_pioche, &tour,0);
    screen = SDL_SetVideoMode(1100,600,16,SDL_HWSURFACE| SDL_RESIZABLE | SDL_DOUBLEBUF|SDL_FULLSCREEN);
    int cont=1;
    while (cont)
    {
        cont=page_principale_processing(&position,screen, carte_precedente, carte_actuel,carte_pioche, &tour);
    }
    if (screen == NULL)      // Si l'ouverture a échoué, on le note et on arrête
    {
        fprintf(stderr, "Impossible de charger le mode vidéo 2  : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    //TTF_CloseFont(police);          // Doit être avant TTF_Quit()
    quit();
    return EXIT_SUCCESS;
}



///jerer le tour du joueur
///il faut desalouer les variable dynamique creé (pointeur etc.)
///gestion de l'Affichage dynamique pr le déplacement des cartes
