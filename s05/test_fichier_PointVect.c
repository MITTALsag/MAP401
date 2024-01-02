#include <stdio.h>
#include "geom2d.h"
#include "fichier_PointVect.h"

//REF 18

int main(int argc, char* argv[]){
    int i, result;
    char nom_fonction[32];
    coordonnee x1, y1, x2, y2, x_res, y_res;
    double lambda, res;
    
    for (i = 1 ; i < argc ; i++){
        printf("-------------------------------------------------------------------------------------------------------\n");
        result = lire_fichier_PointVect(argv[i], nom_fonction, &x1, &y1, &x2, &y2, &lambda, &x_res, &y_res, &res);
        
        if (result == 0){
            afficher_fichier_PointVect(argv[i], nom_fonction, &x1, &y1, &x2, &y2, &lambda, &x_res, &y_res, &res);

            result = test_fonction_PointVect(nom_fonction, x1, y1, x2, y2, lambda, x_res, y_res, res);
        }
    }
    return 0;
}




