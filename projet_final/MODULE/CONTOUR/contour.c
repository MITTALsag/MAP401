#include <stdio.h>
#include <geom2d.h>
#include <struct_liste.h>
#include <image.h>
#include <types_macros.h>
#include <contour.h>

/* initialise un robot qui a pour coordonnée (0,0) est une orientaion vers
** l'Est */
Robot init_robot(Point P)
{
    Robot r;
    r.o = EST;
    r.pt.x = P.x;
    r.pt.y = P.y;
    return r;
}


/* fonction qui calcule et renvoi les coordonnées de la position initial du
** robot pour le calcul de l'image 
** quitte l'execution si il n'y a pas de point noir */
Point calcul_pos_init(Image I)
{
    UINT i,j;
    Pixel p, p_1; //p_1 correspondra au pixel au dessu de p

    // i represente l'abscisse et j l'ordonnée
    for(j = 1 ; j <= hauteur_image(I) ; j++)
    {
        for (i = 1 ; i <= largeur_image(I) ; i++)
        {
            p = get_pixel_image(I, i, j);
            p_1 = get_pixel_image(I, i, j-1);

            if (p == NOIR && p_1 == BLANC)
                return set_point(i, j);
        }
    }

    //si on arrive ici c'est que l'image est toute blance et donc pas de contour
    ERREUR_FATALE("Il n'y a pas de pixel noir dans cette image\n");

    return set_point(0,0);

}






/* fais avncer le robot d'une case en fonction de son orientation */
Point avancer_robot(Robot R)
{
    switch(R.o)
    {
        case NORD:
            R.pt.y = R.pt.y - 1;
            break;
        case SUD:
            R.pt.y = R.pt.y + 1;
            break;
        case EST:
            R.pt.x = R.pt.x + 1;
            break;
        case OUEST:
            R.pt.x = R.pt.x - 1;
            break;
        default : 
            ERREUR_FATALE("avancer_robot : Erreur dans l'orientation du robot");
            break;
    }

    return R.pt;
}

/* Les 4 fonction pixel_NW/NE/SW/SE renvoie la coordonné du pixel au la
** position voulu en fonction de la position du robot */
Point pixel_NW(Point P)
{
    return P;
}

Point pixel_NE(Point P)
{
    return set_point(P.x + 1, P.y);
}

Point pixel_SW(Point P)
{
    return set_point(P.x, P.y + 1);
}

Point pixel_SE(Point P)
{
    return set_point(P.x + 1, P.y + 1);
}


/* La fonction rot_90 renvoie l'orientation apres une rotation de 90 degres
** dans le ses trigonometrique */
/* Le fonction rot_i_90 fais le meme sorte de rotation mais n fais */
Orientation rot_90(Orientation O)
{
    switch (O)
    {
        case NORD:
            return OUEST;
        case SUD:
            return EST;
        case OUEST:
            return SUD;
        case EST:
            return NORD;
    }
}

Orientation rot_n_90(Orientation O, int n)
{
    for (int i = 0; i < n ; i++)
    {
        O = rot_90(O);
    }

    return O; 
}


Orientation calcul_orient(Image I, Robot R)
{
    Point pt_devant_gauche, pt_devant_droit; //coordonné des point devant gauche et devant droit du robot
    Pixel pix_devant_gauche, pix_devant_droit;

    //devant gauche et droit depandent de l'orientation du robot 
    switch(R.o)
    {
        case NORD:
            pt_devant_gauche = pixel_NW(R.pt);
            pt_devant_droit = pixel_NE(R.pt);
            break;
       case SUD:
            pt_devant_gauche = pixel_SE(R.pt);
            pt_devant_droit = pixel_SW(R.pt);
            break;
        case EST:
            pt_devant_gauche = pixel_NE(R.pt);
            pt_devant_droit = pixel_SE(R.pt);
            break;
        case OUEST:
            pt_devant_gauche = pixel_SW(R.pt);
            pt_devant_droit = pixel_NW(R.pt);
            break;
    }

    //recuperation de la couleur des pixel devant gauche et droit
    pix_devant_gauche = get_pixel_image(I, pt_devant_gauche.x, pt_devant_gauche.y);
    pix_devant_droit = get_pixel_image(I, pt_devant_droit.x, pt_devant_droit.y);

    switch (pix_devant_gauche)
    {
        case 0: //pixel blanc
            if (pix_devant_droit == 0)
               return  rot_n_90(R.o, 3); //on tourne 3 fois de 90 degres = 270
            else
                //si le pixel droit est noir alors on garde la meme orientation
                return R.o;
        case 1 : //pixel noir
            //on tourne dans les deux cas (pixel droit blanc ou noir) de 90 degres
            return rot_90(R.o);
    }
}


