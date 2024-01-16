#include <stdio.h>
#include "geom2d.h"
#include "fichier_PointVect.h"


int main(int argc, char* argv[]){
    int i, result;
    char nom_fonction[32];
    bool err = false;
    coordonnee x1, y1, x2, y2, x_res, y_res;
    double lambda, res;
    
    for (i = 1 ; i < argc ; i++){
        printf("-------------------------------------------------------------------------------------------------------\n");
        result = lire_fichier_PointVect(argv[i], nom_fonction, &x1, &y1, &x2, &y2, &lambda, &x_res, &y_res, &res);
        
	/*si le fichier est bien dans le bon format :
		- on affiche les valeurs du fichier
		- et on lance les tests sur les fonctions du fichier 
	*/
        if (result == 0){
		afficher_fichier_PointVect(argv[i], nom_fonction, &x1, &y1, &x2, &y2, &lambda, &x_res, &y_res, &res);

		result = test_fonction_PointVect(nom_fonction, x1, y1, x2, y2, lambda, x_res, y_res, res);

                if (result == 1)
                    err = true;
        }
        else {
            err = true;
        }
        
    }

    printf("-------------------------------------------------------------------------------------------------------\n");
    if (err == true)
        printf("Il y a eut au moins une erreur pendant soit la lecteure d'un fichier ou alors dansles resultat\n");
    else 
        printf("Le ou les fichiers utilisé pour ces tests sont tous bon\n");

    printf("\n\n\n");
    printf("-------------------------------------------------------------------------------------------------------\n");


    return 0;
}




