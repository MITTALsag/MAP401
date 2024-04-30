#include <stdio.h>
#include <string.h>
#include <struct_liste.h>
#include <geom2d.h>
#include <image.h>
#include <contour.h>
#include <types_macros.h>

/*Ce fichier prend en ligend e commande une image .pbm, puis calcul et écrit à
** la volée (dans un fichier du même nom suffixé par .contour) l'ensemble des
** contoyrs de cette image et affiche en ligne de commande le nombre de contour
** et le total du nombred e segments présents dans ce fichier
*/






int main(int argc, char* argv[])
{

    // il faut au moin un fichier .pbm pour cet executable
    if (argc != 2)
    {
        ERREUR_FATALE("Uilisation : ./test_contour <fichier image>\n");
    }


    Image I;
    char nom_fichier[256];


    I = lire_fichier_image(argv[1]);



    //transformation de <nom_fichier>.pbm en <nom_fichier>.contour
    nom_fichier[0] = '\0'; //on initialise nom_fichier a la liste vide
    strcat(nom_fichier, argv[1]);
    nom_fichier[strlen(nom_fichier) - 3] = '\0';
    strcat(nom_fichier, "contour.txt");


    calcul_contour_multiple(I, nom_fichier);

    return 0;

}

