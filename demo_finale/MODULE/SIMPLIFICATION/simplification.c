#include <stdio.h>
#include <struct_liste.h>
#include <geom2d.h>
#include <types_macros.h>
#include <contour.h>
#include <bezier.h>


/*
- simplifier la partie du contour CONT compris entre les indices j1 et j2 avec la distance-seuil d
- la fonction renvoie la s´equence de segments L
- procedure recursive de type ”diviser pour r´egner” (”divide and conquer”)
*/
Contour simplification_douglas_peucker(Tableau_Point CONT, UINT j1, UINT j2, float d)
{

    // Il faut que j1 < j2
    if (j1 >= j2)
        ERREUR_FATALE(RED"Erreur avec les indices j1 et j2 dans la fonction simplification_segemnt"RESET);

    UINT k; //indice du point le plus éloigné du segment [Pj1 Pj2]
    float dmax, dj; //distance entre Pk et le segment [Pj1 Pj2]
    UINT j; //variable temporaire
    Point P, A, B;

/*
- (1) rechercher le point Pk le plus eloigne du segment S
- ainsi que la distance dmax correspondante
*/
    dmax = 0;
    k = j1;

    for (j = j1 + 1; j <= j2; j++)
    {
        P = CONT.tab[j];
        A = CONT.tab[j1];
        B = CONT.tab[j2];

        dj = calcul_distance_point_segment(P, A, B);

        if(dmax < dj)
        {
            dmax = dj;
            k = j;
        }

    }


    if (dmax <= d)
    {
        //- (2) dmax ≤ d : simplification suivant le segment S 
        Contour C = creer_liste_Point_vide();
        C = ajouter_element_liste_Point(C, CONT.tab[j1]);
        C = ajouter_element_liste_Point(C, CONT.tab[j2]);
        return C;
    }
    else 
    {
        //- (3) dmax > d : ”diviser pour regner"

        //- (3.1) d´ecomposer le probl`eme en deux
        //- simplifier la partie du contour CONT compris entre les indices j1 et k avec la distance-seuil d
        Contour C1 = simplification_douglas_peucker(CONT, j1, k, d);

        //- simplifier la partie du contour CONT compris entre les indices k et j2 avec la distance-seuil d
        Contour C2 = simplification_douglas_peucker(CONT, k, j2, d);

        //- (3.2) fusionner les deux s´equences L1 et L2 et les renvoyer
        return concatener_liste_Point(C1, C2);

    }

}


/* Cette procédure prend en argument :
    - le nom d'un fichier contour n1
    - le nom d'un fichier de sortie n2
    - un reel d
Puis calcul grace a l'algorithme de Douglas Peucker la simplification de n1 et met le resultat dans n2.
Cette fonction fais les calcul a la volé : c'est a dire pour chacun des contour de n1 elle va calculer sa simplification puis le mettre dans n2 avant de passer au contour suivant.
*/
void simplification_segment(char* nom_fichier_entree,char* nom_fichier_sortie, float d)
{

    UINT nb_contour, taille_contour, nb_segment;
    Tableau_Point Cont;
    Point P;
    Contour L;
    UINT i, j;

    FILE* f = fopen(nom_fichier_entree, "r");
    if (!f)
        ERREUR_FATALE(RED"ERREUR simplification_image : le fichier d'entree n'a pas pu être ouvert"RESET);

    fscanf(f, "%d\n\n", &nb_contour);


    FILE* fich = fopen(nom_fichier_sortie, "w"); //fichier de sortie avec le contour simplififer
    if (!f)
        ERREUR_FATALE(RED"ERREUR simplification_image : le fichier de sortie n'a pas pu être ouvert"RESET);

    fprintf(fich, "%d                  \n\n", nb_contour);
    nb_segment = 0;
    for (i = 0; i < nb_contour; i++)
    {
        fscanf(f, "%d\n", &taille_contour);
        Cont = cree_Tableau_point_vide(taille_contour);

        for (j = 0; j < taille_contour; j++)
        {
            fscanf(f, "%lf %lf\n", &P.x, &P.y);
            Cont.tab[j] = P;
        }

        L = simplification_douglas_peucker(Cont, 0, taille_contour-1, d);
        nb_segment += (L.taille/2);
        Cont = supprimer_Tableau_point(Cont);
        ecrire_Contour_fichier(&L, fich);

    }

    printf(BLU"Le contour simplifié contient %d segements\n"RESET, nb_segment);
    fclose(f);
    fclose(fich);

}





