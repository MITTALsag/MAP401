#include <stdio.h>
#include <math.h>
#include <bezier.h>
#include <geom2d.h>
#include <struct_liste.h>
#include <types_macros.h>



/* Fichier de tests unitaire du module bezier */

int main(void)
{
    Point C0, C1, C2, C3;
    Bezier3 B;
    Tableau_Point CONT;
    double ti; int n; 

    /* Tests pour approx_bezier3 */
    CONT = cree_Tableau_point_vide(2);
    C0 = set_point(0, 4); C1 = set_point(8, 6);
    CONT.tab[0] = C0 ; CONT.tab[1] = C1;

    B = approx_bezier3(CONT, 0, 1);

    printf(BLU"\nTEST approx_bezier3 (cas n = 1)\n"RESET);
    printf("Le point C0 a pour coordonnées : (%d,%d)\n",(int) B.C0.x,(int) B.C0.y);
    printf("Le point C1 a pour coordonnées : (%d,%d)\n",(int) B.C1.x,(int) B.C1.y);
    printf("Le point C2 a pour coordonnées : (%d,%d)\n",(int) B.C2.x,(int) B.C2.y);
    printf("Le point C3 a pour coordonnées : (%d,%d)\n",(int) B.C3.x,(int) B.C3.y);

    //resultat théorique
    Point c = mult_scalaire_point(add_point(mult_scalaire_point(C0, 2), C1), (double)1/3);
    Point c2 = mult_scalaire_point(add_point(mult_scalaire_point(C1, 2), C0), (double)1/3);

    if (B.C1.x == c.x && B.C1.y == c.y && B.C2.x == c2.x && B.C2.y == c2.y)
        printf(GRN"Le test pour cette courbe de bezier pour n = 1 est bon\n"RESET);
    else
        printf(RED"Le résultat n'est pas le bon a revoir !!!/n"RESET);

    supprimer_Tableau_point (CONT);

/*----------------------------------------------------------------------------------------------------------*/


    /* Tests pour approx_bezier3 cas n = 2 */
    CONT = cree_Tableau_point_vide(3);
    C0 = set_point(0, 4); C1 = set_point(8, 6); C2 = set_point(10,8);
    CONT.tab[0] = C0 ; CONT.tab[1] = C1; CONT.tab[2] = C2;

    B = approx_bezier3(CONT, 0, 2);

    printf(BLU"\nTEST approx_bezier3 (cas n = 2)\n"RESET);
    printf("Le point C0 a pour coordonnées : (%d,%d)\n",(int) B.C0.x,(int) B.C0.y);
    printf("Le point C1 a pour coordonnées : (%d,%d)\n",(int) B.C1.x,(int) B.C1.y);
    printf("Le point C2 a pour coordonnées : (%d,%d)\n",(int) B.C2.x,(int) B.C2.y);
    printf("Le point C3 a pour coordonnées : (%d,%d)\n",(int) B.C3.x,(int) B.C3.y);

    //resultat théorique
     c = mult_scalaire_point(add_point(mult_scalaire_point(C1, 4), mult_scalaire_point(C2, -1)), (double)1/3);
     c2 = mult_scalaire_point(add_point(mult_scalaire_point(C1, 4), mult_scalaire_point(C0, -1)), (double)1/3);

    if (B.C1.x == c.x && B.C1.y == c.y && B.C2.x == c2.x && B.C2.y == c2.y)
        printf(GRN"Le test pour cette courbe de bezier pour n = 1 est bon\n"RESET);
    else
        printf(RED"Le résultat n'est pas le bon a revoir !!!/n"RESET);

    supprimer_Tableau_point (CONT);

/*----------------------------------------------------------------------------------------------------------*/


    printf(BLU"\nTEST approx_bezier3 (cas n ≥ 3), avec l'exemple de l'énnocé\n"RESET);
    n = 8;
    CONT = cree_Tableau_point_vide(n+1);
    C0 = set_point(0, 0);
    C1 = set_point(1.737287,0.929380);
    C2 = set_point(1.844176,3.489158);
    C3 = set_point(5,3);
    B = init_bezier3(C0, C1, C2, C3);

    for (int i = 0 ; i <= n ; i++)
    {
        ti = (double) i / (double) n;
        CONT.tab[i] = calcul_bezier3(B, ti);
    }

    Bezier3 B2 = approx_bezier3(CONT, 0, n);
    printf("Les points initiaux ont pour coordonnées : C0 = (%d,%d) C1 = (%lf,%lf), C2 = (%lf,%lf) et C3 = (%d,%d)\n", (int) B.C0.x, (int) B.C0.y, B.C1.x, B.C1.y, B.C2.x, B.C2.y, (int) B.C3.x, (int) C3.y);


    printf("Les points finnaux ont pour coordonnées :\n");
    printf("Le point C0 a pour coordonnées : (%d,%d)\n",(int) B2.C0.x,(int) B2.C0.y);
    printf("Le point C1 a pour coordonnées : (%lf,%lf)\n", B2.C1.x, B2.C1.y);
    printf("Le point C2 a pour coordonnées : (%lf,%lf)\n", B2.C2.x, B2.C2.y);
    printf("Le point C3 a pour coordonnées : (%d,%d)\n",(int) B2.C3.x,(int) B2.C3.y);


    supprimer_Tableau_point (CONT);


/*----------------------------------------------------------------------------------------------------------*/
    //test de distance_point_bezier2
    printf(BLU"\nTest de la fonction de calcul de distance entre un point et une courbe de bezier\n"RESET);

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
        printf("distance entre le point P%d et B est : d(P%d, B) = %lf\n",i, i, distance_point_bezier3(tab.tab[i], B, (double)i/(double)n));
    }


    supprimer_Tableau_point (tab);

    //tous les tests sont bons

    return 1;
}