/* Calcul le contour de l'image et renvoie une liste chainé de chaque point de
** ce contour */
Contour calcul_contour(Image I)
{
    Robot R;
    Contour C;
    Point pos_pix, pos_point, pos_courante;
    bool boucle;

    pos_pix = calcul_pos_init(I); //position du PIXEL de départ
    pos_point = set_point(pos_pix.x - 1, pos_pix.y - 1);    //position du POINT de depart

    R = init_robot(pos_point); 
    pos_courante.x = R.pt.x; pos_courante.y = R.pt.y;

    C = creer_liste_Point_vide();

    boucle = true;

    while (boucle)
    {
        C = ajouter_element_liste_Point(C, pos_courante);
        R.pt = avancer_robot(R);
        pos_courante.x = R.pt.x; pos_courante.y = R.pt.y;
        R.o = calcul_orient(I, R);

        if (pos_courante.x == pos_point.x && pos_courante.y == pos_point.y && R.o == EST)
            boucle = false;
    }
    C = ajouter_element_liste_Point(C, pos_courante); //Pour ajouter la position intiale a la fin de la liste
    return C;
}




/* Calcul le contour de l'image et affiche a la volee son contour */
void calcul_contour_a_la_vole(Image I)
{
    Robot R;
    Point pos_pix, pos_point, pos_courante;
    bool boucle;

    pos_pix = calcul_pos_init(I); //position du PIXEL de départ
    pos_point = set_point(pos_pix.x - 1, pos_pix.y - 1);    //position du POINT de depart

    R = init_robot(pos_point); 
    pos_courante.x = R.pt.x; pos_courante.y = R.pt.y;

    boucle = true;

    while (boucle)
    {
        printf(" (%5.1f,%5.1f)", pos_courante.x, pos_courante.y);
        R.pt = avancer_robot(R);
        pos_courante.x = R.pt.x; pos_courante.y = R.pt.y;
        R.o = calcul_orient(I, R);

        if (pos_courante.x == pos_point.x && pos_courante.y == pos_point.y && R.o == EST)
            boucle = false;
    }
    printf(" (%5.1f,%5.1f)", pos_courante.x, pos_courante.y);
}




/********************************************************************************************/


/* fonction qui calcule et renvoi les coordonnées de la position initial du
** robot pour le calcul de l'image NEGATIVE
** quitte l'execution si il n'y a pas de point noir */
Point calcul_pos_init_neg(Image I)
{
    UINT i,j;
    Pixel p, p_1; //p_1 correspondra au pixel au dessu de p

    // i represente l'abscisse et j l'ordonnée
    for(j = 1 ; j <= hauteur_image(I) ; j++)
    {
        for (i = 1 ; i <= largeur_image(I) ; i++)
        {
            p = get_pixel_image_neg(I, i, j);
            p_1 = get_pixel_image_neg(I, i, j-1);

            if (p == BLANC && p_1 == NOIR)
                return set_point(i, j);
        }
    }

    //si on arrive ici c'est que l'image est toute blance et donc pas de contour
    ERREUR_FATALE("Il n'y a pas de pixel blanc dans cette image\n");

    return set_point(0,0);

}


Orientation calcul_orient_neg(Image I, Robot R)
{
    Point pt_devant_gauche, pt_devant_droit; //coordonné des point devant gauche et devant droit du robot
    Pixel pix_devant_gauche, pix_devant_droit;

    //devant gauche et droit depandent de l'orientation du robot 
    switch(R.o)
    {
        case NORD:
            pt_devant_gauche = pixel_NW(R.pt);
            pt_devant_droit = pixel_NE(R.pt);
            break;
       case SUD:
            pt_devant_gauche = pixel_SE(R.pt);
            pt_devant_droit = pixel_SW(R.pt);
            break;
        case EST:
            pt_devant_gauche = pixel_NE(R.pt);
            pt_devant_droit = pixel_SE(R.pt);
            break;
        case OUEST:
            pt_devant_gauche = pixel_SW(R.pt);
            pt_devant_droit = pixel_NW(R.pt);
            break;
    }

    //recuperation de la couleur des pixel devant gauche et droit
    pix_devant_gauche = get_pixel_image_neg(I, pt_devant_gauche.x, pt_devant_gauche.y);
    pix_devant_droit = get_pixel_image_neg(I, pt_devant_droit.x, pt_devant_droit.y);

    switch (pix_devant_gauche)
    {
        case 1: //pixel noir
            if (pix_devant_droit == 1)
               return  rot_n_90(R.o, 3); //on tourne 3 fois de 90 degres = 270
            else
                //si le pixel droit est noir alors on garde la meme orientation
                return R.o;
        case 0 : //pixel noir
            //on tourne dans les deux cas (pixel droit blanc ou noir) de 90 degres
            return rot_90(R.o);
    }
}


