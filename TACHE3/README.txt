On se trouve dans le dossier de la tache 3 de L'UE MAP401

ORGANISATION :

Ce dossier est formé par plusieurs dossier :
    - TEST : Ce dossier contient tout les fichier .c destiner a être des
      executable et leurs executable sont aussi dans ce dossier apres
      compilation
    - SRC : Ce dossier contient tous les .c dont ont besoin les fichier tests
      pour complier
    - LIB : Ce dossier contient/contiendra (après compilation) la
      librairies statiques dont ont besoins les fichier tests pour compiler
    - INCLUDES : Ce dossier contiens tous les fichier d'interfaces necessaire à
      la compilation des SRC et des TEST
    - BIN : Ce dossier contient simplement tous les .o cree lors de la
      compilation
    - IMAGE_TEST(_NEG) : Ce sont juste des dossier de test local
    - IMAGE_TEST(_NEG)_CONTOUR : Ce sont les contour associé a IMAGE_TEST(_NEG)

COMPLATION :

Lors de la première compilation le make va cree une librairie statique
"libimage.a", "libgeom2d.a", "libstruct_liste.a" et libcontour.a"
et va la placer dans le dossier LIB.
Il va ensuite cree les executables test_contour(_neg) et
test_contour_a_la_volee et test_struct_liste.

EXECUTABLE :

- test_contour(_neg) : Cet executable prend en ligne de commande une image .pbm, il va
  ensuite la lire, et cree un fichier du même nom mais suffixé par .contour
  contenant le contour de l'image passé en paramètre au format du sujet
  (test_contour_neg fais la même chose mais sur les images négative)

- test_contour_a_la_volee : Fais la même chose que test_contour sauf que ce
  fichier affiche dans le terminal le contour au lieu de la mettre dans un
  fichier

- test_struct_liste : fais des test unitaires sur le module associés

.SH :
il y a aussi un fichier test_contour(_neg-.sh a la racine du dossier. Ce fichier prend
comme argument un dossier contenant des .pbm. Il appelle l'exectable
test_contour(_neg) sur toutes les images du dossier passé en paramètre 
(donc crée un contour par images contenues dans le dossier) et puis les place dans un dossier 
(qu'il créé si besoin) appllé comme le dossier passé en argument suffixé par
_CONTOUR.
Ex : Si on se trouve dans TACHE3 et que l'on fais la commande suivante :
./test_contour.sh ../IMAGE_TESTS
Le programme vas cree tous les contour de toutes les images dans ce dossier et
les placé dans ../IMAGE_TESTS_CONTOUR.

Il y a aussi un fichier test_contour_resultat.
Ce fichier calcul le contour de toutes les images de ../IMAGES_TESTS et de ../IMAGES_TESTS_NEG
(cree les négatif si besoin)
et utilise la commande diff pour voir si les contour sont différents
(si ils sont différents --> il y a une erreur car une image et son negatif ont le même contour)
ATTENTION !!! Il faus être dans le dossier TACHE3 pour executer ce script.
