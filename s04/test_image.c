#include <stdio.h>
#include "image.h"

int main(int argc, char* argv[])
{
    Image I;
    Image neg_I;
    
    I = lire_fichier_image(argv[1]);

    ecrire_image(I);
    neg_I = negatif_image(I);

    ecrire_image(neg_I);

    supprimer_image(&I);
    supprimer_image(&neg_I);


    return 1;
}