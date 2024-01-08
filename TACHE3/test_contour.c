#include <stdio.h>
#include <string.h>
#include "struct_liste.h"
#include "geom2d.h"
#include "image.h"
#include "contour.h"
#include "types_macros.h"

/*Ce fichier prend un ou plusieur fichier .pbm puis calul leurs contour
** (éventulement affiche le contour : decommenter la ligne coorespondante) et
** ecrit da ns un nouveau fichier ce mem conour)
** */

/* fonction qui ecrit dans un fichier dont le nom est passer en paramètre le
** contour du fichier .pbm en cours de lecture au format spécifié dans l'enoncé
** */
int ecrire_Contour_fichier(Contour C, char* nom_fich)
{
    FILE *f = fopen(nom_fich, "w");

    if (!f)
        ERREUR_FATALE("ERREUR : ecrire_Contour_fichier : impossible d'ouvrir le fichier pour ecrire les contour\n");

    int taille = C.taille;
    int i;
    Cellule_Liste_Point* cel;

    fprintf(f, "1\n");
    fprintf(f, "\n%d\n", taille);

    cel = C.first;
    for(i = 0 ; i < taille ; i++)
    {
       if(! cel)
           ERREUR_FATALE("ERREUR : ecrire_Contour_fichier : le pointeur de cellule cel a atteint la fin du contour alors que la taille suggère que ce n'est pas le cas\n");

       fprintf(f, " %.1lf %.1lf \n", cel->data.x, cel->data.y);
       cel = cel->suiv;
    }

    fclose(f);
    return 0;
}



int main(int argc, char* argv[])
{
    // il faut au moin un fichier .pbm pour cet executable
    if (argc < 2)
    {
        fprintf(stderr, "Uilisation : ./test_contour <groupe de fichier image>\n");
        exit(1);
    }
    // Declaration des variable 
    Image I;
    Contour C;
    int i;
    char nom_fichier[256];

    for (i = 1; i < argc ; i++)
    {

        I = lire_fichier_image(argv[i]);
        C = calcul_contour(I);

        //afichage du nombre de segment 
        printf("----------------------------------------------------------------------------\n");
        printf("Il y a %d segment dans le fichier %s\n", C.taille -1, argv[i]);
        printf("----------------------------------------------------------------------------\n");

        //A decomenter si vous voulez afficher aussi le contour dans le terminal
        //ecrire_contour(C);

        //transformation de <nom_fichier>.pbm en <nom_fichier>.contour
        nom_fichier[0] = '\0'; //on initialise nom_fichier a la liste vide
        strcat(nom_fichier, argv[i]);
        nom_fichier[strlen(nom_fichier) - 3] = '\0';
        strcat(nom_fichier, "contour");

        //ecriture dans le fichier du contour
        ecrire_Contour_fichier(C, nom_fichier);
    }
   return 0; 
}

