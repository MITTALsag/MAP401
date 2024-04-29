#include <stdio.h>
#include <string.h>
#include <contour.h>
#include <types_macros.h>
#include <image.h>
#include <simplification.h>
#include <eps.h>
#include <geom2d.h>
#include <bezier.h>


/*
** Ce fichier prend en argument une image .pbm et un float qui sera "d"
** Il va ensuite calculer sont contour comme dans la tache 6 et le mettre dans
** le fichier du meme nom suffixé par .contour.txt
** Puis il va simplifier ce contour grace au courbe de bezier de degres 3
** fichier (cette fois suffixé par .contour_bezier_simple.txt)
** Et enfin il va calculer a partir du contour et du contour simplifier les images eps associés
*/




int main(int argc, char* argv[])
{
    // il faut au moin un fichier .pbm pour cet executable
    if (argc != 3)
    {
        ERREUR_FATALE("Uilisation : ./test_contour <fichier image> <float>\n");
    }


    Image I;
    char nom_fichier_entree[256], nom_fichier_sortie[256], nom_fichier_eps_simple[256], nom_fichier_eps_complet[256];

    I = lire_fichier_image(argv[1]);

    //transformation de <nom_fichier>.pbm en <nom_fichier>.contour.txt
    nom_fichier_entree[0] = '\0'; //on initialise nom_fichier a la liste vide
    strcat(nom_fichier_entree, argv[1]);
    nom_fichier_entree[strlen(nom_fichier_entree) - 3] = '\0';
    strcat(nom_fichier_entree, "contour.txt");


    calcul_contour_multiple(I, nom_fichier_entree);


    //transformation de <nom_fichier>.pbm en <nom_fichier>.contour_simple.txt
    nom_fichier_sortie[0] = '\0'; //on initialise nom_fichier a la liste vide
    strcat(nom_fichier_sortie, argv[1]);
    nom_fichier_sortie[strlen(nom_fichier_sortie) - 3] = '\0';
    strcat(nom_fichier_sortie, "contour_bezier_3_simple.txt");

    simplification_bezier3(nom_fichier_entree, nom_fichier_sortie, (float) atof(argv[2]));


    //transformation de <nom_fichier>.pbm en <nom_fichier>.eps pour eps_complet
    nom_fichier_eps_complet[0] = '\0'; //on initialise nom_fichier_eps_complet a la liste vide
    strcat(nom_fichier_eps_complet, argv[1]);
    nom_fichier_eps_complet[strlen(nom_fichier_eps_complet) - 4] = '\0';
    strcat(nom_fichier_eps_complet, "_fill_complet.eps");

    //ecriture dans le fichier de l'image eps
    cree_image_eps_multiple(nom_fichier_entree, largeur_image(I), hauteur_image(I), nom_fichier_eps_complet, 'F');

    //transformation de <nom_fichier>.pbm en <nom_fichier>.eps pour eps_simple
    nom_fichier_eps_simple[0] = '\0'; //on initialise nom_fichier_eps_simple a la liste vide
    strcat(nom_fichier_eps_simple, argv[1]);
    nom_fichier_eps_simple[strlen(nom_fichier_eps_simple) - 4] = '\0';
    strcat(nom_fichier_eps_simple, "_fill_simple_3.eps");


    //ecriture dans le fichier de l'image eps simplifié
    cree_image_eps_bezier3(nom_fichier_sortie, largeur_image(I), hauteur_image(I), nom_fichier_eps_simple, 'F');
}

