On se trouve dans le dossier de la tache 2 de L'UE MAP401

ORGANISATION :

Ce dossier est formé par plusieurs dossier :
    - TEST : Ce dossier contient tout les fichier .c destiner a être des
      executable et leurs executable sont aussi dans ce dossier apres
      compilation
    - SRC : Ce dossier contient tous les .c dont ont besoin les fichier tests
      pour complier
    - LIB : Ce dossier contient/contiendra (après compilation) la/les
      librairies statiques dont ont besoins les fichier tests pour compiler
    - INCLUDES : Ce dossier contiens tous les fichier d'interfaces necessaire à
      la compilation des SRC et des TEST
    - BIN : Ce dossier contient simplement tous les .o cree lors de la
      compilation
    - IMAGE_TEST(_NEG) : Ce sont juste des dossier de test local

COMPLATION :

Lors de la première compilation le make va cree une librairie statique
"libimage.a", "libgeom2d.a" et va la placer dans le dossier LIB.
Il va ensuite cree les executables test_geom2D et test_alea_geom2d.

EXECUTABLE :

- test_geom2d : Fais des tests unitaires sur les fonction du module geom2d

- test_alea_geom2d : Fais es tests unitaires mais cette fois de facon aléatoire
  sur le même module