/* Calcul le contour de l'image NEGATIVES et renvoie une liste chainé de chaque point de
** ce contour */
Contour calcul_contour_neg(Image I)
{
    Robot R;
    Contour C;
    Point pos_pix, pos_point, pos_courante;
    bool boucle;

    pos_pix = calcul_pos_init_neg(I); //position du PIXEL de départ
    pos_point = set_point(pos_pix.x - 1, pos_pix.y - 1);    //position du POINT de depart

    R = init_robot(pos_point); 
    pos_courante.x = R.pt.x; pos_courante.y = R.pt.y;

    C = creer_liste_Point_vide();

    boucle = true;

    while (boucle)
    {
        C = ajouter_element_liste_Point(C, pos_courante);
        R.pt = avancer_robot(R);
        pos_courante.x = R.pt.x; pos_courante.y = R.pt.y;
        R.o = calcul_orient_neg(I, R);

        if (pos_courante.x == pos_point.x && pos_courante.y == pos_point.y && R.o == EST)
            boucle = false;
    }
    C = ajouter_element_liste_Point(C, pos_courante); //Pour ajouter la position intiale a la fin de la liste
    return C;
}


/*********************************************************************************************************************/
/***************************/
/* PARTIE CONTOUR MULTIPLE */
/***************************/


/* fonction qui calcule et renvoi l'image masque de l'image passé en parametre
** quitte l'execution si il n'y a pas de point noir */
Image calcul_image_masque(Image I)
{
    UINT i,j;
    Pixel p, p_1; //p_1 correspondra au pixel au dessu de p
    Image masque;   //image masque
    bool presence = false;  //pour savoir si il y a au moins un pixel noir dans l'image

    // création de l'image masque de hauteur et largeur égal à l'image passé e paramètre
    masque = creer_image(largeur_image(I), hauteur_image(I));

    // i represente l'abscisse et j l'ordonnée
    for(j = 1 ; j <= hauteur_image(I) ; j++)
    {
        for (i = 1 ; i <= largeur_image(I) ; i++)
        {
            p = get_pixel_image(I, i, j);
            p_1 = get_pixel_image(I, i, j-1);

            if (p == NOIR && p_1 == BLANC){
                set_pixel_image(masque, i, j, NOIR);
                presence = true;
            }
        }
    }

    if (!presence)
        ERREUR_FATALE("Il n'y a pas de pixel noir dans cette image\n");

    return masque;

}


/* Calcul un contour de l'image masque et le met dans le pointeur du contour
** passé en parametre
*/
/* Même chose que calcul contour mais avec la position initial passé en
** paramètre car elle dépend de l'image masque
** ET le fais que si le robot a pour orientation EST et est sur un pixel noir
** de l'image masque alors ce pixel deviens blance
*/
Contour calcul_contour_masque(Point pos_pix, Image masque, Image I)
{
    Robot R;
    Contour C;
    Point pos_point, pos_courante;
    bool boucle;

    set_pixel_image(masque, pos_pix.x, pos_pix.y, BLANC);

    C = creer_liste_Point_vide();
    pos_point = set_point(pos_pix.x - 1, pos_pix.y - 1);    //position du POINT de depart

    R = init_robot(pos_point); 
    pos_courante.x = R.pt.x; pos_courante.y = R.pt.y;


    boucle = true;

    while (boucle)
    {
        C = ajouter_element_liste_Point(C, pos_courante);
        R.pt = avancer_robot(R);
        pos_courante.x = R.pt.x; pos_courante.y = R.pt.y;
        R.o = calcul_orient(I, R);


        if (R.o == EST && get_pixel_image(masque, pos_courante.x+1, pos_courante.y+1) == NOIR)
            set_pixel_image(masque, pos_courante.x+1, pos_courante.y +1, BLANC);


        if (pos_courante.x == pos_point.x && pos_courante.y == pos_point.y && R.o == EST)
            boucle = false;
    }
    C = ajouter_element_liste_Point(C, pos_courante); //Pour ajouter la position intiale a la fin de la liste

    return C;
}




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

