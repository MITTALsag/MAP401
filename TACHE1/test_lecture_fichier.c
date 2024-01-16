#include <stdio.h>
#include <image.h>


int main (int argc, char* argv[]){

    Image I;
    if (argc != 2){
        printf ("USAGE : ./test_lecture_fichier <fichier.pbm>\n");
        return 1;
    }

    I = lire_fichier_image(argv[1]);

    ecrire_image(I);

    supprimer_image(&I);

    return 0;
}
