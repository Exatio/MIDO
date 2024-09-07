#!/bin/bash

dossier=$1

if [ $# -ne 1 ]
then
  echo "Un argument : nom de répertoire"
  exit 1
fi

if [ ! -d $dossier ]
then
  echo "Donnez un nom de répertoire valide"
  exit 1
fi

for element in $(ls $dossier)
do
  type="fichier"
  if [ -d "$dossier/$element" ]
  then
    type="repertoire"
  fi

  echo "$element est un $type"
done