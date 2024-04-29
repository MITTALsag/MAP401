#ifndef _BEZIER_H_
#define _BEZIER_H_

#include <geom2d.h>
#include <contour.h>



/*******************************/
/* TYPE DE BEZIER  DE DEGRES 2 */
/*******************************/

typedef struct Bezier2_
{
    Point C0;
    Point C1;
    Point C2;
}Bezier2;


/*-------------------------------------------------------------------------------------*/


/*******************************/
/* TYPE DE BEZIER  DE DEGRES 3 */
/*******************************/

typedef struct Bezier3_
{
    Point C0;
    Point C1;
    Point C2;
    Point C3;
}Bezier3;


/*--------------------------------------------------------------------------------------------------------*/

/****************************/
/* FONCTION BEZIER DEGRES 2 */
/****************************/



/*initialisation de courbe de bezier de degres 2*/
Bezier2 init_bezier2(Point C0, Point C1, Point C2);


/* Cette fonction calcul C(t) pour t entre [-2 et 1] et pour une courbe de
** bezier de degres 2
*/
Point calcul_bezier2(Bezier2 C, double t);



/* CETTE fonction approxime le contour polygonal CONT par une courbe de bezier
** de degres 2
*/
Bezier2 approx_bezier2(Tableau_Point CONT, UINT j1, UINT j2);


/* Cette fonction calcul et renvoie la distance entre le point P et la courbe
** de bezier de degres 2 B 
*/
double distance_point_bezier2(Point P, Bezier2 B, double t);


/*--------------------------------------------------------------------------------------------------------*/

/****************************/
/* FONCTION BEZIER DEGRES 3 */
/****************************/


/*initialisation de courbe de bezier de degres 3*/
Bezier3 init_bezier3(Point C0, Point C1, Point C2, Point C3);


/* Cette fonction calcul C(t) pour t entre [0 et 1] et pour une courbe de
** bezier de degres 3
*/
Point calcul_bezier3(Bezier3 C, double t);


/*Cette fonction convertis une courbe de bezier de degres 2 en courbe de bezier
** de degres 3 par elevation au degres
*/
Bezier3 elevation_degre(Bezier2 B);



/* CETTE fonction approxime le contour polygonal CONT par une courbe de bezier
** de degres 3
*/
Bezier3 approx_bezier3(Tableau_Point CONT, UINT j1, UINT j2);


/* Cette fonction calcul et renvoie la distance entre le point P et la courbe
** de bezier de degres 3 B 
*/
double distance_point_bezier3(Point P, Bezier3 B, double t);


#endif
