#include <stdio.h>
#include <assert.h>
#include <geom2d.h>

//Fichier de tests unitaire du module geom2d

/* test unitaires pour les points */
int unit_test_point(Point P, coordonnee x, coordonnee y)
{
    assert(P.x == x);
    assert(P.y == y);

    return 0;
}


/* test unitaires pour les vecteurs */
int unit_test_vecteur(Vecteur P, coordonnee x, coordonnee y)
{
    assert(P.x == x);
    assert(P.y == y);

    return 0;
}

/* test unitaires pour les double */
int unit_test_double(double d, double res_att)
{
    assert(d == res_att);

    return 0;
}

int main(void)
{
    /* Initialisation des points et vecteurs pour les tests */
    Point P = set_point(0,0); // point origine
    Point P2 = set_point(4, 3); //point P2 = (4,3)
    Vecteur V1 = vect_bipoint(P, P); //vecteur nul
    Vecteur V2 = vect_bipoint(set_point(1, 2), set_point(5, 5)); //vecteur (4,3)

    /* Test sur les points */
    unit_test_point(P, 0, 0);
    unit_test_point(P2,4, 3);
    unit_test_point(add_point(P, P2),P2.x,P2.y);
    unit_test_point(mult_scalaire_point(P, 3), 0, 0);
    unit_test_point(mult_scalaire_point(P2, 5), 5*P2.x, 5*P2.y);
    unit_test_double(distance(P, P2), 5);
    printf(GRN"Tous les tests manuel des point se sont bien passé\n"RESET);

    /* Test sur les vecteurs */
    unit_test_vecteur(V2, 4, 3);
    unit_test_vecteur(V1, 0, 0);
    unit_test_vecteur(add_vect(V1, V2), V2.x, V2.y);
    unit_test_vecteur(mult_scalaire_vect(V1, 4), 0, 0);
    unit_test_vecteur(mult_scalaire_vect(V2, 4),V2.x*4, V2.y*4);
    unit_test_vecteur(mult_scalaire_vect(V2, 3.5), 4*3.5, 3*3.5);
    unit_test_double(prod_scal(V1, V2), 0);
    unit_test_double(prod_scal(V2, V2), 25);
    unit_test_double(norme(V1), 0);
    unit_test_double(norme(V2), 5);
    printf(GRN"Tous les tests manuel des vecteurs se sont bien passé\n"RESET);

    /* test manuel (celui de l'énoncé) */
    Point A, B, C; Vecteur U;
    A = set_point(1.0, -3.0);
    B = set_point(4.0, 1.0);
    C = add_point (A, B); /* −−> C = ( 5 .0 , −2 .0) */
    if (C.x != 5. || C.y != -2.){
        printf(GRN"ERREUR DANS add_point avec les points A = (1., -3.) et B = (4., 1.)\n"RESET);
        return 1;
    }

    U = vect_bipoint(C, A); /* −−> U = ( −4 .0 , −1 .0) */

    if (U.x != -4. || U.y != -1.){
        printf(GRN"ERREUR DANS vect_bipoint avec les points C = (5., -2.) et A = (1., -3.)\n"RESET);
        return 1;
    }

    printf(GRN"Le test de l'énoncé s'est bien dérouler \n"RESET);


    return 0;
}
