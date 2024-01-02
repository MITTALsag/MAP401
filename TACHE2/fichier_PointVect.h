#ifndef _FICHIER_POINTVECT_H_
#define _FICHIER_POINTVECT_H_

//REF 17

#include "geom2d.h"
#include "types_macros.h"




/* lit un fichier test de fonctoin Point_Vecteur
 - fait une ERREUR_NON_FATALE si le format n'est pas bon
 - puis met dans les paramètre coordonnée* les bonnes valeurs 
 - retourne 0 si tout s'est bien passé et 1 sinon */
 /* Format attentu : 
    - nom de la fonction a tester (exqctement le même nom)
    - premier argument de la fonction a tester (si c'est un point ou un vecteur premiere coordonnée puis espace puis deuxième coordonnée) 
    - deuxieme paramètre de la fonction 
            (sauf pour la fonction set_point qui a ces deux coordonnées sur la même ligne)
    - resulat attendu 
    - éventullement des commentaires */
int lire_fichier_PointVect(char* nom_fich, char* nom_fonction, coordonnee* x1, coordonnee* y1, coordonnee* x2, coordonnee* y2, double* lambda, coordonnee* x_res, coordonnee* y_res, double* res);



/* affiche :
Chemin relatif du fichier : <nom du fichier>
Nom fonction : <nom de la fonction>
Argument 1 : <argument 1> (si c'est un point ou un vecteur --> affiche (coordonnée x, coordonnée y))
Argument 2 : <argument 2>   (si il y en as un)
Resultat : <resultat> 
*/
void afficher_fichier_PointVect(char* nom_fich, char* nom_fonction, coordonnee* x1, coordonnee* y1, coordonnee* x2, coordonnee* y2, double* lambda, coordonnee* x_res, coordonnee* y_res, double* res);



/* test la fonction attendu et compare avec le resultat attendu (x_res, y_res ou res) 
 Renvoie 0 si le resultat attendue est le bon et 1 sinon */
int test_fonction_PointVect(char* nom_fonction, coordonnee x1, coordonnee y1, coordonnee x2, coordonnee y2, double lambda, coordonnee x_res, coordonnee y_res, double res);





#endif