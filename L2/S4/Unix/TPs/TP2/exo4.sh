#!/bin/bash

if [ ! $# -ge 1 ]
then
  echo "Un ou plusieurs arguments : noms de répertoires"
  exit 1
fi

for dossier in $*
do
  echo
  if [ ! -d $dossier ]
  then
    echo "$dossier n'est pas un nom de dossier valide. arrêt du programme..."
    exit 1
  fi

  
  echo "Analyse de $dossier :"

  for element in $(ls $dossier)
  do
    type="fichier"
    if [ -d "$dossier/$element" ]
    then
      type="repertoire"
    fi

    echo "$element est un $type"
  done
done
