#include <stdio.h>
#include <math.h>
#include <bezier.h>
#include <geom2d.h>
#include <types_macros.h>
#include <contour.h>


/*--------------------------------------------------------------------------------------------------------*/

/****************************/
/* FONCTION BEZIER DEGRES 2 */
/****************************/


/*initialisation de courbe de bezier de degres 2*/
Bezier2 init_bezier2(Point C0, Point C1, Point C2)
{
    Bezier2 B = {C0, C1, C2};
    return B;
}


/* Cette fonction calcul C(t) pour t entre [0 et 1] et pour une courbe de
** bezier de degres 2
*/
Point calcul_bezier2(Bezier2 B, double t)
{
    if (t<0 || t > 1)
        ERREUR_FATALE(RED"Erreur dans calcul_bezier2 : t doit etre compris entre 0 et 1 (inclus)\n");
    return add_point(add_point(mult_scalaire_point(B.C0, pow(1-t, 2)), mult_scalaire_point(B.C1, 2*(1-t)*t)), mult_scalaire_point(B.C2, pow(t, 2)));
}


/* CETTE fonction approxime le contour polygonal CONT par une courbe de bezier
** de degres 2
*/
Bezier2 approx_bezier2(Tableau_Point CONT, UINT j1, UINT j2)
{
    int n = j2 - j1;
    Point P, C1;
    double alpha, beta;

    if (n <= 0)
        ERREUR_FATALE(RED"Erreur approx_bezier2 : erreur dans le passage des indice (j1 < j2)\n"RESET);


    //cas n = 1
    if (n == 1)
    {
        C1 = mult_scalaire_point(add_point(CONT.tab[j1], CONT.tab[j2]), 0.5);
        return init_bezier2(CONT.tab[j1], C1, CONT.tab[j2]);
    }

    //si n ≥ 2

    //cacul de la somme des Pj
    P = set_point(0, 0);
    for (int i = 1; i <= n-1; i++)
    {
        P = add_point(CONT.tab[j1+i], P);
    }

    //calcul de alpha et beta
    alpha = (3* (double) n)/(pow((double) n, 2) - 1);
    beta = (1 - 2* (double) n )/(2*((double) n +1));

    C1 = add_point(mult_scalaire_point(P, alpha), mult_scalaire_point(add_point(CONT.tab[j1], CONT.tab[j2]), beta));

        return init_bezier2(CONT.tab[j1], C1, CONT.tab[j2]);


}


/* Cette fonction calcul et renvoie la distance entre le point P et la courbe
** de bezier de degres 2 B 
*/
double distance_point_bezier2(Point P, Bezier2 B, double t)
{
    Point Ct;
    Ct = calcul_bezier2(B, t);
    return distance(P, Ct);

}



/*--------------------------------------------------------------------------------------------------------*/

/****************************/
/* FONCTION BEZIER DEGRES 3 */
/****************************/



/*initialisation de courbe de bezier de degres 3*/
Bezier3 init_bezier3(Point C0, Point C1, Point C2, Point C3)
{
    Bezier3 B = {C0, C1, C2, C3};
    return B;
}



/* Cette fonction calcul C(t) pour t entre [0 et 1] et pour une courbe de
** bezier de degres 3
*/
Point calcul_bezier3(Bezier3 B, double t)
{
    if (t<0 || t > 1)
        ERREUR_FATALE(RED"Erreur dans calcul_bezier2 : t doit etre compris entre 0 et 1 (inclus)\n");
    return add_point(add_point(mult_scalaire_point(B.C0, pow(1-t, 3)), mult_scalaire_point(B.C1, 3*pow(1-t, 2)*t)), add_point(mult_scalaire_point(B.C2, 3*pow(t, 2)*(1-t)), mult_scalaire_point(B.C3, pow(t, 3))));
}



