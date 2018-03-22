#include "constantes.h"
#include "fonctions.h"
#include "clicks.h"
#include "evenements.h"

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL");
        exit(EXIT_FAILURE);
    }
    else
    {
        int continuer = 1, compt1, nb_lignes = 20, nb_colonnes = 20, pos_x = -1, pos_y = -1, etape = 0;
        int **ma_map = NULL, affichage_pos_x = 0, affichage_pos_y = 0;
        int lig, col, vraie_case_x, vraie_case_y, selection = 0, intermediaire;
        SDL_Surface *ecran = NULL, *terrains[NB_TERRAINS], *vide = NULL, *fleche_haute = NULL;
        SDL_Surface *fleche_basse = NULL, *fleche_g = NULL, *fleche_d = NULL, *bouton_recup = NULL, *bouton_new = NULL;
        SDL_Surface *bouton_croix = NULL, *bouton_plus = NULL, *filtre = NULL;
        SDL_Rect positionTerrain, pos_save, pos_fleche_haute, pos_fleche_basse, p_f_g, p_f_d, p_b_r, p_b_n;
        SDL_Rect pos_croix_haut, pos_croix_bas, pos_croix_d, pos_croix_g, p_b_p_h, p_b_p_b, p_b_p_g, p_b_p_d, sel_1, sel_2;
        image_fixe fond, cadre, save;

        SDL_Event event;
        sel_1 = enregistre_pos(0,0);
        sel_2 = enregistre_pos(0,0);
        SDL_WM_SetIcon(SDL_LoadBMP("boussole.bmp"), NULL);
        ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
        SDL_WM_SetCaption(" Map creator", NULL);
// Chargement des images
        fond.img = SDL_LoadBMP("fond.bmp");
        fond.pos = enregistre_pos(0,0);
        cadre.img = SDL_LoadBMP("cadre.bmp");
        cadre.pos = enregistre_pos(POS_TERRAIN_X - 1, POS_TERRAIN_Y - 1);

        vide = SDL_LoadBMP("Terrains/vide.bmp");
        terrains[T_INCONNU] = SDL_LoadBMP("Terrains/inconnu.bmp");
        terrains[T_EAU] = SDL_LoadBMP("Terrains/riviere.bmp");
        terrains[T_HERBE] = SDL_LoadBMP("Terrains/herbe.bmp");


        filtre = SDL_LoadBMP("Terrains/filtre.bmp");
        SDL_SetAlpha(filtre, SDL_SRCALPHA, 128);

        positionTerrain = enregistre_pos(POS_TERRAIN_X, POS_TERRAIN_Y);
        save.img = SDL_LoadBMP("Boutons/save.bmp");
        SDL_SetColorKey(save.img, SDL_SRCCOLORKEY, SDL_MapRGB(save.img->format, 255, 255, 255));
        save.pos = enregistre_pos(660,10);

        fleche_haute = SDL_LoadBMP("Boutons/fleche_bas.bmp");
        SDL_SetColorKey(fleche_haute, SDL_SRCCOLORKEY, SDL_MapRGB(fleche_haute->format, 255, 255, 255));
        pos_fleche_haute = enregistre_pos(385,5);

        fleche_basse = SDL_LoadBMP("Boutons/fleche_haut.bmp");
        SDL_SetColorKey(fleche_basse, SDL_SRCCOLORKEY, SDL_MapRGB(fleche_basse->format, 255, 255, 255));
        pos_fleche_basse = enregistre_pos(pos_fleche_haute.x,565);

        fleche_g = SDL_LoadBMP("Boutons/fleche_droite.bmp");
        SDL_SetColorKey(fleche_g, SDL_SRCCOLORKEY, SDL_MapRGB(fleche_g->format, 255, 255, 255));
        p_f_g  = enregistre_pos(45,285);

        fleche_d = SDL_LoadBMP("Boutons/fleche_gauche.bmp");
        SDL_SetColorKey(fleche_d, SDL_SRCCOLORKEY, SDL_MapRGB(fleche_d->format, 255, 255, 255));
        p_f_d = enregistre_pos(700,p_f_g.y);

        bouton_croix = SDL_LoadBMP("Boutons/croix.bmp");
        SDL_SetColorKey(bouton_croix, SDL_SRCCOLORKEY, SDL_MapRGB(bouton_croix->format, 255, 255, 255));
        pos_croix_bas = enregistre_pos(pos_fleche_basse.x - 2*TAILLE_BOUTON, pos_fleche_basse.y);
        pos_croix_d = enregistre_pos(p_f_d.x, p_f_d.y - 2*TAILLE_BOUTON);
        pos_croix_g = enregistre_pos(p_f_g.x, p_f_g.y - 2*TAILLE_BOUTON);
        pos_croix_haut = enregistre_pos(pos_fleche_haute.x - 2*TAILLE_BOUTON, pos_fleche_haute.y);

        bouton_plus = SDL_LoadBMP("Boutons/plus.bmp");
        SDL_SetColorKey(bouton_plus, SDL_SRCCOLORKEY, SDL_MapRGB(bouton_plus->format, 255, 255, 255));
        p_b_p_b = enregistre_pos(pos_fleche_basse.x + 2*TAILLE_BOUTON, pos_fleche_basse.y);
        p_b_p_d = enregistre_pos(p_f_d.x, p_f_d.y + 2*TAILLE_BOUTON);
        p_b_p_g = enregistre_pos(p_f_g.x, p_f_g.y + 2*TAILLE_BOUTON);
        p_b_p_h = enregistre_pos(pos_fleche_haute.x + 2*TAILLE_BOUTON, pos_fleche_haute.y);

        bouton_recup = SDL_LoadBMP("Boutons/recup.bmp");
        p_b_r = enregistre_pos(200,100);

        bouton_new = SDL_LoadBMP("Boutons/nouveau.bmp");
        p_b_n = enregistre_pos(p_b_r.x,400);
// Fin du chargement des images

        etape = 0;
        while (continuer)
        {
            if(etape == 0)
            {
                SDL_BlitSurface(fond.img, NULL, ecran, &fond.pos);
                SDL_BlitSurface(bouton_recup, NULL, ecran, &p_b_r);
                SDL_BlitSurface(bouton_new, NULL, ecran , &p_b_n);

                SDL_Flip(ecran);

                SDL_WaitEvent(&event);
                switch(event.type)
                {
                    case SDL_QUIT:
                        continuer = 0;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if(dans_ecart_2(event.button.x, p_b_r.x,500) && dans_ecart_2(event.button.y, p_b_r.y, 100))
                        {
                            ma_map = recuperer_donnees(&nb_lignes, &nb_colonnes);
                            etape = 1;
                        }
                        if(dans_ecart_2(event.button.x, p_b_n.x, 500) && dans_ecart_2(event.button.y, p_b_n.y, 100))
                        {
                            ma_map = initialiser_map();
                            etape = 1;
                        }
                        break;
                }
            }
            if(etape == 1)
            {
                SDL_BlitSurface(fond.img, NULL, ecran, &fond.pos);
                SDL_BlitSurface(cadre.img, NULL, ecran, &cadre.pos);
                SDL_BlitSurface(save.img, NULL, ecran , &save.pos);
                SDL_BlitSurface(fleche_haute, NULL, ecran , &pos_fleche_haute);
                SDL_BlitSurface(fleche_basse, NULL, ecran , &pos_fleche_basse);
                SDL_BlitSurface(fleche_g, NULL, ecran , &p_f_g);
                SDL_BlitSurface(fleche_d, NULL, ecran , &p_f_d);
                SDL_BlitSurface(bouton_croix, NULL, ecran , &pos_croix_bas);
                SDL_BlitSurface(bouton_croix, NULL, ecran , &pos_croix_haut);
                SDL_BlitSurface(bouton_croix, NULL, ecran , &pos_croix_g);
                SDL_BlitSurface(bouton_croix, NULL, ecran , &pos_croix_d);
                SDL_BlitSurface(bouton_plus, NULL, ecran , &p_b_p_b);
                SDL_BlitSurface(bouton_plus, NULL, ecran , &p_b_p_h);
                SDL_BlitSurface(bouton_plus, NULL, ecran , &p_b_p_g);
                SDL_BlitSurface(bouton_plus, NULL, ecran , &p_b_p_d);
                for (col = affichage_pos_x; col < 20 + affichage_pos_x; col++)
                {
                    positionTerrain.x = POS_TERRAIN_X + TAILLE_TERRAIN * (col - affichage_pos_x);
                    for (lig = affichage_pos_y; lig < 20 + affichage_pos_y; lig++)
                    {

                        positionTerrain.y = POS_TERRAIN_Y + TAILLE_TERRAIN * (lig - affichage_pos_y);
                        if (col < 0 || col > nb_colonnes || lig < 0 || lig > nb_lignes)
                        {
                            SDL_BlitSurface(vide, NULL, ecran, &positionTerrain);
                        }
                        else
                            SDL_BlitSurface(terrains[*(*(ma_map + lig) + col)], NULL, ecran, &positionTerrain);
                        if(selection == 1 && sel_1.x == col + affichage_pos_x && sel_1.y == lig + affichage_pos_y)
                            SDL_BlitSurface(filtre, NULL, ecran, &positionTerrain);
                        if(selection == 2 && dans_ecart(col + affichage_pos_x, sel_1.x, sel_2.x) == 1 && dans_ecart(lig + affichage_pos_y, sel_1.y, sel_2.y))
                            SDL_BlitSurface(filtre, NULL, ecran, &positionTerrain);
                    }
                }

                SDL_Flip(ecran);

                SDL_WaitEvent(&event);
                switch(event.type)
                {
                    case SDL_QUIT:
                        continuer = 0;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if(dans_ecart_2(event.button.x, POS_TERRAIN_X, 500) && dans_ecart_2(event.button.y, POS_TERRAIN_Y, 500))
                        {
                            for (col = 0; col < 20; col++)
                            {
                                for (lig = 0; lig < 20; lig++)
                                {
                                    if (dans_ecart_2(event.button.x, POS_TERRAIN_X + TAILLE_TERRAIN * col, TAILLE_TERRAIN))
                                        pos_x = col;
                                    if (dans_ecart_2(event.button.y, POS_TERRAIN_Y + TAILLE_TERRAIN * lig, TAILLE_TERRAIN))
                                        pos_y = lig;
                                }
                            }
                            if (pos_x != -1 && pos_y != -1)
                            {
                                vraie_case_x = pos_x + affichage_pos_x;
                                vraie_case_y = pos_y + affichage_pos_y;

                                if(selection == 0)
                                {
                                    if(event.button.button == SDL_BUTTON_LEFT)
                                        changer_valeur_case(ma_map, vraie_case_y, vraie_case_x, 1);
                                    if(event.button.button == SDL_BUTTON_RIGHT)
                                        changer_valeur_case(ma_map, vraie_case_y, vraie_case_x, -1);
                                    if(event.button.button == SDL_BUTTON_MIDDLE)
                                    {
                                        selection = 1;
                                        sel_1 = enregistre_pos(vraie_case_x,vraie_case_y);
                                    }
                                }
                                else if(selection == 1)
                                {
                                    if(event.button.button == SDL_BUTTON_LEFT)
                                    {
                                        if(vraie_case_x == sel_1.x && vraie_case_y == sel_1.y)
                                            changer_valeur_case(ma_map, vraie_case_y, vraie_case_x, 1);
                                        if(vraie_case_x != sel_1.x || vraie_case_y != sel_1.y)
                                            selection = 0;
                                    }
                                    if(event.button.button == SDL_BUTTON_RIGHT)
                                    {
                                        if(vraie_case_x == sel_1.x && vraie_case_y == sel_1.y)
                                            changer_valeur_case(ma_map, vraie_case_y, vraie_case_x, -1);
                                        if(vraie_case_x != sel_1.x || vraie_case_y != sel_1.y)
                                            selection = 0;
                                    }
                                    if(event.button.button == SDL_BUTTON_MIDDLE)
                                    {
                                        if(vraie_case_x == sel_1.x && vraie_case_y == sel_1.y)
                                            selection = 0;
                                        if(vraie_case_x != sel_1.x || vraie_case_y != sel_1.y)
                                        {
                                            selection = 2;
                                            sel_2 = enregistre_pos(vraie_case_x,vraie_case_y);
                                            if(sel_1.x > sel_2.x)
                                            {
                                                intermediaire = sel_1.x;
                                                sel_1.x = sel_2.x;
                                                sel_2.x = intermediaire;
                                            }
                                            if(sel_1.y > sel_2.y)
                                            {
                                                intermediaire = sel_1.y;
                                                sel_1.y = sel_2.y;
                                                sel_2.y = intermediaire;
                                            }
                                        }
                                    }
                                }
                                else if(selection == 2)
                                {
                                    if(event.button.button == SDL_BUTTON_LEFT || event.button.button == SDL_BUTTON_RIGHT)
                                    {
                                        if(dans_ecart(vraie_case_x, sel_1.x, sel_2.x) == 1 && dans_ecart(vraie_case_y, sel_1.y, sel_2.y) == 1)
                                        {
                                            for(lig = sel_1.y; lig <= sel_2.y; lig++)
                                            {
                                                for(col = sel_1.x; col <= sel_2.x; col++)
                                                {
                                                    vraie_case_x = col + affichage_pos_x;
                                                    vraie_case_y = lig + affichage_pos_y;
                                                    if(event.button.button == SDL_BUTTON_LEFT)
                                                        changer_valeur_case(ma_map, vraie_case_y, vraie_case_x, 1);
                                                    if(event.button.button == SDL_BUTTON_RIGHT)
                                                        changer_valeur_case(ma_map, vraie_case_y, vraie_case_x, -1);
                                                }
                                            }
                                        }
                                        if(dans_ecart(vraie_case_x, sel_1.x, sel_2.x) != 1 || dans_ecart(vraie_case_y, sel_1.y, sel_2.y) != 1)
                                            selection = 0;
                                    }
                                    if(event.button.button == SDL_BUTTON_MIDDLE)
                                        selection = 0;
                                }
                            }
                            pos_x = -1;
                            pos_y = -1;
                        }
                        if(dans_ecart_2(event.button.x, save.pos.x, TAILLE_SAVE_X) && dans_ecart_2(event.button.y, save.pos.y, TAILLE_SAVE_Y))
                        {
                            sauvegarder(ma_map, nb_lignes, nb_colonnes);
                            continuer = 0;
                        }
                        if(click_bouton(pos_fleche_haute, event) == 1)
                        {
                            affichage_pos_y = affichage_pos_y - 1;//*/
                        }
                        if(click_bouton(pos_fleche_basse, event) == 1)
                        {
                            if (nb_lignes - affichage_pos_y != 20)
                                affichage_pos_y = affichage_pos_y + 1;//*/
                        }
                        if(click_bouton(p_f_g, event) == 1)
                        {
                            affichage_pos_x = affichage_pos_x - 1;//*/
                        }
                        if(click_bouton(p_f_d, event) == 1)
                        {
                            if (nb_colonnes - affichage_pos_x != 20)
                                affichage_pos_x = affichage_pos_x + 1;
                        }
                        if(click_bouton(p_b_p_h, event) == 1)
                        {
                            ma_map = agrandir_tableau(ma_map, &nb_lignes, &nb_colonnes, 0);
                        }
                        if(click_bouton(p_b_p_b, event) == 1)
                        {
                            ma_map = agrandir_tableau(ma_map, &nb_lignes, &nb_colonnes, 6);
                            if (nb_lignes - affichage_pos_y != 20)
                                affichage_pos_y = affichage_pos_y + 1;
                        }
                        if(click_bouton(p_b_p_d, event) == 1)
                        {
                            ma_map = agrandir_tableau(ma_map, &nb_lignes, &nb_colonnes, 3);
                            if (nb_colonnes - affichage_pos_x != 20)
                                affichage_pos_x = affichage_pos_x + 1;
                        }
                        if(click_bouton(p_b_p_g, event) == 1)
                        {
                            ma_map = agrandir_tableau(ma_map, &nb_lignes, &nb_colonnes, 9);
                        }
                        if(click_bouton(pos_croix_haut, event) == 1 && nb_lignes > 20)
                        {
                            ma_map = reduire_map(ma_map, &nb_lignes, &nb_colonnes, 0);
                            affichage_pos_y = affichage_pos_y - 1;
                        }
                        if(click_bouton(pos_croix_bas, event) == 1 && nb_lignes > 20)
                        {
                            ma_map = reduire_map(ma_map, &nb_lignes, &nb_colonnes, 6);
                            affichage_pos_y = affichage_pos_y - 1;
                        }
                        if(click_bouton(pos_croix_g, event) == 1 && nb_colonnes > 20)
                        {
                            ma_map = reduire_map(ma_map, &nb_lignes, &nb_colonnes, 9);
                            affichage_pos_x = affichage_pos_x - 1;
                        }
                        if(click_bouton(pos_croix_d, event) == 1 && nb_colonnes > 20)
                        {
                            ma_map = reduire_map(ma_map, &nb_lignes, &nb_colonnes, 3);
                            affichage_pos_x = affichage_pos_x - 1;
                        }
                        break;
                }
            }
        }
        SDL_FreeSurface(vide);
        SDL_FreeSurface(save.img);
        SDL_FreeSurface(bouton_croix);
        SDL_FreeSurface(bouton_plus);
        SDL_FreeSurface(bouton_new);
        SDL_FreeSurface(bouton_recup);
        for(compt1 = 0; compt1 < NB_TERRAINS; compt1++)
        {
            SDL_FreeSurface(terrains[compt1]);
        }
        SDL_FreeSurface(cadre.img);
        SDL_FreeSurface(fond.img);

        for(compt1 = 0; compt1 < nb_lignes; compt1++)
        {
            free(ma_map[compt1]);
        }
        free(ma_map);
    }

    SDL_Quit();

    return EXIT_SUCCESS;
}

