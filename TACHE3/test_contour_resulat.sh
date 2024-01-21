#!/bin/bash

# ATTENTION CE FICHIER DOIT ETRE LANCER SI ON SE TROUVE DANS LE DOSSIER TACHE3

# Ce programme sert a tester si les contours des images dans ../IMAGES_TESTS et
# IMAGES_TESTS_NEG sont les même apres l'appel de l'éxécutable contour.sh
# Pour cela on utilise la commande diff qui renvoie 0 si les deux fichier en
# arguments sont les mêmes et 1 sinon.
# Donc normalement il faut que la commande : diff <nom image> <nom image neg>
# Revoie 0 pour cahque image. (Où <nom image> se trouve dans IMAGES_TESTS et 
# <nom image neg> est le négatif de <nom image>


# On re-crée les images négatives si elels n'existent pas
if [ ! -d ../IMAGES_TESTS_NEG ]
then
    cd ../TACHE1
    ./test_image.sh ../IMAGES_TESTS
fi


# On cree le contour de IMAGES_TESTS et IMAGES_TESTS_NEG si ils n'existent pas
# déjà
if [ ! -d ../IMAGES_TESTS_CONTOUR ]
then
    cd ../TACHE3
    ./contour.sh ../IMAGES_TESTS
fi
if [ ! -d ../IMAGES_TESTS_NEG_CONTOUR ]
then
    cd ../TACHE3
    ./contour_neg.sh ../IMAGES_TESTS_NEG
fi

# On se met dans le dossier contenant IMAGES_TESTS_CONTOUR et
# IMAGES_TESTS_NEG_CONTOUR
cd ..
suffixe_neg=_negatif
compteur_reussi=0
compteur_rate=0
compteur_test=0

for contour in IMAGES_TESTS_CONTOUR/*.contour
do
   nom_cont_neg=$(echo "$contour" | cut -f1 -d '.' | cut -f2 -d '/')

   echo "Test du contour de l'image $nom_cont_neg"
   echo "----------------------------------------------------------"

   diff -sBb $contour IMAGES_TESTS_NEG_CONTOUR/$nom_cont_neg$suffixe_neg.contour > /dev/null

    if [ $? -ne 0 ]
    then
      echo "l'image $nom_cont_neg n'a pas le même contour que son négatif"
      compteur_rate=$(( $compteur_rate + 1))
    else
      echo "l'image $nom_cont_neg a bien le même contour que son négatif"
      compteur_reussi=$(( $compteur_reussi + 1))

    fi
    compteur_test=$(( $compteur_test + 1))
  echo "----------------------------------------------------------"
  echo ""
  echo""
done

echo ""
echo "NB TEST : $compteur_test"
echo "PASS : $compteur_reussi | FAIL : $compteur_rate "

