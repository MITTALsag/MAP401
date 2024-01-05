#############################################################################
# Fichier Makefile 
# UE MAP401 - DLST - UGA - 2020/2021
#############################################################################
# utilisation des variables internes $@ $< $^ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond a toutes les dependances
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = clang

# chemin d'acces aux librairies (interfaces)
INCDIR = .

# chemin d'acces aux librairies (binaires)
LIBDIR = .

# options pour l'edition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# liste des executables
EXECUTABLES = test_struct_liste test_contour test_contour_a_la_volee


#############################################################################
# definition des regles
#############################################################################

########################################################
# la regle par defaut
all : $(EXECUTABLES)

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
geom2d.o : geom2d.c geom2d.h types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module geom2d"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

image.o : image.c image.h types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

contour.o : contour.c contour.h types_macros.h struct_liste.h geom2d.h image.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module contour"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

struct_liste.o : struct_liste.c struct_liste.h geom2d.h types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module struct_liste"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_struct_liste.o : test_struct_liste.c geom2d.h struct_liste.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_struct_liste"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_contour.o : test_contour.c geom2d.h struct_liste.h image.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_contour"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_contour_a_la_volee.o : test_contour_a_la_volee.c geom2d.h struct_liste.h image.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_contour_a_la_volee"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<



########################################################
# regles explicites de creation des executables

test_struct_liste : test_struct_liste.o struct_liste.o geom2d.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_contour : test_contour.o struct_liste.o geom2d.o image.o contour.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_contour_a_la_volee : test_contour_a_la_volee.o struct_liste.o geom2d.o image.o contour.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@



# regle pour "nettoyer" le repertoire
clean:
	rm -fR $(EXECUTABLES) *.o 
