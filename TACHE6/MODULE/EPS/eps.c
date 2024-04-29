#include <stdio.h>
#include <eps.h>
#include <struct_liste.h>
#include <geom2d.h>
#include <types_macros.h>


/* - Ouvre le fichier "nom_fichier" en ecriture
** - cree l'image sous format eps avec le contour passé en paramètre
** (l'image est cree avec des segements)
** - l'image est cree avec fill ou stroke en fonction du mode passé en argument
** (fais stroke par defaut et il faut passé F dans mode pour faire fill)
*/
void cree_image_eps(const Contour C, const UINT Largeur_Image, const UINT Hauteur_Image, const char* nom_fichier, const char mode)
{
    FILE* fich = fopen(nom_fichier, "w");

    if (!fich)
        ERREUR_FATALE(RED"ERREUR cree_image_eps : le fichier n'a pas pu être ouvert"RESET);


    Cellule_Liste_Point *point_courant = C.first;

    fprintf(fich, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(fich, "%%%%BoundingBox: 0 0 %d %d\n", Largeur_Image, Hauteur_Image);
 
    //fprintf("%% Contour de l'image %s\n", nom_fichier);

    fprintf(fich, "%d %d moveto\n", (int)point_courant->data.x, Hauteur_Image - (int)point_courant->data.y);

    point_courant = point_courant->suiv;
    while (point_courant)
    {
        fprintf(fich, "%d %d lineto\n", (int)point_courant->data.x, Hauteur_Image - (int)point_courant->data.y);
        point_courant = point_courant->suiv;
    }
    fprintf(fich, "%% largeur du tracé\n");
    fprintf(fich, "0 setlinewidth\n");

    fprintf(fich, "%% Instruction de tracé\n");
    if (mode == 'F')
        fprintf(fich, "fill\n");
    else
        fprintf(fich, "stroke\n");

    fprintf(fich, "showpage\n");

    fclose(fich);

}



/* - Ouvre le fichier "nom_fichier" en ecriture
** - cree l'image sous format eps avec les contour passé en paramètre
** (l'image est cree avec des segements)
** - l'image est cree avec fill ou stroke en fonction du mode passé en argument
** (fais stroke par defaut et il faut passé F dans mode pour faire fill)
*/
void cree_image_eps_multiple(const char* fichier_contour, const UINT Largeur_Image, const UINT Hauteur_Image, const char* nom_fichier, const char mode)
{
    FILE* fich = fopen(nom_fichier, "w");

    if (!fich)
        ERREUR_FATALE(RED"ERREUR cree_image_eps : le fichier n'a pas pu être ouvert"RESET);

    //overtur du fichier qui contiens tous les contours
    FILE* fich_contour = fopen(fichier_contour, "r");

    if (!fich_contour)
        ERREUR_FATALE(RED"ERREUR cree_image_eps : le fichier contour n'a pas pu être ouvert"RESET);

    //declaration de variables
    int nb_contour, taille_contour;
    float val_x, val_y;


    fprintf(fich, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(fich, "%%%%BoundingBox: 0 0 %d %d\n", Largeur_Image, Hauteur_Image);


    fscanf(fich_contour, "%d\n\n", &nb_contour);

    for (int i = 0 ; i < nb_contour ; i++)
    {
       fscanf(fich_contour, "%d\n", &taille_contour);

       fscanf(fich_contour, "%f %f\n", &val_x, &val_y);

        fprintf(fich, "%d %d moveto\n", (int)val_x, Hauteur_Image - (int)val_y);

        for (int j = 1 ; j < taille_contour ; j++)
        {

            fscanf(fich_contour, "%f %f\n", &val_x, &val_y);

            fprintf(fich, "%d %d lineto\n", (int)val_x, Hauteur_Image - (int)val_y);

        }
        fscanf(fich_contour, "\n");
        fprintf(fich, "\n");
    }

    fprintf(fich, "%% largeur du tracé\n");
    fprintf(fich, "0 setlinewidth\n");

    fprintf(fich, "%% Instruction de tracé\n");
    if (mode == 'F')
        fprintf(fich, "fill\n");
    else
        fprintf(fich, "stroke\n");

    fprintf(fich, "showpage\n");

    fclose(fich);
    fclose(fich_contour);

}







