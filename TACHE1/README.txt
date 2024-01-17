On se trouve dans le dossier de la tache 1 de L'UE MAP401

ORGANISATION :

Ce dossier est formé par plusieurs dossier :
    - TEST : Ce dossier contient tout les fichier .c destiner a être des
      executable et leurs executable sont aussi dans ce dossier apres
      compilation
    - SRC : Ce dossier contient tous les .c dont ont besoin les fichier tests
      pour complier
    - LIOBRARY : Ce dossier contient/contiendra (après compilation) la
      librairies statiques dont ont besoins les fichier tests pour compiler
    - includes : Ce dossier contiens tous les fichier d'interfaces necessaire à
      la compilation des SRC et des TEST
    - binarires : Ce dossier contient simplement tous les .o cree lors de la
      compilation
    - IMAGE_TEST(_NEG) : Ce sont juste des dossier de test local

COMPLATION :

Lors de la première compilation le make va cree une librairie statique
"libimage.a" et va la placer dans le dossier LIBRARY.
Il va ensuite cree les executables test_image et test_lecture_fichier.

EXECUTABLE :

- test_image : Cet executable prend en ligne de commande une image .pbm, il va
  ensuite la lire, et cree son negatif qui va appeler du même nom que
  le fichier suffixé par "_negatif" et le placer dans le même dossier que le
  fichier d'origine.

- test_lecture_fichier : Cet executable aussi prend en argument unn .pbm, mais
  il vas simplemnt le lire et afficher l'image correspondante sur le
  terminal.

.SH :
il y a aussi un fichier test_image.sh a la racine du dossier. Ce fichier prend
comme argument un dossier contenant des .pbm. Il appelle l'exectable test_image
sur toutes les images du dossier passé en paramètre (donc crée un négatif par
images contenues dans le dossier) et puis les place dans un dossier (qu'il créé
si besoin) appllé comme le dossier passé en argument suffixé par _NEG.
Ex : Si on se trouve dans TACHE1 et que l'on fais la commande suivante :
./test_image.sh ../IMAGE_TESTS
Le programme vas cree tous les negatif de toutes les images dans ce dossier et
les placé dans ../IMAGE_TESTS_NEG.
