#!/bin/bash



# Ce fichier sert a tester tous les fichier .pbm contenue dans ../IMAGES_TESTS et de les mettre dans un dossier IMAGES_TESTS_NEG


#si il n'y a pas de dossier IMAGES_TESTS_NEG on le cree
if [ ! -d ../IMAGES_TESTS_NEG ]
then 
	echo "Création du dossier IMAGES_TESTS_NEG"
	mkdir ../IMAGES_TESTS_NEG 
fi 


# Si il n'y a pas d'éxécutable test_image on le cree 
if [ ! -f test_image ]
then 
	echo "Création de l'éxécutable test_image"
	make test_image
fi


#Execution de l'executable 

./test_image ../IMAGES_TESTS/* 
