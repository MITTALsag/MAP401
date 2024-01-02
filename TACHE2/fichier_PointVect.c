#include <stdio.h>
#include <string.h>
#include "fichier_PointVect.h"

//REF 17

/***************************************/
/* Vérification du contenue du fichier */
/***************************************/

/* fonction qui verifie si nom est égale a une fonction du module geom2d 
- retourne 0 si c'est le cas et 1 sinon */
int verif_nom_fonction(char* nom){
    if (strcmp(nom, "set_point") && strcmp(nom, "vect_bipoint") && \
    strcmp(nom, "add_point") && strcmp(nom, "add_vect") && \
    strcmp(nom, "mult_scalaire_point") && strcmp(nom, "mult_scalaire_vect") \
    && strcmp(nom, "prod_scal") && strcmp(nom, "norme") && strcmp(nom, "distance"))
        return 1;
    
    return 0;
}


/* Les fonctions lire... lises soir un double soit un point (ou veceteur) au bon format :
    - lire_double ---> %lf\n
    - lire_coor   --->  %lf' '%lf\n
*/

int lire_double(FILE* fich, double* val, char* ligne, char* nom_fich){
    char sep;
    int result;
    result = fscanf(fich, "%lf%c", val, &sep);
    if (result != 2 || sep != '\n'){
        fprintf(stderr, "lire_double : erreur lecture du %s dans le fichier %s\n", ligne, nom_fich);
        return 1;
    }
    return 0;
}

int lire_coor(FILE* fich, coordonnee* x, coordonnee* y, char* ligne, char* nom_fich){
    char sep1, sep2;
    int result;
    result = fscanf(fich, "%lf%c%lf%c", x, &sep1, y, &sep2);
    if (result != 4 || sep1 != ' ' || sep2 != '\n'){
        fprintf(stderr, "lire_coor : erreur lecture du %s dans le fichier %s\n", ligne, nom_fich);
        return 1;
    }
    return 0;
}



/**************************************************************************************************************************************/

int lire_fichier_PointVect(char* nom_fich, char* nom_fonction, coordonnee* x1, coordonnee* y1, coordonnee* x2, coordonnee* y2, double* lambda, coordonnee* x_res, coordonnee* y_res, double* res){
    int res_lire;
    FILE* fich = fopen(nom_fich, "r");

    if (!fich){
        ERREUR_NON_FATALE("lire_fichier_PointVect : ouverture du fichier impossible\n");
        return 1;
    }
    
    //verification si le nom de la fonction est valide 
    fscanf(fich, "%s", nom_fonction);
    if (verif_nom_fonction(nom_fonction) == 1){
        fprintf(stderr, "lire_fichier_PointVect : le nom de la fonction %s dans %s n'existe pas dans le module geom2d\n", nom_fonction, nom_fich);
        fclose(fich);
        return 1;
    }

    /* lecture des arguments de la fonction (au besoin des paramètre de la fonction) */
    if (!strcmp(nom_fonction, "set_point") || !strcmp(nom_fonction, "norme"))
        /* Ces fonction ont une seul ligne de deux coordonné dans les fichiers tests*/
        res_lire =  lire_coor(fich, x1, y1, "premier argument.", nom_fich);

    else if (!strcmp(nom_fonction, "mult_scalaire_point") || !strcmp(nom_fonction, "mult_scalaire_vect")){
        /* Ces fonction on d'abord un couple de coordonné puis un double */
        res_lire = lire_coor(fich, x1, y1, "premier argument.", nom_fich);
        //Vérification de la justesse du premier argument
        if (res_lire == 0)
		//lecteure du deuxième argument
            res_lire = lire_double(fich, lambda, "deuxième argument.", nom_fich);
    }
    else {
        /* Ces fonction ont deux couple de coordonnées comme arguments */
        res_lire = lire_coor(fich, x1, y1, "premier argument.", nom_fich);
        //Vérification de la justesse du premier argument
        if (res_lire == 0)
            //lecteure du deuxième argument
            res_lire = lire_coor(fich, x2, y2, "deuxième argument.", nom_fich);
    }

    //si res_lire = 1 --> il y a eut un souci dans la lecture du deuxième paramètre
    if (res_lire == 1){
        fclose(fich);
        return 1;
    }

    /* lecture du resultat attendue (en fonction de la fonction utilisé) */
    if (!strcmp(nom_fonction, "prod_scal") || !strcmp(nom_fonction, "norme") || !strcmp(nom_fonction, "distance"))
        res_lire = lire_double(fich, res, "résultat.", nom_fich);
    else 
        res_lire = lire_coor(fich, x_res, y_res, "résulatat.", nom_fich);

    
    fclose(fich);

    //si res_lire = 1 --> il y a eut un souci dans la lecture des resultat
    if (res_lire){
        return 1;
    }

    return 0;
}


