
#!/bin/bash



# Ce fichier prend en argument un dossier contenant au moins un fichier .pbm
# Il calcul ensuite son contour et enfin ecrit le contour dans un image eps du
# même nom que le fichier suffixé par .eps
# Ce fichier est ensuite sotcké dans un dossier du même nom que le dossier
# passé en argument suffixé par _EPS



# Vérification du bon nombre d'argument
if [ $# -ne 1 ] || [ ! -d $1 ]
then
    echo "Utilisation : ./contour <nom_dossier> (où nom_dossier est un dossier qui contient des .pbm)"
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


nom_doss_cont=$1_FILL_EPS

# Cette variable verifie si il y a au moins une image eps cree et si c'est le cas
# alors on cree le dossier et on fais la commande pour bouger l'image eps cree dans le bon dossier
exist_eps=0

for file in $1/*.pbm
do
    echo ""
    echo "calcul de l'image $file"

    ./TEST/test_eps_fill $file

    if [ $? -eq 0 ]
    then
        exist_eps=1
    fi

done

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