/*
- simplifier la partie du contour CONT compris entre les indices j1 et j2 avec la distance-seuil d
- la fonction renvoie la s´equence de segments L contenant des point desitiné a etre des courbe de bezier de degres 2
- procedure recursive de type ”diviser pour r´egner” (”divide and conquer”)
*/
Contour simplification_douglas_peucker_bezier2(Tableau_Point CONT, UINT j1, UINT j2, UINT d)
{

    // Il faut que j1 < j2
    if (j1 >= j2)
        ERREUR_FATALE(RED"Erreur avec les indices j1 et j2 dans la fonction simplification_segemnt"RESET);

    UINT k; //indice du point le plus éloigné du segment [Pj1 Pj2]
    double dmax, dj; //distance entre Pk et le segment [Pj1 Pj2]
    UINT i,j; //variable temporaire
    int n;
    double ti;
    Bezier2 B;

    n = j2 - j1; //-- nombre de segments de CONT entre les indices j1 et j2

    //-- (0) approcher la s´equence de n + 1 points CONT(j1..j2) par une B´ezier B de degr´e 2
    B = approx_bezier2(CONT, j1, j2);



/*
- (1) rechercher le point Pk le plus eloigne de la bezier B
- ainsi que la distance dmax correspondante
*/
    dmax = 0;
    k = j1;

    for (j = j1 + 1; j <= j2; j++)
    {
        i = j-j1;
        ti = (double)i/(double)n;

        dj = distance_point_bezier2(CONT.tab[j], B, ti);

        if(dmax < dj)
        {
            dmax = dj;
            k = j;
        }

    }


    if (dmax <= d)
    {
        //-- (2) dmax ≤ d : simplification suivant la B´ezier B
        Contour C = creer_liste_Point_vide();
        C = ajouter_element_liste_Point(C, B.C0);
        C = ajouter_element_liste_Point(C, B.C1);
        C = ajouter_element_liste_Point(C, B.C2);
        return C;
    }
    else
    {
        //- (3) dmax > d : ”diviser pour regner"

        //- (3.1) d´ecomposer le probl`eme en deux
        //- simplifier la partie du contour CONT compris entre les indices j1 et k avec la distance-seuil d
        Contour C1 = simplification_douglas_peucker_bezier2(CONT, j1, k, d);

        //- simplifier la partie du contour CONT compris entre les indices k et j2 avec la distance-seuil d
        Contour C2 = simplification_douglas_peucker_bezier2(CONT, k, j2, d);

        //- (3.2) fusionner les deux s´equences L1 et L2 et les renvoyer
        return concatener_liste_Point(C1, C2);

    }

}




/* Cette procédure prend en argument :
    - le nom d'un fichier contour n1
    - le nom d'un fichier de sortie n2
    - un reel d
Puis calcul grace a l'algorithme de Douglas Peucker  pour le scourbe de bezier 2 la simplification de n1 et met le resultat dans n2.
Cette fonction fais les calcul a la volé : c'est a dire pour chacun des contour de n1 elle va calculer sa simplification puis le mettre dans n2 avant de passer au contour suivant.
*/
void simplification_bezier2(char* nom_fichier_entree, char* nom_fichier_sortie, float d)
{

    UINT nb_contour, taille_contour;
    Tableau_Point Cont;
    Point P;
    Contour L;
    UINT i, j;

    FILE* f = fopen(nom_fichier_entree, "r");
    if (!f)
        ERREUR_FATALE(RED"ERREUR simplification_bezier2 : le fichier d'entree n'a pas pu être ouvert"RESET);

    fscanf(f, "%d\n\n", &nb_contour);


    FILE* fich = fopen(nom_fichier_sortie, "w"); //fichier de sortie avec le contour simplififer
    if (!f)
        ERREUR_FATALE(RED"ERREUR simplification_bezier2 : le fichier de sortie n'a pas pu être ouvert"RESET);

    fprintf(fich, "%d                  \n\n", nb_contour);

    for (i = 0; i < nb_contour; i++)
    {
        fscanf(f, "%d\n", &taille_contour);
        Cont = cree_Tableau_point_vide(taille_contour);

        for (j = 0; j < taille_contour; j++)
        {
            fscanf(f, "%lf %lf\n", &P.x, &P.y);
            Cont.tab[j] = P;
        }

        L = simplification_douglas_peucker_bezier2(Cont, 0, taille_contour-1, d);
        Cont = supprimer_Tableau_point(Cont);
        ecrire_Contour_fichier(&L, fich);

    }

    fclose(f);
    fclose(fich);

}




