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
EXECUTABLES = TEST/test_struct_liste TEST/test_contour TEST/test_contour_neg TEST/test_contour_a_la_volee

# chemin d'acces aux librairies (binaires)
LIBDIR = LIB

# options pour l'édition des liens
LDOPTS = -L. -lm

# Nom pour la creation des différentes lib
GEOM2D = $(LIBDIR)/libgeom2d.a

IMAGE = $(LIBDIR)/libimage.a

STRUCT_LISTE = $(LIBDIR)/libstruct_liste.a

CONTOUR = $(LIBDIR)/libcontour.a

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
#############################################################################
# Création de la lib "geom2d"
#############################################################################

$(GEOM2D) : BIN/geom2d.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Création de librairie geom2d"
	@echo "---------------------------------------------"
	$(AR) rsc $@ $^

########################################################

#############################################################################
# Création de la lib "image"
#############################################################################

$(IMAGE) : BIN/image.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Création de librairie image"
	@echo "---------------------------------------------"
	$(AR) rsc $@ $^

########################################################

#############################################################################
# Création de la lib "struct_liste"
#############################################################################

$(STRUCT_LISTE) : BIN/struct_liste.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Création de librairie struct_liste"
	@echo "---------------------------------------------"
	$(AR) rsc $@ $^

########################################################

#############################################################################
# Création de la lib "contour"
#############################################################################

$(CONTOUR) : BIN/contour.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Création de librairie contour"
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
BIN/geom2d.o : SRC/geom2d.c INCLUDES/geom2d.h INCLUDES/types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module geom2d"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@

BIN/image.o : SRC/image.c INCLUDES/image.h INCLUDES/types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@

BIN/contour.o : SRC/contour.c INCLUDES/contour.h INCLUDES/types_macros.h INCLUDES/struct_liste.h INCLUDES/geom2d.h INCLUDES/image.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module contour"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@

BIN/struct_liste.o : SRC/struct_liste.c INCLUDES/struct_liste.h INCLUDES/geom2d.h INCLUDES/types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module struct_liste"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@

BIN/test_struct_liste.o : TEST/test_struct_liste.c INCLUDES/geom2d.h INCLUDES/struct_liste.h INCLUDES/types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_struct_liste"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@

BIN/test_contour.o : TEST/test_contour.c INCLUDES/geom2d.h INCLUDES/struct_liste.h INCLUDES/image.h INCLUDES/types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_contour"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@

BIN/test_contour_neg.o : TEST/test_contour_neg.c INCLUDES/geom2d.h INCLUDES/struct_liste.h INCLUDES/image.h INCLUDES/types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_contour_neg"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@

BIN/test_contour_a_la_volee.o : TEST/test_contour_a_la_volee.c INCLUDES/geom2d.h INCLUDES/struct_liste.h INCLUDES/image.h INCLUDES/types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_contour_a_la_volee"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@

########################################################
# regles explicites de creation des executables

TEST/test_struct_liste : BIN/test_struct_liste.o $(STRUCT_LISTE) $(GEOM2D)
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -L$(LIBDIR) -lgeom2d -o $@

TEST/test_contour : BIN/test_contour.o $(STRUCT_LISTE) $(GEOM2D) $(IMAGE) $(CONTOUR)
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -L$(LIBDIR) -limage -L$(LIBDIR) -lgeom2d -o $@

TEST/test_contour_neg : BIN/test_contour_neg.o $(STRUCT_LISTE) $(GEOM2D) $(IMAGE) $(CONTOUR)
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -L$(LIBDIR) -limage -L$(LIBDIR) -lgeom2d -o $@

TEST/test_contour_a_la_volee : BIN/test_contour_a_la_volee.o $(STRUCT_LISTE) $(GEOM2D) $(IMAGE) $(CONTOUR)
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -L$(LIBDIR) -limage -L$(LIBDIR) -lgeom2d -o $@



########################################################
# regle pour "nettoyer" le répertoire
clean:
	rm -fR $(EXECUTABLES) BIN/*.o

# full clean
fclean : clean
	rm -fR LIB/*.a

re : fclean all