/*Cette fonction convertis une courbe de bezier de degres 2 en courbe de bezier
** de degres 3 par elevation au degres
*/
Bezier3 elevation_degre(Bezier2 B)
{
   Point D0, D1, D2, D3;
   D0 = B.C0;
   D3 = B.C2;
   D1 = add_point(mult_scalaire_point(B.C0,(double)1/3), mult_scalaire_point(B.C1, (double)2/3));
   D2 = add_point(mult_scalaire_point(B.C2,(double)1/3), mult_scalaire_point(B.C1, (double)2/3));

   return init_bezier3(D0, D1, D2, D3);
}


/* fonction qui sert dans approx_bezier3 */
double gamma(double k, double n)
{
    return (6*pow(k, 4) - 8*n*pow(k,3) + 6*pow(k,2) - 4*n*k + pow(n,4) - pow(n,2));
}

/* CETTE fonction approxime le contour polygonal CONT par une courbe de bezier
** de degres 3
*/
Bezier3 approx_bezier3(Tableau_Point CONT, UINT j1, UINT j2)
{
    int n = j2 - j1;
    Point P, C1, C2;
    double alpha, beta, lambda;
    double n2;

    if (n <= 0)
        ERREUR_FATALE(RED"Erreur approx_bezier2 : erreur dans le passage des indice (j1 < j2)\n"RESET);

    //cas n = 1
    if (n == 1)
    {
        C1 = mult_scalaire_point(add_point(mult_scalaire_point(CONT.tab[j1], 2), CONT.tab[j2]), (double)1/3);
        C2 = mult_scalaire_point(add_point(mult_scalaire_point(CONT.tab[j2], 2), CONT.tab[j1]), (double)1/3);
        return init_bezier3(CONT.tab[j1], C1, C2, CONT.tab[j2]);
    }
    if (n == 2)
    {
        C1 = mult_scalaire_point(add_point(mult_scalaire_point(CONT.tab[j1+1], 4), mult_scalaire_point(CONT.tab[j2], -1)), (double)1/3);
        C2 = mult_scalaire_point(add_point(mult_scalaire_point(CONT.tab[j1+1], 4), mult_scalaire_point(CONT.tab[j1], -1)), (double)1/3);
        return init_bezier3(CONT.tab[j1], C1, C2, CONT.tab[j2]);
    }

    //si n ≥ 3

    n2 = (double) n;

    //calcul de alpha et beta
    alpha = (-15*pow(n2,3) + 5*pow(n2, 2) + 2*n2 +4)/(3*(n2+2)*(3*pow(n2,2) +1));
    beta = (10*pow(n2,3) - 15*pow(n2,2) + n2 + 2)/(3*(n2+2)*(3*pow(n2, 2) +1));
    lambda = 70*n2/(3*(pow(n2,2)-1)*(pow(n2,2)-4)*(3*pow(n2,2)+1));

    //cacul de la somme de C1
    P = set_point(0, 0);
    for (int i = 1; i <= n-1; i++)
    {
        P = add_point(mult_scalaire_point(CONT.tab[j1+i], gamma((double) i,  n2)), P);
    }

    P = mult_scalaire_point(P, lambda);

    C1 = add_point(add_point(mult_scalaire_point(CONT.tab[j1], alpha), P), mult_scalaire_point(CONT.tab[j2], beta));

    //cacul de la somme de C2
    P = set_point(0, 0);
    for (int i = 1; i <= n-1; i++)
    {
        P = add_point(mult_scalaire_point(CONT.tab[j1+i], gamma((double) (n-i),  n2)), P);
    }

    P = mult_scalaire_point(P, lambda);

    C2 = add_point(add_point(mult_scalaire_point(CONT.tab[j1], beta), P), mult_scalaire_point(CONT.tab[j2], alpha));

    return init_bezier3(CONT.tab[j1], C1, C2, CONT.tab[j2]);
}




/* Cette fonction calcul et renvoie la distance entre le point P et la courbe
** de bezier de degres 3 B 
*/
double distance_point_bezier3(Point P, Bezier3 B, double t)
{
    Point Ct;
    Ct = calcul_bezier3(B, t);
    return distance(P, Ct);

}

