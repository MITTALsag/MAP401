On se trouve dans le dossier de la tache 6 de L'UE MAP401

ORGANISATION :

Ce dossier est formé par plusieurs dossier :
    - TEST : Ce dossier contient tout les fichier .c destiner a être des
      executable et leurs executable sont aussi dans ce dossier apres
      compilation
    - MODULE : Ce dossier contient des sous dossier. Il y a un sous dossier par
      module et chaque sous dossier contient le .c et le .h associé au module
      et aussi le .o associé après la compilation.
    - LIB : Ce dossier contient/contiendra (après compilation) la/les
      librairies statiques dont ont besoins les fichier tests pour compiler
    - INCLUDES : Ce dossier contiens tous les fichier d'interfaces necessaire à
      la compilation des TEST (ces fichier sont des liens symbolique vers les
      fichier .h contenu dans les sous dossier de MODULE).
    - BIN : Ce dossier contient simplement tous les .o cree lors de la
      compilation
    - IMAGE_TEST : Ce sont juste des dossier de test local
    - IMAGE_TEST_CONTOUR_COMPLET : Les contours des images de IMAGE_TEST avant
      simplifaction
    - IMAGE_TEST_CONTOUR_SIMPLE : Les contours des images de IMAGE_TEST après
      simplifaction par courbe de bezier de degres 2
    - IMAGE_TEST_CONTOUR_SIMPLE_3 : Les contours des images de IMAGE_TEST après
      simplifaction par courbe de bezier de degres 3
    - IMAGE_TEST_FILL_EPS_COMPLET : les même images que IMAGE_TEST mais sous
      format .eps et en mode fill avant simplifacation par segments
    - IMAGE_TEST_FILL_EPS_SIMPLE : les même images que IMAGE_TEST mais sous
      format .eps et en mode fill apres simplifacation par courbe de bezier de
      dregre 2
    - IMAGE_TEST_FILL_EPS_SIMPLE_3 : les même images que IMAGE_TEST mais sous
      format .eps et en mode fill apres simplifacation par courbe de bezier de
      dregre 3

COMPLATION :

Lors de la première compilation le make va cree une librairie statique
"libimage.a", "libgeom2d.a" "libstruct_liste", libcontour",
"libeps","libsimplifaction" et "libbezier"
et va la placer dans le dossier LIB.
Il va ensuite cree les executables test_bezier test_bezier3, test_simplifiation_bezier et test_simplifaction_bezier3

EXECUTABLE :

- test_bezier et test_bezier3 : Ces deux fichier fonct des test unitaire sur
    les focntions du module bezier pour les courbes de bezier de degres 2 et 3
    respectivement

- test_simplifactaion_bezier(/3) :
    Ces fichier prend en argument une image .pbm et un float qui sera "d"
    Il va ensuite calculer sont contour comme dans la tache 6 et le mettre dans
    le fichier du meme nom suffixé par .contour.txt
    Puis il va simplifier ce contour grace au courbe de bezier de degres 2(/3)
    fichier (cette fois suffixé par .contour_bezier_simple.txt)
    Et enfin il va calculer a partir du contour et du contour simplifier les images eps associés

.SH :
- simplifactaion_bezier2.sh et simplification_bezier3.sh :
    Ce fichier prend en argument un dossier contenant au moins un fichier .pbm
    Il calcul ensuite ses contours les simplifié et ensuite cree une image .eps
    de l'image (une a partir du contour originale et une a partir du contour simplifié
    Les différents fichier sont ensuite placé dans les dossier correspondant 
    - IMAGES_TEST_CONTOUR_COMPLET  : les contours complet des images
    - IMAGES_TEST_CONTOUR_SIMPLE   : les contour simplifié des images
    - IMAGES_TEST_FILL_EPS_COMPLET : les images eps cree a partir des contour complet
    - IMAGES_TEST_FILL_EPS_SIMPLE  : les images eps cree a partir des contour simple


