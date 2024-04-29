#!/bin/bash



# Ce fichier prend en argument un dossier contenant au moins un fichier .pbm
# Il calcul ensuite ses contours les simplifié et ensuite cree une image .eps
# de l'image (une a partir du contour originale et une a partir du contour simplifié
# Les différents fichier sont ensuite placé dans les dossier correspondant 
# - IMAGES_TEST_CONTOUR_COMPLET  : les contours complet des images
# - IMAGES_TEST_CONTOUR_SIMPLE   : les contour simplifié des images
# - IMAGES_TEST_FILL_EPS_COMPLET : les images eps cree a partir des contour complet
# - IMAGES_TEST_FILL_EPS_SIMPLE  : les images eps cree a partir des contour simple



# Vérification du bon nombre d'argument
if [ $# -ne 2 ] || [ ! -d $1 ]
then
    echo "Utilisation : ./contour <nom_dossier> (où nom_dossier est un dossier qui contient des .pbm)"
    exit 1
fi

# On fais le make
make re


#si le make ne s'est pas bien passe on exit 
if [ $? -ne 0 ]
then
    echo "ERREUR DANS LA MAKE"
    exit 1
fi


clear

contour_comp=$1_CONTOUR_COMPLET
contour_simpl=$1_CONTOUR_SIMPLE_3
eps_comp=$1_FILL_EPS_COMPLET
eps_simpl=$1_FILL_EPS_SIMPLE_3

# Cette variable verifie si il y a au moins un contour cree et si c'est le cas
# alors on cree le dossier pour le et on fais la commande pour bouger le
# contour cree dans le bon dossier
exist_cont=0

for file in $1/*.pbm
do
    echo ""
    echo "calcul de l'image $file"
    echo "Pour distance seuil d = $2"
    ./TEST/test_simplification_bezier_3 $file $2


    if [ $? -eq 0 ]
    then
        exist_cont=1
    fi

done

if [ $exist_cont -eq 1 ]
then
    # si les dossiers n'existe pas on le cree
    mkdir -p $contour_comp
    mkdir -p $contour_simpl
    mkdir -p $eps_comp
    mkdir -p $eps_simpl

    #On met tous les contours complet dans le dossier correspondant
    echo ""
    echo ""
    rm $contour_comp/*
    echo "On met touts les contours complet dans le dossier $contour_comp"
    mv $1/*contour.txt $contour_comp

    #On met tous les contours simple dans le dossier correspondant
    echo ""
    rm $contour_simpl/*
    echo "On met touts les contours simple dans le dossier $contour_simpl"
    mv $1/*contour_bezier_3_simple.txt $contour_simpl

    #On met toutes les images complete dans le dossier correspondant
    echo ""
    rm $eps_comp/*
    echo "On met toutes les images complete dans le dossier $eps_comp"
    mv $1/*fill_complet.eps $eps_comp

    #On met toutes les images simple dans le dossier correspondant
    echo ""
    rm $eps_simpl/*
    echo "On met toutes les images simple dans le dossier $eps_simpl"
    mv $1/*fill_simple_3.eps $eps_simpl
fi