void afficher_fichier_PointVect(char* nom_fich, char* nom_fonction, coordonnee* x1, coordonnee* y1, coordonnee* x2, coordonnee* y2, double* lambda, coordonnee* x_res, coordonnee* y_res, double* res){
    /* affichage du nom du fichier, du nom de la fonction et du premier argument (qui est tout le temps de la forme (x,y)) */
    printf("Chemin relatif du fichier : %s\n", nom_fich);
    printf("Nom fonction : %s\n", nom_fonction);
    printf("Argument 1 : (%lf,%lf)\n", *x1, *y1);


    if (strcmp(nom_fonction, "set_point") && strcmp(nom_fonction, "norme")){
        if (!strcmp(nom_fonction, "mult_scalaire_point") || !strcmp(nom_fonction, "mult_scalaire_vect"))
            printf("Argument 2 : %lf\n", *lambda);
        else 
            printf("Argument 2 : (%lf,%lf)\n", *x2, *y2);
    }


    if (!strcmp(nom_fonction, "prod_scal") || !strcmp(nom_fonction, "norme") || !strcmp(nom_fonction, "distance"))  
        printf("Resultat : %lf\n", *res);
    else 
        printf("Resultat : (%lf,%lf)\n", *x_res, *y_res);

}




/* Ces fonction verifie si le resultat attendue est le même que celui obtenue */
int compare_PointVect(Point P, Vecteur V, coordonnee x, coordonnee y, char c){
    if (c == 'P')
        return (P.x == x && P.y == y);
    
    return (V.x == x && V.y == y);
}

int compare_double(double lambda, double res){
    return lambda == res;
}



/* test la fonction attendu et compare avec le resultat attendu (x_res, y_res ou res) 
 Renvoie 0 si le resultat attendue est le même que celui obtenu et 1 sinon */
int test_fonction_PointVect(char* nom_fonction, coordonnee x1, coordonnee y1, coordonnee x2, coordonnee y2, double lambda, coordonnee x_res, coordonnee y_res, double res){
    Point A = {0,0};
    Vecteur V = {0,0};
    double result;

    if (!strcmp(nom_fonction, "set_point")){
        A = set_point(x1, y1);
        if (!compare_PointVect(A, V, x_res, y_res, 'P')){
            ERREUR_NON_FATALE("Le resultat obtenu n'est pas celui espéré !\n");
            return 1;
        }
    }
    else if (!strcmp(nom_fonction, "vect_bipoint")){
        V = vect_bipoint(set_point(x1, y1), set_point(x2, y2));
        if (!compare_PointVect(A, V, x_res, y_res, 'V')){
            ERREUR_NON_FATALE("Le resultat obtenu n'est pas celui espéré !\n");
            return 1;
        }
    }
    else if (!strcmp(nom_fonction, "add_point")){
        A = add_point(set_point(x1, y1), set_point(x2, y2));
        if (!compare_PointVect(A, V, x_res, y_res, 'P')){
            ERREUR_NON_FATALE("Le resultat obtenu n'est pas celui espéré !\n");
            return 1;
        }
    }
    else if (!strcmp(nom_fonction, "add_vect")){
        V = add_vect(vect_bipoint(set_point(0,0), set_point(x1,y1)), vect_bipoint(set_point(0,0), set_point(x2,y2)));
        if (!compare_PointVect(A, V, x_res, y_res, 'V')){
            ERREUR_NON_FATALE("Le resultat obtenu n'est pas celui espéré !\n");
            return 1;
        }
    }    
    else if (!strcmp(nom_fonction, "mult_scalaire_point")){
        A = mult_scalaire_point(set_point(x1, y1), lambda);
        if (!compare_PointVect(A, V, x_res, y_res, 'P')){
            ERREUR_NON_FATALE("Le resultat obtenu n'est pas celui espéré !\n");
            return 1;
        }
    }    
    else if (!strcmp(nom_fonction, "mult_scalaire_vect")){
        V = mult_scalaire_vect(vect_bipoint(set_point(0,0), set_point(x1,y1)), lambda);
        if (!compare_PointVect(A, V, x_res, y_res, 'V')){
            ERREUR_NON_FATALE("Le resultat obtenu n'est pas celui espéré !\n");
            return 1;
        }
    }    
    else if (!strcmp(nom_fonction, "prod_scal")){
        result = prod_scal(vect_bipoint(set_point(0,0), set_point(x1,y1)), vect_bipoint(set_point(0,0), set_point(x2,y2)));
        if (!compare_double(result, res)){
            ERREUR_NON_FATALE("Le resultat obtenu n'est pas celui espéré !\n");
            return 1;
        }
    }    
    else if (!strcmp(nom_fonction, "norme")){
        result = norme(vect_bipoint(set_point(0,0), set_point(x1,y1)));
        if (!compare_double(result, res)){
            ERREUR_NON_FATALE("Le resultat obtenu n'est pas celui espéré !\n");
            return 1;
        }
    }    
    else if (!strcmp(nom_fonction, "distance")){
        result = distance(set_point(x1, y1), set_point(x2, y2));
        if (!compare_double(result, res)){
            ERREUR_NON_FATALE("Le resultat obtenu n'est pas celui espéré !\n");
            return 1;
        }

    }
    printf("Le resultat obtenu est bien celui attendu.\n");
    return 0;
}
