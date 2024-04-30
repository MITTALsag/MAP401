#ifndef _EPS_H_
#define _EPS_H_

#include <struct_liste.h>
#include <types_macros.h>

/* - Ouvre le fichier "nom_fichier" en ecriture
** - cree l'image sous format eps avec le contour passé en paramètre
** (l'image est cree avec des segements)
** - l'image est cree avec fill ou stroke en fonction du mode passé en argument
*/
void cree_image_eps(const Contour C, const UINT Largeur_Image, const UINT Hauteur_Image, const char* nom_fichier, const char mode);


void cree_image_eps_multiple(const char* fichier_contour, const UINT Largeur_Image, const UINT Hauteur_Image, const char* nom_fichier, const char mode);



void cree_image_eps_bezier2(const char* fichier_contour, const UINT Largeur_Image, const UINT Hauteur_Image, const char* nom_fichier, const char mode);



void cree_image_eps_bezier3(const char* fichier_contour, const UINT Largeur_Image, const UINT Hauteur_Image, const char* nom_fichier, const char mode);

#endif /* _EPS_H_ */
