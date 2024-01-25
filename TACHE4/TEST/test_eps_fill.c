#include <stdio.h>
#include <string.h>
#include <struct_liste.h>
#include <image.h>
#include <contour.h>
#include <eps.h>
#include <types_macros.h>


int main(int argc, char* argv[])
{
    // il faut un fichier .pbm pour cet executable
    if (argc != 2)
    {
        ERREUR_FATALE("Uilisation : ./test_contour <fichier image>\n");
    }
    // Declaration des variable 
    Image I;
    Contour C;
    char nom_fichier[256];


    I = lire_fichier_image(argv[1]);
    C = calcul_contour(I);

    //afichage du nombre de segment 
    printf("----------------------------------------------------------------------------\n");
    printf(CYN"Il y a %d segment dans le fichier %s\n"RESET, C.taille -1, argv[1]);
    printf("----------------------------------------------------------------------------\n");


    //transformation de <nom_fichier>.pbm en <nom_fichier>.eps
    nom_fichier[0] = '\0'; //on initialise nom_fichier a la liste vide
    strcat(nom_fichier, argv[1]);
    nom_fichier[strlen(nom_fichier) - 4] = '\0';
    strcat(nom_fichier, "_fill.eps");

    //ecriture dans le fichier du contour
    cree_image_eps(C, largeur_image(I), hauteur_image(I), nom_fichier, 'F');

    return 0; 
}

