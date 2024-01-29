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
CFLAGS= -g -Wall -Wextra -Werror

# chemin d'acces aux librairies (interfaces)
INCDIR = includes

# Listes de tous les fichiers interfaces
FILEH = $(INCDIR)/$(wildcard *.h)

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# liste des executables
EXECUTABLES = TEST/test_image TEST/test_lecture_fichier

# chemin d'acces aux librairies (binaires)
LIBDIR = LIBRARY

# options pour l'édition des liens
LDOPTS = -L$(LIBDIR) -limage -L. -lm

# Nom pour la creation des différentes lib
IMAGE = LIBRARY/libimage.a

#############################################################################
# definition des regles
#############################################################################

########################################################
# la règle par défaut
all : $(EXECUTABLES)


# Règle pour la création de la lib image
limage : $(IMAGE)

#############################################################################
# Création de la lib "image"
#############################################################################

$(IMAGE) : binaries/image.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Création de librairie image"
	@echo "---------------------------------------------"
	$(AR) rsc $@ $^
#	mv $(TARGET) LIBRARY/
########################################################


########################################################
# Règle pour la création des .o
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
binaries/image.o : SRC/image.c $(FILEH)
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(INCLUDEOPTS) $< -o $@
#	$(MAKE) limage

binaries/test_image.o : TEST/test_image.c $(FILEH)
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_image"
	@echo "---------------------------------------------"
	$(CC) -c $(CFLAGS) $(INCLUDEOPTS) $< -o $@

binaries/test_lecture_fichier.o : TEST/test_lecture_fichier.c $(FILEH)
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_lecture_fichier"
	@echo "---------------------------------------------"
	$(CC) -c $(CFLAGS) $(INCLUDEOPTS) $< -o $@

########################################################
# regles explicites de creation des executables

TEST/test_image : binaries/test_image.o $(IMAGE)
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

TEST/test_lecture_fichier : binaries/test_lecture_fichier.o $(IMAGE)
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

########################################################
# regle pour "nettoyer" le répertoire
clean:
	rm -fR $(EXECUTABLES) binaries/*.o

# full clean
fclean : clean
	rm -fR LIBRARY/*.a

re : fclean all
