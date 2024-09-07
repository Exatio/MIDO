#!/bin/bash

fichier=$1

if [ $# -ne 1 ]
then
  echo "Un argument : nom de fichier"
  exit 1
fi

if [ ! -e $fichier ]
then
  echo "Donnez un nom de fichier valide"
  exit 1
fi

total_lignes=`tail -n +0 $fichier | wc -l`
i=$((total_lignes+1))

while [ $i -gt 0 ]
do
  echo `head -n $i $fichier | tail -n 1`
  i=$((i-1))
done

