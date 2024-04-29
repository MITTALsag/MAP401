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
      simplifaction par segments.
    - IMAGE_TEST_CONTOUR_SIMPLE : Les contours des images de IMAGE_TEST après
      simplifaction par segments.
    - IMAGE_TEST_FILL_EPS_COMPLET : les même images que IMAGE_TEST mais sous
      format .eps et en mode fill avant simplifacation par segments
    - IMAGE_TEST_FILL_EPS_SIMPLE : les même images que IMAGE_TEST mais sous
      format .eps et en mode fill apres simplifacation par segments

COMPLATION :

Lors de la première compilation le make va cree une librairie statique
"libimage.a", "libgeom2d.a" "libstruct_liste", libcontour", "libeps" et "libsimplifaction"
et va la placer dans le dossier LIB.
Il va ensuite cree les executables test_simplifaction_segment et test_distance

EXECUTABLE :

- test_distance : Ce fichier test NE PREND PAS d'argument en ligne de commande mais demande
    a l'utilisateur de saisir 3 points (P puis A et en fin B) et calcul et affiche la distance
    entre P et le segement [AB]

- test_simplifactaion_segment : Ce fichier prend en argument une image .pbm et un float qui sera "d"
    Il va ensuite calculer sont contour comme dans la tache 6 et le mettre dans
    le fichier du meme nom suffixé par .contour.txt
    Puis il va simplifier ce contour et mettre le nouveau contour dans un autre
    fichier (cette fois suffixé par .contour_simple.txt)
    Et enfin il va calculer a partir du contour et du contour simplifier lews images eps associés

.SH :
- simplifactaion_segemnt.sh :
    Ce fichier prend en argument un dossier contenant au moins un fichier .pbm
    Il calcul ensuite ses contours les simplifié et ensuite cree une image .eps
    de l'image (une a partir du contour originale et une a partir du contour simplifié
    Les différents fichier sont ensuite placé dans les dossier correspondant 
    - IMAGES_TEST_CONTOUR_COMPLET  : les contours complet des images
    - IMAGES_TEST_CONTOUR_SIMPLE   : les contour simplifié des images
    - IMAGES_TEST_FILL_EPS_COMPLET : les images eps cree a partir des contour complet
    - IMAGES_TEST_FILL_EPS_SIMPLE  : les images eps cree a partir des contour simple
