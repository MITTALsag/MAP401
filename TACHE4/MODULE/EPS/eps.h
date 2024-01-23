#ifndef _EPS_H_
#define _EPS_H_

#include <struct_liste.h>
#include <types_macros.h>

/* - Ouvre le fichier "nom_fichier" en ecriture
** - cree l'image sous format eps avec le contour passé en paramètre
** (l'image est cree avec des segements)
** - l'image est cree avec fill ou stroke en fonction du mode passé en argument
*/
void cree_image_eps(Contour C, UINT Largeur_Image, UINT Hauteur_Image, char* nom_fichier, char mode);


#endif /* _EPS_H_ */
