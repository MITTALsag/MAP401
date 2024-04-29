#include <stdio.h>
#include <string.h>
#include <geom2d.h>
#include <types_macros.h>





/* Ce fichier test NE PREND PAS d'argument en ligne de commande mais demande a
** l'utilisateur de saisir 3 points (P puis A et en fin B) et calcul et affiche
** la distance entre P et le segement [AB]
*/



int main()
{
    Point P, A, B;
    coordonnee x, y;
    double dist;

    printf("Entrer les coordonnées du POINT P : ");
    scanf("%lf %lf", &x, &y);
    P = set_point(x, y);

    printf("Entrer les coordonnées du POINT A : ");
    scanf("%lf %lf", &x, &y);
    A = set_point(x, y);

    printf("Entrer les coordonnées du POINT B : ");
    scanf("%lf %lf", &x, &y);
    B = set_point(x, y);

    dist = calcul_distance_point_segment(P, A, B);

    printf(BLU"La discatnce entre P et S = [AB] est : d = %f\n"RESET, dist);

    return 0;
}



