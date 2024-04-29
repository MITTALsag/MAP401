#include <stdio.h>
#include <string.h>
#include <image.h>


int main (int argc, char* argv[]){

    if (argc != 2){
        printf("Utlisiation ./test_image <nom_fichier>\n");
        return 1;
    }

    Image I;
    Image neg_I;
    char nom_image[256] = {'\0'};
    int len;

    strcpy(nom_image, argv[1]);
    len = strlen(nom_image);

    I = lire_fichier_image(nom_image);

    // a décommenter au besoins
    //ecrire_image(I);

    neg_I = negatif_image(I);

    // a décommenter au besoins
    //ecrire_image(neg_I);

    // pour transformer <nom_fichier>.pbm en <nom_fichier>_negatif.pbm
    nom_image[len - 4] = '\0';
    strcat(nom_image, "_negatif.pbm");

    ecrire_fichier_image(neg_I, nom_image);

    printf(GRN"Création du négatif de l'image %s dasn le dossier %s\n"RESET, argv[1], nom_image);
    supprimer_image(&I);
    supprimer_image(&neg_I);
    return 0;

}
