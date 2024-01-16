#!/bin/bash

# Pour toutes les images contenues dans ../IMAGES_TESTS
# on fais son negatif qu'on place dans un dossier ../IMAGES_TESTS_NEG

# On fais le make
make

#si le make ne s'est pas bien passe on exit 
if [ $? -ne 0 ]
then
    exit 1
fi


# si le dossier IMAGES_TESTS_NEG n'existe pas on le cree
mkdir -p ../IMAGES_TESTS_NEG

for file in ../IMAGES_TESTS/*
do
    echo "test de l'image $file"
    ./test_image $file
done

mv ../IMAGES_TESTS/*negatif* ../IMAGES_TESTS_NEG/.

