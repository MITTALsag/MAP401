#include <stdio.h>
#include <string.h>
#include "image.h"


int main (int argc, char* argv[]){

    if (argc != 2){
        fprintf(stderr, "Utlisiation ./test_image_seul <nom_fichier>\n");
        exit(1);
    }

    Image I;
    Image neg_I;
    char nom_image[256];
    int len;

    strcpy(nom_image, argv[1]);
    len = strlen(nom_image);

    I = lire_fichier_image(nom_image);
    
    // a décommenter au besoins
    ecrire_image(I);

    neg_I = negatif_image(I);

    // a décommenter au besoins
    ecrire_image(neg_I);

    nom_image[len - 4] = '\0';

    strcat(nom_image, "_negatif.pbm");

    ecrire_fichier_image(neg_I, nom_image);

    return 0;

}