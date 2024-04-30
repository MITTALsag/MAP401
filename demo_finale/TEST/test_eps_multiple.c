#include <stdio.h>
#include <string.h>
#include <image.h>
#include <eps.h>
#include <types_macros.h>


int main(int argc, char* argv[])
{
    // il faut un fichier .pbm pour cet executable
    if (argc != 3)
    {
        ERREUR_FATALE("Uilisation : ./test_contour <fichier image> <fichier contour correspondant>\n");
    }
    // Declaration des variable 
    Image I;
    char nom_fichier[256];


    I = lire_fichier_image(argv[1]);


    //transformation de <nom_fichier>.pbm en <nom_fichier>.eps
    nom_fichier[0] = '\0'; //on initialise nom_fichier a la liste vide
    strcat(nom_fichier, argv[1]);
    nom_fichier[strlen(nom_fichier) - 4] = '\0';
    strcat(nom_fichier, "_fill.eps");

    //ecriture dans le fichier du contour
    cree_image_eps_multiple(argv[2], largeur_image(I), hauteur_image(I), nom_fichier, 'F');

    return 0;
}

