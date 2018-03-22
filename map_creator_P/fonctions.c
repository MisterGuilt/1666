#include "constantes.h"
#include "fonctions.h"

void sauvegarder(int **carte, int nb_lignes, int nb_colonnes)
{
    FILE *fichier = NULL;
    int lig, col;
    fichier = fopen("test.txt", "w+");
    fprintf(fichier,"%d %d\n", nb_lignes, nb_colonnes);
    for(lig = 0; lig < nb_lignes; lig++)
    {
        for(col = 0; col < nb_colonnes; col++)
        {
            fprintf(fichier,"%d ", *(*(carte + lig) + col));
        }
        fprintf(fichier,"\n");
    }
    fclose(fichier);
}

int** agrandir_tableau(int **carte, int *nb_lignes, int *nb_colonnes, int sens)//sens comme les aiguilles d'une montre
{
    int **nouvelle_carte, *ligne_originale, *ligne_copie,*case_originale,*case_copie;
    int lig, col, new_lignes = *nb_lignes, new_colonnes = *nb_colonnes;

    if (sens == 0 || sens == 6)
        new_lignes += 1;
    if (sens == 3 || sens == 9)
        new_colonnes += 1;

    nouvelle_carte = malloc(new_lignes * sizeof(int*));
    for(lig = 0; lig < new_lignes; lig++)
    {
        *(nouvelle_carte + lig) = malloc(new_colonnes * sizeof(int));
    }

    for(lig = 0; lig < new_lignes; lig++)
    {
        for(col = 0; col < new_colonnes; col++)
        {
            ligne_copie = *(nouvelle_carte + lig);
            case_copie = ligne_copie + col;
            if(sens == 0)
            {
                ligne_originale = *(carte + lig - 1);
                case_originale = ligne_originale + col;
                if(lig > 0)
                {
                    *case_copie = *case_originale;
                }
                else
                {
                    *case_copie = 0;
                }
            }
            if(sens == 6)
            {
                ligne_originale = *(carte + lig);
                case_originale = ligne_originale + col;
                if(lig < new_lignes - 1)
                    *case_copie = *case_originale;
                else
                    *case_copie = 0;
            }
            if(sens == 9)
            {
                ligne_originale = *(carte + lig);
                case_originale = ligne_originale + col - 1;
                if(col > 0)
                    *case_copie = *case_originale;
                else
                    *case_copie = 0;
            }
            if(sens == 3)
            {
                ligne_originale = *(carte + lig);
                case_originale = ligne_originale + col;
                if(col < new_colonnes - 1)
                    *case_copie = *case_originale;
                else
                    *case_copie = 0;
            }
        }
    }

    for(lig = 0; lig < *nb_lignes; lig++)
    {
        free(*(carte + lig));
    }
    free(carte);
    *nb_lignes = new_lignes;
    *nb_colonnes = new_colonnes;
    return nouvelle_carte;

}

int** initialiser_map()
{
    int** ma_map = NULL;
    int lig, col;
    ma_map = malloc(20 * sizeof(int*));
    for (lig = 0; lig < 20; lig++)
    {
        *(ma_map + lig) = malloc(20 * sizeof(int));
    }
    for (lig = 0; lig < 20; lig++)
    {
        for (col = 0; col < 20; col++)
        {
            *(*(ma_map + lig) + col) = 0;
        }
    }
    return ma_map;
}

int** recuperer_donnees(int *nb_lignes, int* nb_colonnes)
{
    FILE *fichier = NULL;
    int** ma_map = NULL;
    int lig, col, tot_lig, tot_col;
    char autre;

    fichier = fopen("test.txt", "r");
    if (fichier == NULL)
        return initialiser_map();

    fscanf(fichier, "%d %d", &tot_lig, &tot_col);
    *nb_lignes = tot_lig;
    *nb_colonnes = tot_col;
    ma_map = malloc(*nb_lignes * sizeof(int*));
    autre = fgetc(fichier);
    for (lig = 0; lig < *nb_lignes; lig++)
    {
        *(ma_map + lig) = malloc(*nb_colonnes * sizeof(int));
    }
    for (lig = 0; lig < *nb_lignes; lig++)
    {
        for (col = 0; col < *nb_colonnes; col++)
        {
            fscanf(fichier,"%d", &(*(*(ma_map + lig) + col)));
        }

    }
    fclose(fichier);
    return ma_map;
}

int** reduire_map(int **carte, int *nb_lignes, int *nb_colonnes, int sens)//sens comme les aiguilles d'une montre
{
    int **nouvelle_carte, *ligne_originale, *ligne_copie,*case_originale,*case_copie;
    int lig, col, new_lignes = *nb_lignes, new_colonnes = *nb_colonnes;

    if (sens == 0 || sens == 6)
        new_lignes -= 1;
    if (sens == 3 || sens == 9)
        new_colonnes -= 1;

    nouvelle_carte = malloc(new_lignes * sizeof(int*));
    for(lig = 0; lig < new_lignes; lig++)
    {
        *(nouvelle_carte + lig) = malloc(new_colonnes * sizeof(int));
    }

    for(lig = 0; lig < new_lignes; lig++)
    {
        for(col = 0; col < new_colonnes; col++)
        {
            ligne_copie = *(nouvelle_carte + lig);
            case_copie = ligne_copie + col;
            if(sens == 0)
            {
                ligne_originale = *(carte + lig + 1);
                case_originale = ligne_originale + col;
                *case_copie = *case_originale;
            }
            if(sens == 6)
            {
                ligne_originale = *(carte + lig);
                case_originale = ligne_originale + col;
                *case_copie = *case_originale;
            }
            if(sens == 9)
            {
                ligne_originale = *(carte + lig);
                case_originale = ligne_originale + col + 1;
                *case_copie = *case_originale;
            }
            if(sens == 3)
            {
                ligne_originale = *(carte + lig);
                case_originale = ligne_originale + col;
                *case_copie = *case_originale;
            }
        }
    }

    for(lig = 0; lig < *nb_lignes; lig++)
    {
        free(*(carte + lig));
    }
    free(carte);
    *nb_lignes = new_lignes;
    *nb_colonnes = new_colonnes;
    return nouvelle_carte;
}

