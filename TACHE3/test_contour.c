#include <stdio.h>
#include "struct_liste.h"
#include "geom2d.h"
#include "image.h"
#include "contour.h"



int main(int argc, char* argv[])
{
    // il faut au moin un fichier .pbm pour cet executable
    if (argc < 2)
    {
        fprintf(stderr, "Uilisation : ./test_contour <groupe de fichier image>\n");
        exit(1);
    }
    // Declaration des variable 
    Image I;
    Contour C;
    int i;

    for (i = 1; i < argc ; i++)
    {

        I = lire_fichier_image(argv[i]);
        C = calcul_contour(I);
        ecrire_contour(C);
    }
    
}

