#ifndef _SIMPLIFICATION_H_
#define _SIMPLIFICATION_H_

/*
- simplifier la partie du contour CONT compris entre les indices j1 et j2 avec la distance-seuil d
- la fonction renvoie la s´equence de segments L
- procedure recursive de type ”diviser pour r´egner” (”divide and conquer”)
*/
Contour simplification_douglas_peucker(Tableau_Point CONT, UINT j1, UINT j2, UINT d);



/* Cette procédure prend en argument :
    - le nom d'un fichier contour n1
    - le nom d'un fichier de sortie n2
    - un reel d
Puis calcul grace a l'algorithme de Douglas Peucker la simplification de n1 et met le resultat dans n2.
Cette fonction fais les calcul a la volé : c'est a dire pour chacun des contour de n1 elle va calculer sa simplification puis le mettre dans n2 avant de passer au contour suivant.
*/
void simplification_segment(char* nom_fichier_entree, char* nom_fichier_sortie, float d);

#endif
