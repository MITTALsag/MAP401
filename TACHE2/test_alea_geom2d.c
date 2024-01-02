#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> 
#include "geom2d.h"




/*A MODIFIER EN FAISANT EN SORTE QUE LA VALEUR DE RETOUR NE SOIT PAS TROP GRANDE */
/* renvoie un Double avec 15 chiffre apres la virgule */
double randomDouble()
{
    return (double)(rand()) / (double)(rand());
}

/* renvoie un double sous forme d'entier par ex : 2. = 2 */
double randomInt()
{
    return (double)(rand() % 100);
}

/* fonction qui verifie chaque fonction une fois grace a 4 coordonnées */
int test_all_fonction(coordonnee x1,coordonnee x2, coordonnee y1, coordonnee y2, double lambda, int nb_test){
    double result;
    Point A, B, C; 
    Vecteur U, W, V;

    for (int i = 0; i < nb_test; i++) {

        /******************************/
        /* tests des fonctions points */
        /******************************/
    
        A = set_point (x1, y1);
        B = set_point (x2, y2);

        if (A.x != x1 || A.y != y1){
            printf("ERREUR DANS set_point avec le point A = (%f, %f)\n", x1, y1);
            return 1;
        }

        if (B.x != x2 || B.y != y2){
            printf("ERREUR DANS set_point avec le point B = (%f, %f)\n", x2, y2);
            return 1;
        }

        
        C = add_point(A, B);

        if (C.x != x1 + x2 || C.y != y1 + y2){
            printf("ERREUR DANS add_point avec les points A = (%f, %f) et B = (%f, %f)\n", x1, y1, x2, y2);
            return 1;
        }

        C = mult_scalaire_point(A, lambda);

        if (C.x != lambda * x1 || C.y != lambda * y1){
            printf("ERREUR DANS mult_scalaire_point avec le points A = (%f, %f)\n", x1, y1);
            return 1;
        }

        result = distance(A, B);

        if (result != sqrt(pow(x1 - x2, 2.) + pow(y1 - y2, 2.))){    
            printf("ERREUR DANS norme avec les points A = (%f, %f) et B = (%f, %f)\n", x1, y1, x2, y2);
            return 1;
        }

        /*******************************/
        /* tests des fonctions vecteur */
        /*******************************/

        //creation d'un vecteur bipoint
        U = vect_bipoint(A, B);
        if (U.x != x2 - x1 || U.y != y2 - y1){
            printf("ERREUR DANS vect_bipoint avec les points A = (%f, %f) et B = (%f, %f)\n", x1, y1, x2, y2);
            return 1;
        }

        x1 = U.x; y1 = U.y;
        
        //creation d'un vecteur uni point
        V.x = A.x;
        V.y = A.y;

        x2 = V.x; y2 = V.y;

        W = add_vect(U, V);
        if (W.x != x1 + x2 || W.y != y1 + y2){
            printf("ERREUR DANS add_vect avec les vecteurs U = (%f, %f) et V = (%f, %f)\n", x1, y1, x2, y2);
            return 1;
        }

        W = mult_scalaire_vect(U, lambda);
        if (W.x != lambda * x1 || W.y != lambda * y1){
            printf("ERREUR DANS mult_scalaire_vect avec le vecteur U = (%f, %f)\n", x1, y1);
            return 1;
        }

        result = prod_scal(U, V);
        if (result != x1*x2 + y1*y2){
            printf("ERREUR DANS prod_scal avec les vecteurs U = (%f, %f) et V = (%f, %f)\n", x1, y1, x2, y2);
            return 1;
        }

        result = norme(U);
        if (result != sqrt(x1*x1 + y1*y1)){
            printf("ERREUR DANS norme avec les vecteurs U = (%f, %f)\n", x1, y1);
            return 1;
        }
        
    }

    return 0;
}


int main(void){
    
    srand(time(NULL));
    coordonnee x1, x2, y1, y2;
    double lambda, result;
    int nb_test;

    printf("Combien de tests voulez-vous effectuer ?\n");
    scanf("%d", &nb_test);

    /* test avec des double positif */
    x1 = randomDouble();
    x2 = randomDouble();
    y1 = randomDouble();
    y2 = randomDouble();
    lambda = randomDouble();

    result = test_all_fonction(x1, y1, x2, y2, lambda, nb_test);
    if (result == 0)
        printf("Tous les tests des réel positif sont bon.\n");
    else 
        return 1;



    /* test avec des double negatif */
    x1 = -1 * randomDouble();
    x2 = -1 * randomDouble();
    y1 = -1 * randomDouble();
    y2 = -1 * randomDouble();

    result = test_all_fonction(x1, y1, x2, y2, lambda, nb_test);
    if (result == 0)
        printf("Tous les tests des réel négatif sont bon.\n");
    else 
        return 1;

   

    /* test avec des entier positif */
    x1 = randomInt();
    x2 = randomInt();
    y1 = randomInt();
    y2 = randomInt();

    result = test_all_fonction(x1, y1, x2, y2, lambda, nb_test);
    if (result == 0)
        printf("Tous les tests des entiers positifs sont bon.\n");
    else 
        return 1;



    /* test avec des entiers négatifs */
    x1 = -1 * randomInt();
    x2 = -1 * randomInt();
    y2 = -1 * randomInt();
    y1 = -1 * randomInt();

    result = test_all_fonction(x1, y1, x2, y2, lambda, nb_test);
    if (result == 0)
        printf("Tous les tests des entiers négatifs sont bon.\n");
    else 
        return 1;  



    /* test manuel (celui de l'énoncé) */
    Point A, B, C; Vecteur U;
    A = set_point(1.0, -3.0);
    B = set_point(4.0, 1.0);
    C = add_point (A, B); /* −−> C = ( 5 .0 , −2 .0) */
    if (C.x != 5. || C.y != -2.){
        printf("ERREUR DANS add_point avec les points A = (1., -3.) et B = (4., 1.)\n");
        return 1;
    }

    U = vect_bipoint(C, A); /* −−> U = ( −4 .0 , −1 .0) */

    if (U.x != -4. || U.y != -1.){
        printf("ERREUR DANS vect_bipoint avec les points C = (5., -2.) et A = (1., -3.)\n");
        return 1;
    }

    printf("Tous les tests manuel sont bon.\n");

    //si tout c'est bien passé
    return 0;
}
