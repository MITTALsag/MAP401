#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> 
#include <geom2d.h>




/* renvoie un Double avec 15 chiffre apres la virgule */
double randomDouble()
{
    int max = 100;
    // x est un nombre pseudo aléatoire entre 0 et max
    double x = ((double)rand() / (double)RAND_MAX) * max; 
    return x;
}

/* renvoie un double sous forme d'entier par ex : 2. = 2 */
double randomInt()
{
    return (double)(rand() % 100);
}

/* fonction qui verifie chaque fonction une fois grace a 4 coordonnées */
int test_all_fonction(int nb_test, int coef, bool test_double){
    double result, lambda;
    Point A, B, C; 
    Vecteur U, W, V;
    coordonnee x1, x2, y1, y2;

    for (int i = 0; i < nb_test; i++) {

        //generation aleatoire de coordonnées 
        if (test_double) /* test avec des double */
        {
            x1 = coef * randomDouble();
            x2 = coef * randomDouble();
            y1 = coef * randomDouble();
            y2 = coef * randomDouble();
            lambda = coef * randomDouble();
        }
        else /* test avec des entier positif */
        {
            x1 = coef * randomInt();
            x2 = coef * randomInt();
            y1 = coef * randomInt();
            y2 = coef * randomInt();
            lambda = coef * randomInt();
        }

        /******************************/
        /* tests des fonctions points */
        /******************************/

        A = set_point (x1, y1);
        B = set_point (x2, y2);

        if (A.x != x1 || A.y != y1){
            printf(RED"ERREUR DANS set_point avec le point A = (%f, %f)\n"RESET, x1, y1);
            return 1;
        }

        if (B.x != x2 || B.y != y2){
            printf(RED"ERREUR DANS set_point avec le point B = (%f, %f)\n"RESET, x2, y2);
            return 1;
        }


        C = add_point(A, B);

        if (C.x != x1 + x2 || C.y != y1 + y2){
            printf(RED"ERREUR DANS add_point avec les points A = (%f, %f) et B = (%f, %f)\n", x1, y1, x2, y2);
            return 1;
        }

        C = mult_scalaire_point(A, lambda);

        if (C.x != lambda * x1 || C.y != lambda * y1){
            printf(RED"ERREUR DANS mult_scalaire_point avec le points A = (%f, %f)\n"RESET, x1, y1);
            return 1;
        }

        result = distance(A, B);

        if (result != sqrt(pow(x1 - x2, 2.) + pow(y1 - y2, 2.))){
            printf(RED"ERREUR DANS norme avec les points A = (%f, %f) et B = (%f, %f)\n"RESET, x1, y1, x2, y2);
            return 1;
        }

        /*******************************/
        /* tests des fonctions vecteur */
        /*******************************/

        //creation d'un vecteur bipoint
        U = vect_bipoint(A, B);
        if (U.x != x2 - x1 || U.y != y2 - y1){
            printf(RED"ERREUR DANS vect_bipoint avec les points A = (%f, %f) et B = (%f, %f)\n"RESET, x1, y1, x2, y2);
            return 1;
        }

        x1 = U.x; y1 = U.y;

        //creation d'un vecteur uni point
        V.x = A.x;
        V.y = A.y;

        x2 = V.x; y2 = V.y;

        W = add_vect(U, V);
        if (W.x != x1 + x2 || W.y != y1 + y2){
            printf(RED"ERREUR DANS add_vect avec les vecteurs U = (%f, %f) et V = (%f, %f)\n"RESET, x1, y1, x2, y2);
            return 1;
        }

        W = mult_scalaire_vect(U, lambda);
        if (W.x != lambda * x1 || W.y != lambda * y1){
            printf(RED"ERREUR DANS mult_scalaire_vect avec le vecteur U = (%f, %f)\n"RESET, x1, y1);
            return 1;
        }

        result = prod_scal(U, V);
        if (result != x1*x2 + y1*y2){
            printf(RED"ERREUR DANS prod_scal avec les vecteurs U = (%f, %f) et V = (%f, %f)\n"RESET, x1, y1, x2, y2);
            return 1;
        }

        result = norme(U);
        if (result != sqrt(x1*x1 + y1*y1)){
            printf(RED"ERREUR DANS norme avec les vecteurs U = (%f, %f)\n"RESET, x1, y1);
            return 1;
        }

    }

    return 0;
}


int main(void){
    
    srand(time(NULL));
    double result;
    int nb_test;

    printf(GRN"Combien de tests voulez-vous effectuer ?\n"RESET);
    scanf("%d", &nb_test);

    result = test_all_fonction(nb_test, 1, true);
    if (result == 0)
        printf(GRN"Tous les tests des réel positif sont bon.\n"RESET);
    else 
        return 1;



    /* test avec des double negatif */
    result = test_all_fonction(nb_test, -1, true);
    if (result == 0)
        printf(GRN"Tous les tests des réel négatif sont bon.\n"RESET);
    else
        return 1;



    /* test avec des entier positif */
    result = test_all_fonction(nb_test, 1, false);
    if (result == 0)
        printf(GRN"Tous les tests des entiers positifs sont bon.\n"RESET);
    else 
        return 1;



    /* test avec des entiers négatifs */
    result = test_all_fonction(nb_test, -1, false);
    if (result == 0)
        printf(GRN"Tous les tests des entiers négatifs sont bon.\n"RESET);
    else
        return 1;

    //si tout c'est bien passé
    return 0;
}