/*
- simplifier la partie du contour CONT compris entre les indices j1 et j2 avec la distance-seuil d
- la fonction renvoie la s´equence de segments L contenant des point desitiné a etre des courbe de bezier de degres 3
- procedure recursive de type ”diviser pour r´egner” (”divide and conquer”)
*/
Contour simplification_douglas_peucker_bezier3(Tableau_Point CONT, UINT j1, UINT j2, UINT d)
{

    // Il faut que j1 < j2
    if (j1 >= j2)
        ERREUR_FATALE(RED"Erreur avec les indices j1 et j2 dans la fonction simplification_segemnt"RESET);

    UINT k; //indice du point le plus éloigné du segment [Pj1 Pj2]
    double dmax, dj; //distance entre Pk et le segment [Pj1 Pj2]
    UINT i,j; //variable temporaire
    int n;
    double ti;
    Bezier3 B;

    n = j2 - j1; //-- nombre de segments de CONT entre les indices j1 et j2

    //-- (0) approcher la s´equence de n + 1 points CONT(j1..j2) par une B´ezier B de degr´e 2
    B = approx_bezier3(CONT, j1, j2);



/*
- (1) rechercher le point Pk le plus eloigne de la bezier B
- ainsi que la distance dmax correspondante
*/
    dmax = 0;
    k = j1;

    for (j = j1 + 1; j <= j2; j++)
    {
        i = j-j1;
        ti = (double)i/(double)n;

        dj = distance_point_bezier3(CONT.tab[j], B, ti);

        if(dmax < dj)
        {
            dmax = dj;
            k = j;
        }

    }


    if (dmax <= d)
    {
        //-- (2) dmax ≤ d : simplification suivant la B´ezier B
        Contour C = creer_liste_Point_vide();
        C = ajouter_element_liste_Point(C, B.C0);
        C = ajouter_element_liste_Point(C, B.C1);
        C = ajouter_element_liste_Point(C, B.C2);
        C = ajouter_element_liste_Point(C, B.C3);
        return C;
    }
    else
    {
        //- (3) dmax > d : ”diviser pour regner"

        //- (3.1) d´ecomposer le probl`eme en deux
        //- simplifier la partie du contour CONT compris entre les indices j1 et k avec la distance-seuil d
        Contour C1 = simplification_douglas_peucker_bezier3(CONT, j1, k, d);

        //- simplifier la partie du contour CONT compris entre les indices k et j2 avec la distance-seuil d
        Contour C2 = simplification_douglas_peucker_bezier3(CONT, k, j2, d);

        //- (3.2) fusionner les deux s´equences L1 et L2 et les renvoyer
        return concatener_liste_Point(C1, C2);

    }

}


/* Cette procédure prend en argument :
    - le nom d'un fichier contour n1
    - le nom d'un fichier de sortie n2
    - un reel d
Puis calcul grace a l'algorithme de Douglas Peucker  pour le scourbe de bezier 3 la simplification de n1 et met le resultat dans n2.
Cette fonction fais les calcul a la volé : c'est a dire pour chacun des contour de n1 elle va calculer sa simplification puis le mettre dans n2 avant de passer au contour suivant.
*/
void simplification_bezier3(char* nom_fichier_entree, char* nom_fichier_sortie, float d)
{

    UINT nb_contour, taille_contour;
    Tableau_Point Cont;
    Point P;
    Contour L;
    UINT i, j;

    FILE* f = fopen(nom_fichier_entree, "r");
    if (!f)
        ERREUR_FATALE(RED"ERREUR simplification_bezier2 : le fichier d'entree n'a pas pu être ouvert"RESET);

    fscanf(f, "%d\n\n", &nb_contour);


    FILE* fich = fopen(nom_fichier_sortie, "w"); //fichier de sortie avec le contour simplififer
    if (!f)
        ERREUR_FATALE(RED"ERREUR simplification_bezier2 : le fichier de sortie n'a pas pu être ouvert"RESET);

    fprintf(fich, "%d                  \n\n", nb_contour);

    for (i = 0; i < nb_contour; i++)
    {
        fscanf(f, "%d\n", &taille_contour);
        Cont = cree_Tableau_point_vide(taille_contour);

        for (j = 0; j < taille_contour; j++)
        {
            fscanf(f, "%lf %lf\n", &P.x, &P.y);
            Cont.tab[j] = P;
        }

        L = simplification_douglas_peucker_bezier3(Cont, 0, taille_contour-1, d);
        Cont = supprimer_Tableau_point(Cont);
        ecrire_Contour_fichier(&L, fich);

    }

    fclose(f);
    fclose(fich);

}


