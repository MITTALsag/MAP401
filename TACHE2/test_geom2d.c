#include <stdio.h>
#include <assert.h>
#include "geom2d.h"

//A FINIR
//Fichier de tests unitaire du module geom2d

int unit_test_point(Point P, coordonnee x, coordonnee y)
{
    assert(P.x == x);
    assert(P.y == y);

    return 0;
}

int unit_test_vecteur(Vecteur P, coordonnee x, coordonnee y)
{
    assert(P.x == x);
    assert(P.y == y);

    return 0;
}


int unit_test_double(double d, double res_att)
{
    assert(d == res_att);

    return 0;
}

int main(void)
{
    Point P = set_point(0,0); // point origine
    Point P2 = set_point(343.24334, 4567.45785);
    Vecteur V1 = vect_bipoint(P, P); //vecteur nul
    Vecteur V2 = vect_bipoint(set_point(1, 3), set_point(4, 5)); //vecteur (3,2)
    //double d;

    unit_test_point(P, 0, 0);
    unit_test_point(P2,343.24334, 4567.45785);

    unit_test_vecteur(V2, 3, 2);
    unit_test_vecteur(V1, 0, 0);

    unit_test_point(mult_scalaire_point(P, 4), 0, 0);
    unit_test_point(mult_scalaire_point(set_point(345, 456), 4),345*4, 456*4);



    unit_test_vecteur(mult_scalaire_vect(V1, 4), 0, 0);
    unit_test_vecteur(mult_scalaire_vect(V2, 3.5), 3*3.5, 2*3.5);
    return 0;
}
