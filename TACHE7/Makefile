#############################################################################
# Fichier Makefile 
# UE MAP401 - DLST - UGA 
#############################################################################
# utilisation des variables internes $@ $< $^ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond à toutes les dépendances
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################
# Ce fichier compile si besoin une bibliothèque statique "image" depuis SRC et
# la met dans LIB. Puis compile les tests dans TEST
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = clang

#Option de compilation
COMPILOPTS = -g -Wall -Wextra -Werror

# chemin d'acces aux librairies (interfaces)
INCDIR = INCLUDES

# Listes de tous les fichiers interfaces
FILEH = $(INCDIR)/$(wildcard *.h)

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# liste des executables
EXECUTABLES = TEST/test_bezier TEST/test_simplification_bezier TEST/test_bezier_3 TEST/test_simplification_bezier_3

# chemin d'acces aux librairies (binaires)
LIBDIR = LIB

# options pour l'édition des liens
LDOPTS = -L. -lm

# Nom pour la creation des différentes lib
GEOM2D = $(LIBDIR)/libgeom2d.a

IMAGE = $(LIBDIR)/libimage.a

STRUCT_LISTE = $(LIBDIR)/libstruct_liste.a

CONTOUR = $(LIBDIR)/libcontour.a

EPS = $(LIBDIR)/libeps.a

SIMPLIFICATION = $(LIBDIR)/libsimplification.a

BEZIER = $(LIBDIR)/libbezier.a
#############################################################################
# definition des regles
#############################################################################

########################################################
# la regle par defaut
all : $(EXECUTABLES)

# Règle pour la création de la lib point et vecteur
lgeom2d : $(GEOM2D)

limage : $(IMAGE)

lstruct : $(STRUCT_LISTE)

lcontour : $(CONTOUR)

leps : $(EPS)

lsimplification : $(SIMPLIFICATION)

#############################################################################
# Création de la lib "geom2d"
#############################################################################

$(GEOM2D) : MODULE/GEOM2D/geom2d.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Création de librairie geom2d"
	@echo "---------------------------------------------"
	$(AR) rsc $@ $^

########################################################

#############################################################################
# Création de la lib "image"
#############################################################################

$(IMAGE) : MODULE/IMAGE/image.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Création de librairie image"
	@echo "---------------------------------------------"
	$(AR) rsc $@ $^

########################################################

#############################################################################
# Création de la lib "struct_liste"
#############################################################################

$(STRUCT_LISTE) : MODULE/STRUCT_LISTE/struct_liste.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Création de librairie struct_liste"
	@echo "---------------------------------------------"
	$(AR) rsc $@ $^

########################################################

#############################################################################
# Création de la lib "contour"
#############################################################################

$(CONTOUR) : MODULE/CONTOUR/contour.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Création de librairie contour"
	@echo "---------------------------------------------"
	$(AR) rsc $@ $^

########################################################

#############################################################################
# Création de la lib "eps"
#############################################################################

$(EPS) : MODULE/EPS/eps.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Création de librairie eps"
	@echo "---------------------------------------------"
	$(AR) rsc $@ $^

########################################################

#############################################################################
# Création de la lib "simplification"
#############################################################################

$(SIMPLIFICATION) : MODULE/SIMPLIFICATION/simplification.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Création de librairie simplification"
	@echo "---------------------------------------------"
	$(AR) rsc $@ $^

########################################################

#############################################################################
# Création de la lib "bezier"
#############################################################################

$(BEZIER) : MODULE/BEZIER/bezier.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Création de librairie bezier"
	@echo "---------------------------------------------"
	$(AR) rsc $@ $^

########################################################

########################################################
# regle generique : 
#  remplace les regles de compilation separee de la forme
#	module.o : module.c module.h
#		$(CC) -c $(COMPILOPTS) module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules
MODULE/GEOM2D/geom2d.o : MODULE/GEOM2D/geom2d.c INCLUDES/geom2d.h INCLUDES/types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module geom2d"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@

MODULE/IMAGE/image.o : MODULE/IMAGE/image.c INCLUDES/image.h INCLUDES/types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@

MODULE/CONTOUR/contour.o : MODULE/CONTOUR/contour.c INCLUDES/contour.h INCLUDES/types_macros.h INCLUDES/struct_liste.h INCLUDES/geom2d.h INCLUDES/image.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module contour"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@

MODULE/STRUCT_LISTE/struct_liste.o : MODULE/STRUCT_LISTE/struct_liste.c INCLUDES/struct_liste.h INCLUDES/geom2d.h INCLUDES/types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module struct_liste"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@

MODULE/EPS/eps.o : MODULE/EPS/eps.c INCLUDES/eps.h INCLUDES/geom2d.h INCLUDES/types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module eps"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@

MODULE/SIMPLIFICATION/simplification.o : MODULE/SIMPLIFICATION/simplification.c INCLUDES/simplification.h INCLUDES/geom2d.h INCLUDES/types_macros.h INCLUDES/struct_liste.h INCLUDES/contour.h INCLUDES/bezier.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module simplification"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@

MODULE/BEZIER/bezier.o : MODULE/BEZIER/bezier.c INCLUDES/bezier.h INCLUDES/geom2d.h INCLUDES/types_macros.h INCLUDES/struct_liste.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module bezier"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@


BIN/test_bezier.o : TEST/test_bezier.c INCLUDES/geom2d.h INCLUDES/bezier.h INCLUDES/types_macros.h INCLUDES/contour.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_bezier"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@


BIN/test_simplification_bezier.o : TEST/test_simplification_bezier.c INCLUDES/types_macros.h INCLUDES/contour.h INCLUDES/image.h INCLUDES/simplification.h INCLUDES/eps.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_simplification_bezier"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@

BIN/test_bezier_3.o : TEST/test_bezier_3.c INCLUDES/geom2d.h INCLUDES/bezier.h INCLUDES/types_macros.h INCLUDES/contour.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_bezier_3"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@


BIN/test_simplification_bezier_3.o : TEST/test_simplification_bezier_3.c INCLUDES/types_macros.h INCLUDES/contour.h INCLUDES/image.h INCLUDES/simplification.h INCLUDES/eps.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_simplification_bezier_3"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@

########################################################
# regles explicites de creation des executables

TEST/test_bezier : BIN/test_bezier.o $(GEOM2D) $(BEZIER) $(STRUCT_LISTE)
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -L$(LIBDIR) -lgeom2d -L$(LIBDIR) -lbezier -L$(LIBDIR) -lstruct_liste -o $@


TEST/test_simplification_bezier : BIN/test_simplification_bezier.o $(CONTOUR) $(IMAGE) $(SIMPLIFICATION) $(STRUCT_LISTE) $(EPS) $(BEZIER)
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -L$(LIBDIR) -lgeom2d -o $@


TEST/test_bezier_3 : BIN/test_bezier_3.o $(GEOM2D) $(BEZIER) $(STRUCT_LISTE)
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -L$(LIBDIR) -lgeom2d -L$(LIBDIR) -lbezier -L$(LIBDIR) -lstruct_liste -o $@


TEST/test_simplification_bezier_3 : BIN/test_simplification_bezier_3.o $(CONTOUR) $(IMAGE) $(SIMPLIFICATION) $(STRUCT_LISTE) $(EPS) $(BEZIER)
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -L$(LIBDIR) -lgeom2d -o $@

########################################################
# regle pour "nettoyer" le répertoire
clean:
	rm -fR $(EXECUTABLES) BIN/*.o MODULE/*/*.o

# full clean
fclean : clean
	rm -fR LIB/*.a

re : fclean all
