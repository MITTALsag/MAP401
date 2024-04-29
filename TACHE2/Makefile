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
EXECUTABLES = TEST/test_alea_geom2d TEST/test_geom2d 

# chemin d'acces aux librairies (binaires)
LIBDIR = LIB

# options pour l'édition des liens
LDOPTS = -L$(LIBDIR) -lgeom2d -L. -lm

# Nom pour la creation des différentes lib
GEOM2D = $(LIBDIR)/libgeom2d.a

#############################################################################
# definition des regles
#############################################################################

########################################################
# la règle par défaut
all : $(EXECUTABLES)


# Règle pour la création de la lib point et vecteur
lgeom2d : $(GEOM2D)


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
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules

BIN/geom2d.o : SRC/geom2d.c $(FILEH)
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module geom2d"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@

BIN/test_alea_geom2d.o : TEST/test_alea_geom2d.c $(FILEH)
	@echo "---------------------------------------------"
	@echo "Compilation du module test_alea_geom2d"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@

BIN/test_geom2d.o : TEST/test_geom2d.c $(FILEH)
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_geom2d"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@

########################################################
# regles explicites de creation des executables

TEST/test_alea_geom2d : BIN/test_alea_geom2d.o $(GEOM2D)
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

TEST/test_geom2d : BIN/test_geom2d.o $(GEOM2D)
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@


########################################################
# regle pour "nettoyer" le répertoire
clean:
	rm -fR $(EXECUTABLES) BIN/*.o

# full clean
fclean : clean
	rm -fR LIB/*.a

re : fclean all





