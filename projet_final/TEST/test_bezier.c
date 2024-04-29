#include <stdio.h>
#include <math.h>
#include <bezier.h>
#include <geom2d.h>
#include <struct_liste.h>
#include <types_macros.h>



/* Fichier de tests unitaire du module bezier */

int main(void)
{
    Point C0, C1, C2;
    Bezier2 B;
    Tableau_Point CONT;
    double ti; int n; /* EXERCICE 6 de la feuille de TD */ C0 = set_point(0, 4);
    C1 = set_point(8, 8);
    C2 = set_point(4, 0);

    B = init_bezier2(C0, C1, C2);

    printf(BLU"EXERCICE 6 de la fauille de TD\n"RESET);

    Point P = calcul_bezier2(B, 0);
    printf("Le point C(0) a pour coordonnées : (%d,%d)\n",(int) P.x, (int)P.y);


    Point P2 = calcul_bezier2(B, 1);
    printf("Le point C(1) a pour coordonnées : (%d,%d)\n",(int) P2.x,(int) P2.y);

    // il faut que P3 = (5,5)
    Point P3 = calcul_bezier2(B, 0.5);
    printf("Le point C(1/2) a pour coordonnées : (%d,%d)\n",(int) P3.x,(int) P3.y);

    if (P3.x == 5 && P3.y == 5)
        printf(GRN"Le tests pour cette courbe est bon\n"RESET);
    else
        printf(RED"Le résultat n'est pas le bon a revoir !!!/n"RESET);



/*----------------------------------------------------------------------------------------------------------*/

    /* Tests pour approx_bezier2 */
    CONT = cree_Tableau_point_vide(2);
    C0 = set_point(0, 4); C1 = set_point(8, 6);
    CONT.tab[0] = C0 ; CONT.tab[1] = C1;

    B = approx_bezier2(CONT, 0, 1);

    printf(BLU"\nTEST approx_bezier2 (cas n = 1)\n"RESET);
    printf("Le point C0 a pour coordonnées : (%d,%d)\n",(int) B.C0.x,(int) B.C0.y);
    printf("Le point C1 a pour coordonnées : (%d,%d)\n",(int) B.C1.x,(int) B.C1.y);
    printf("Le point C2 a pour coordonnées : (%d,%d)\n",(int) B.C2.x,(int) B.C2.y);

    //resultat théorique
    Point c = mult_scalaire_point(add_point(C0, C1), 0.5);

    if (B.C1.x == c.x && B.C1.y == c.y)
        printf(GRN"Le test pour cette courbe de bezier pour n = 1 est bon\n"RESET);
    else
        printf(RED"Le résultat n'est pas le bon a revoir !!!/n"RESET);

    supprimer_Tableau_point (CONT);

/*----------------------------------------------------------------------------------------------------------*/

    printf(BLU"\nTEST approx_bezier2 (cas n ≥ 2), avec l'exemple de l'énnocé\n"RESET);
    n = 8;
    CONT = cree_Tableau_point_vide(n+1);
    C0 = set_point(0, 0);
    C2 = set_point(5,3);
    C1 = set_point(1.547619, 2.452381);
    B = init_bezier2(C0, C1, C2);
    for (int i = 0 ; i <= 8 ; i++)
    {
        ti = (double) i / (double) n;
        CONT.tab[i] = calcul_bezier2(B, ti);
    }

    Bezier2 B2 = approx_bezier2(CONT, 0, n);
    printf("Les points initiaux ont pour coordonnées : C0 = (%d,%d) C1 = (%lf,%lf) et C2 = (%d,%d)\n", (int) B.C0.x, (int) B.C0.y, B.C1.x, B.C1.y, (int) B.C2.x, (int) C2.y);


    printf("Les points finnaux ont pour coordonnées :\n");
    printf("Le point C0 a pour coordonnées : (%d,%d)\n",(int) B2.C0.x,(int) B2.C0.y);
    printf("Le point C1 a pour coordonnées : (%lf,%lf)\n", B2.C1.x, B2.C1.y);
    printf("Le point C2 a pour coordonnées : (%d,%d)\n",(int) B2.C2.x,(int) B2.C2.y);


    supprimer_Tableau_point (CONT);


    //Calcul des Ci,1 avec la formule du cours
    n = 8;
    CONT = cree_Tableau_point_vide(n+1);
    CONT.tab[0] = set_point(0,0);
    CONT.tab[1] = set_point(1,0);
    CONT.tab[2] = set_point(1,1);
    CONT.tab[3] = set_point(1,2);
    CONT.tab[4] = set_point(2,2);
    CONT.tab[5] = set_point(3,2);
    CONT.tab[6] = set_point(3,3);
    CONT.tab[7] = set_point(4,3);
    CONT.tab[8] = set_point(5,3);

    printf(BLU"\nCalcul des différents point Ci,1 pour i de 1 a n (exemple du cours\n"RESET);
    for (int i = 1 ; i < 8 ; i++)
    {
        ti = (double) i / (double) n;
        Point Ci;
        Ci.x = (CONT.tab[0+i].x - pow(1-ti, 2)*CONT.tab[0].x - pow(ti, 2)*CONT.tab[8].x)/(2*ti*(1-ti));
        Ci.y = (CONT.tab[0+i].y - pow(1-ti, 2)*CONT.tab[0].y - pow(ti, 2)*CONT.tab[8].y)/(2*ti*(1-ti));
        printf("Le point C%d,1 = (%lf,%lf)\n", i, Ci.x, Ci.y);
    }

    supprimer_Tableau_point (CONT);

/*----------------------------------------------------------------------------------------------------------*/
    //test de distance_point_bezier2
    printf(BLU"\nOn test mainentant la fonction de calcul de distance entre un point et une courbe de bezier\n"RESET);

    Tableau_Point tab = cree_Tableau_point_vide(9);
    tab.tab[0] = set_point(0,0);
    tab.tab[1] = set_point(1,0);
    tab.tab[2] = set_point(1,1);
    tab.tab[3] = set_point(1,2);
    tab.tab[4] = set_point(2,2);
    tab.tab[5] = set_point(3,2);
    tab.tab[6] = set_point(3,3);
    tab.tab[7] = set_point(4,3);
    tab.tab[8] = set_point(5,3);
    for (int i = 0 ; i <= n ; i++)
    {
        printf("distance entre le point P%d et B est : d(P%d, B) = %lf\n",i, i, distance_point_bezier2(tab.tab[i], B, (double)i/(double)n));
    }


    supprimer_Tableau_point (tab);

    //tous les tests sont bons

    return 1;
}
