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
EXECUTABLES = TEST/test_contour_masque TEST/test_eps_multiple

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

BIN/test_contour_masque.o : TEST/test_contour_masque.c INCLUDES/geom2d.h INCLUDES/struct_liste.h INCLUDES/image.h INCLUDES/types_macros.h INCLUDES/contour.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_contour_masque"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@


BIN/test_eps_multiple.o : TEST/test_eps_multiple.c INCLUDES/eps.h INCLUDES/image.h INCLUDES/types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_eps_multiple"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@
########################################################
# regles explicites de creation des executables

TEST/test_contour_masque : BIN/test_contour_masque.o $(STRUCT_LISTE) $(GEOM2D) $(IMAGE) $(CONTOUR)
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -L$(LIBDIR) -limage -L$(LIBDIR) -lgeom2d -o $@


TEST/test_eps_multiple : BIN/test_eps_multiple.o $(STRUCT_LISTE) $(IMAGE) $(EPS)
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -L$(LIBDIR) -limage -L$(LIBDIR) -lgeom2d -o $@
########################################################
# regle pour "nettoyer" le répertoire
clean:
	rm -fR $(EXECUTABLES) BIN/*.o MODULE/*/*.o

# full clean
fclean : clean
	rm -fR LIB/*.a

re : fclean all
