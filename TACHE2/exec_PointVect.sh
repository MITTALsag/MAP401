#!/bin/bash



#si il n'y a pas de dossier ../TEST_FILES on arrete
if [ ! -d ../TEST_FILES ]
then 
    echo "Il n'y a pas de fichier a tester pour ce fichier veuiller lancer
    test_fichier_PointVect manuelemnt"
    exit 1
fi


for dir in ../TEST_FILES/*
do
    echo lancement des test sur $dir
    ./test_fichier_PointVect $dir/*
    echo "--------------------------------------------------"
done

