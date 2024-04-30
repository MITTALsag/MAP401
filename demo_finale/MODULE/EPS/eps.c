#include <stdio.h>
#include <eps.h>
#include <struct_liste.h>
#include <geom2d.h>
#include <types_macros.h>
#include <bezier.h>


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




void cree_image_eps_bezier2(const char* fichier_contour, const UINT Largeur_Image, const UINT Hauteur_Image, const char* nom_fichier, const char mode)
{
    FILE* fich = fopen(nom_fichier, "w");

    if (!fich)
        ERREUR_FATALE(RED"ERREUR cree_image_eps : le fichier n'a pas pu être ouvert"RESET);

    //overtur du fichier qui contiens tous les contours
    FILE* fich_contour = fopen(fichier_contour, "r");

    if (!fich_contour)
        ERREUR_FATALE(RED"ERREUR cree_image_eps : le fichier contour n'a pas pu être ouvert"RESET);

    //declaration de variables
    int nb_contour, taille_contour, nb_courbe;
    double val_x, val_y;
    bool premier;
    Bezier2 B;
    Bezier3 B3;
    Point C0, C1, C2;


    fprintf(fich, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(fich, "%%%%BoundingBox: 0 0 %d %d\n\n", Largeur_Image, Hauteur_Image);


    fscanf(fich_contour, "%d\n\n", &nb_contour);
    nb_courbe = 0;

    for (int i = 0 ; i < nb_contour ; i++)
    {
       fscanf(fich_contour, "%d\n", &taille_contour);
       premier = true; //sert a ecrire le "moveto"

        for (int j = 0 ; j < taille_contour ; j+=3)
        {
            fscanf(fich_contour, "%lf %lf\n", &val_x, &val_y);
            C0 = set_point(val_x, val_y);

            fscanf(fich_contour, "%lf %lf\n", &val_x, &val_y);
            C1 = set_point(val_x, val_y);

            fscanf(fich_contour, "%lf %lf\n", &val_x, &val_y);
            C2 = set_point(val_x, val_y);

            B = init_bezier2(C0, C1, C2);
            //elevation au degres car il faut que se soit de degres 3
            B3 = elevation_degre(B);

            if (premier) //pour ecrive un seul moveto par contour
            {
                fprintf(fich, "%lf %lf moveto\n", B3.C0.x, (double)Hauteur_Image - B3.C0.y);
                premier = false;
            }

            fprintf(fich, "%lf %lf\n", B3.C1.x, (double)Hauteur_Image - B3.C1.y);
            fprintf(fich, "%lf %lf\n", B3.C2.x, (double)Hauteur_Image - B3.C2.y);
            fprintf(fich, "%lf %lf curveto\n\n", B3.C3.x, (double)Hauteur_Image - B3.C3.y);
            nb_courbe++;

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


    printf(BLU"Le contour simplifié contient %d courbe de bezier de degres 2\n"RESET, nb_courbe);
    fclose(fich);
    fclose(fich_contour);

}




void cree_image_eps_bezier3(const char* fichier_contour, const UINT Largeur_Image, const UINT Hauteur_Image, const char* nom_fichier, const char mode)
{
    FILE* fich = fopen(nom_fichier, "w");

    if (!fich)
        ERREUR_FATALE(RED"ERREUR cree_image_eps : le fichier n'a pas pu être ouvert"RESET);

    //overtur du fichier qui contiens tous les contours
    FILE* fich_contour = fopen(fichier_contour, "r");

    if (!fich_contour)
        ERREUR_FATALE(RED"ERREUR cree_image_eps : le fichier contour n'a pas pu être ouvert"RESET);

    //declaration de variables
    int nb_contour, taille_contour, nb_courbe;
    double val_x, val_y;
    bool premier;
    Bezier3 B;
    Point C0, C1, C2, C3;


    fprintf(fich, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(fich, "%%%%BoundingBox: 0 0 %d %d\n\n", Largeur_Image, Hauteur_Image);


    fscanf(fich_contour, "%d\n\n", &nb_contour);
    nb_courbe = 0;

    for (int i = 0 ; i < nb_contour ; i++)
    {
       fscanf(fich_contour, "%d\n", &taille_contour);
       premier = true; //sert a ecrire le "moveto"

        for (int j = 0 ; j < taille_contour ; j+=4)
        {
            fscanf(fich_contour, "%lf %lf\n", &val_x, &val_y);
            C0 = set_point(val_x, val_y);

            fscanf(fich_contour, "%lf %lf\n", &val_x, &val_y);
            C1 = set_point(val_x, val_y);

            fscanf(fich_contour, "%lf %lf\n", &val_x, &val_y);
            C2 = set_point(val_x, val_y);

            fscanf(fich_contour, "%lf %lf\n", &val_x, &val_y);
            C3 = set_point(val_x, val_y);


            B = init_bezier3(C0, C1, C2, C3);

            if (premier) //pour ecrive un seul moveto par contour
            {
                fprintf(fich, "%lf %lf moveto\n", B.C0.x, (double)Hauteur_Image - B.C0.y);
                premier = false;
            }

            fprintf(fich, "%lf %lf\n", B.C1.x, (double)Hauteur_Image - B.C1.y);
            fprintf(fich, "%lf %lf\n", B.C2.x, (double)Hauteur_Image - B.C2.y);
            fprintf(fich, "%lf %lf curveto\n\n", B.C3.x, (double)Hauteur_Image - B.C3.y);
            nb_courbe++;

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


    printf(BLU"Le contour simplifié contient %d courbe de bezier de degres 3\n"RESET, nb_courbe);
    fclose(fich);
    fclose(fich_contour);

}


