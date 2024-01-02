#include <stdio.h>
#include <string.h>
#include "image.h"

/* ce fichier peut etre utiliser uniquement si les fichier .pbm sont dans le dossier ../IMAGES_TESTS/ */
/* Sinon utliser test_image_seul qui prend que un seul fichier .pbm */

void extract(int deb, char* chaine, char* sous_chaine){

    int i=0, j=0;
    //récupérer la longueur de la chaîne
    int len = strlen(chaine);
    
    if( deb > len){
        printf("L'index 'deb' est invalide\n");
        exit(1);
    } 
    for( i = deb, j = 0; chaine[i] != '.'; i++, j++){
        sous_chaine[j] = chaine[i];
    }  
    sous_chaine[j] = '\0';
}

int main(int argc, char* argv[])
{
    if (argc < 2){
        fprintf(stderr, "UTILISATION ./test_image <../IMAGES_TESTS/<nom_fichier OU groupe de fichier>\n");
        exit(1);
    }

    
    //variables utiles
    Image I;
    Image neg_I;
    int i;
    char nom_image[256];
    char sous_chaine[256];

    //boucle pour itérer sur chaque images de la ligne de commande
    for(i = 1 ; i < argc ; i++){
    
        I = lire_fichier_image(argv[i]);
        
        // a décommenter au besoins
        //ecrire_image(I);

        neg_I = negatif_image(I);

        /* Modifier nom_image = ../IMAGES_TESTS/<nom_fichier>.pbm -------> ../IMAGES_TESTS_NEG/<nom_fichier>_negatif.pbm */
        /*------------------------------------------------------------------------------------------------------------------------------*/

        strcpy(nom_image, argv[i]);
        
        extract(16, nom_image, sous_chaine);

        nom_image[15] = '\0';
        strcat(nom_image, "_NEG/");

        strcat(nom_image, sous_chaine);
        
        strcat(nom_image, "_negatif.pbm");
        
        /*------------------------------------------------------------------------------------------------------------------------------*/

        // const char* commande = "mv ../IMAGES_TESTS/*negatif.pbm ../IMMAGES_TESTS_NEG/.";
        // system(commande);

        ecrire_fichier_image(neg_I, nom_image);
        
        supprimer_image(&I);
        supprimer_image(&neg_I);


    }

    return 1;
}