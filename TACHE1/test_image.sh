#!/bin/bash

# Pour toutes les images contenues dans ../IMAGES_TESTS
# on fais son negatif qu'on place dans un dossier ../IMAGES_TESTS_NEG

# Vérification du bon nombre d'argument
if [ $# -ne 1 ] || [ ! -d $1 ]
then
    echo "Utilisation : ./test_image.sh <nom_dossier> (où nom_dossier est un dossier qui contient des .pbm)"
    exit 1
fi

# On fais le make
make

#si le make ne s'est pas bien passe on exit 
if [ $? -ne 0 ]
then
    echo "ERREUR DANS LA MAKE"
    exit 1
fi


nom_doss_neg=$1_NEG

# si le dossier IMAGES_TESTS_NEG n'existe pas on le cree
mkdir -p $nom_doss_neg

for file in $1/*.pbm
do
    echo "test de l'image $file"
    ./TEST/test_image $file
done

#On met tous les négatifs cree dans le dossier IMAGE_TESTS_NEG
echo "On met toutes les images negatives dans le dossier $nom_doss_neg"
mv $1/*negatif* $nom_doss_neg

