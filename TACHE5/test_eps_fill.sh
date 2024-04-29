
#!/bin/bash



# Ce fichier prend en argument un dossier contenant au moins un fichier .pbm
# puis il execute le contour.sh pour calculer les contour des .pbm qui se
# trouvent dans le fichier
# Puis il execute sur chaque fichier .pbm test_eps_multiple pour cree une image
# au format eps et enfin place ces images dans un dossier du meme nom que
# l'argumnet suffixé par EPS_FILL


# Vérification du bon nombre d'argument
if [ $# -ne 1 ] || [ ! -d $1 ]
then
    echo "Utilisation : ./contour <nom_dossier> (où nom_dossier est un dossier qui contient des .pbm)"
    exit 1
fi


./contour.sh $1


# Cette variable verifie si il y a au moins une image eps cree et si c'est le cas
# alors on cree le dossier et on fais la commande pour bouger l'image eps cree dans le bon dossier
exist_eps=0

for file in $1/*.pbm
do
    # pour mettre dans nom_fich_contour
    # IMAGE_TEST_CONTOUR/<nom_du_fichier>.contour.txt
    nom_fich_contour=${file%????}
    nom_fich_contour=${nom_fich_contour#???????????}
    nom_fich_contour=IMAGE_TEST_CONTOUR_MULTIPLE/$nom_fich_contour.contour.txt

    echo ""
    echo "calcul de l'image $file avec le contour $nom_fich_contour"

    ./TEST/test_eps_multiple $file $nom_fich_contour

    if [ $? -eq 0 ]
    then
        exist_eps=1
    fi

done

nom_doss_cont=$1_FILL_EPS_MULTIPLE
if [ $exist_eps -eq 1 ]
then
    # si le dossier IMAGES_TESTS_EPS n'existe pas on le cree
    mkdir -p $nom_doss_cont

    #On met toutes les images eps dans le dossier IMAGE_TESTS_EPS
    echo ""
    echo ""
    echo "On met touts les contours dans le dossier $nom_doss_cont"
    mv $1/*.eps $nom_doss_cont
fi



