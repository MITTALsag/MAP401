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
void cree_image_eps(Contour C, const UINT Largeur_Image, const UINT Hauteur_Image, char* nom_fichier, char mode)
{
    FILE* fich = fopen(nom_fichier, "w");

    if (!fich)
        ERREUR_FATALE(RED"ERREUR cree_image_eps : le fichier n'a pas pu être ouvert"RESET);


    Cellule_Liste_Point *point_courant = C.first;

    fprintf(fich, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(fich, "%\%BoundingBox: 0 0 %d %d\n", Largeur_Image, Hauteur_Image);
 
    //fprintf("%% Contour de l'image %s\n", nom_fichier);

    fprintf(fich, "%d %d moveto\n", (int)point_courant->data.x, (int)point_courant->data.y);

    point_courant = point_courant->suiv;
    while (point_courant)
    {
        fprintf(fich, "%d %d lineto\n", (int)point_courant->data.x, (int)point_courant->data.y);
        point_courant = point_courant->suiv;
    }

    fprintf(fich, "%% Instruction de tracé\n");
    if (mode == 'F')
        fprintf(fich, "fill\n");
    else
        fprintf(fich, "stroke\n");

    fprintf(fich, "showpage\n");


}
