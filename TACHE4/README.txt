On se trouve dans le dossier de la tache 4 de L'UE MAP401

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
    - IMAGE_TEST(_FILL(STROKE)_EPS) : Ce sont juste des dossier de test local

COMPLATION :

Lors de la première compilation le make va cree une librairie statique
"libimage.a", "libgeom2d.a" "libstruct_liste", libcontour" et "libeps"
et va la placer dans le dossier LIB.
Il va ensuite cree les executables test_eps_stroke et test_eps_fill.

EXECUTABLE :

- test_eps_stroke : prend en ligne de commande un fichier .pbm et ecrit dans un
  fichier le contour de l'image associé en mode "stroke"

- test_eps_fill : fais la même chose mais le fais en mode "fill"

.SH :
il y a aussi un fichier test_eps_fill(_stroke).sh a la racine du dossier. Ce fichier prend
comme argument un dossier contenant des .pbm. Il appelle l'executable
test_eps_fill(_stroke) sur toutes les images du dossier passé en paramètre 
(donc crée une image .eps  par images contenues dans le dossier) et puis les place dans un dossier 
(qu'il créé si besoin) appllé comme le dossier passé en argument suffixé par
_FILL(_STROKE)_EPS.
Ex : Si on se trouve dans TACHE4 et que l'on fais la commande suivante :
./test_eps_fill.sh ../IMAGE_TESTS
Le programme vas cree toutes les images .eps de toutes les images .pbm dans ce dossier et
les placé dans ../IMAGE_TESTS_FILL_EPS.

ATTENTION !!! Il faus être dans le dossier TACHE4 pour executer ce script.
