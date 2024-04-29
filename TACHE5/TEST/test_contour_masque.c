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




/* fonction qui ecrit dans un fichier (passé en parametre) un contour
** du fichier .pbm en cours de lecture au format spécifié dans l'enoncé
** */
int ecrire_Contour_fichier(Contour* C, FILE* f)
{

    int taille = C->taille;
    int i;
    Cellule_Liste_Point* cel;

    fprintf(f, "%d\n", taille);

    cel = C->first;

    //parcour de l'ensemble de la liste chainée
    for(i = 0 ; i < taille ; i++)
    {
       if(!cel)
           ERREUR_FATALE(RED"ERREUR : ecrire_Contour_fichier : le pointeur de cellule cel a atteint la fin du contour alors que la taille suggère que ce n'est pas le cas\n"RESET);

       fprintf(f, "%.1lf %.1lf\n", cel->data.x, cel->data.y);
       cel = cel->suiv;
    }

    fprintf(f, "\n");

    return 0;
}




/* Fonction qui prend une image en parametre et calcul puis ecrit a la voléé
** (grace a ecrire_contour_fichier) les contours dans un fichier dont le nom est
** passé en paramètre
*/
void calcul_contour_multiple(Image I, char* nom_fich)
{


    FILE *f = fopen(nom_fich, "w");

    if (!f)
        ERREUR_FATALE(RED"ERREUR : ecrire_Contour_fichier : impossible d'ouvrir le fichier pour ecrire les contour\n"RESET);


    //declarations des variables
    Contour C;
    Image masque_I;
    UINT i,j,H,L;
    int nb_segment, nb_contour;
    Pixel p;


    //initialistaion de
    //H : hauteur de l'image
    //L : largeur de l'image
    //nb_contour : nombre de contour dans l'image
    //nb_segment : nombre de segemnt dans l'image
    H = hauteur_image(I);
    L = largeur_image(I);
    nb_contour = 0;
    nb_segment = 0;

    masque_I = calcul_image_masque(I);

    //ces espaces servent à faire le rewind en fin de boucle car le rewindne cree pas des caractere (il ecrase ceux déjà présents)
    //Ces pour mettre le nombre de contours aà la fin
    fprintf(f, "          \n\n");

    //parcours de toute l'image masque et si un pixel est noir on calcul son contour, et on met a jour les variable nb_contour et nb_segement
    for(j = 1; j<= H; j++)
    {
        for(i= 1; i<= L; i++)
        {
            p = get_pixel_image(masque_I, i, j);

            if (p == NOIR)
            {
                //calcul du contour
                C = calcul_contour_masque(set_point(i,j), masque_I, I);

                ecrire_Contour_fichier(&C, f);

                //mise a jour des variable nb_contour et nb_segment
                nb_segment += C.taille - 1;
                nb_contour++;
            }

        }
    }


    //pour mettre nb_contour au debut du fichier
    rewind(f);
    fprintf(f, "%d", nb_contour);

    fclose(f);


    //afichage du nombre de segment
    printf("----------------------------------------------------------------------------\n");
    printf(YEL"Les dimension de cette images sont : %dx%d\n"RESET, largeur_image(I), hauteur_image(I));
    printf(CYN"Il y a %d contour et un total de %d segments dans le fichier %s\n"RESET, nb_contour, nb_segment,nom_fich);
    printf("----------------------------------------------------------------------------\n");
}



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

