#!/bin/bash

mdp="351a7b5994f2b820a91812722119afca"
mots="smolwords.txt" # "/usr/share/dict/words" mais pour des besoins pratiques c'est plus rapide
for mot in $(cat $mots)
do
    crypte=$(echo "$mot" | md5sum | cut -d ' ' -f 1)
    echo "mot analyse est $mot, son crypte est $crypte"
    if [ "$crypte" = "$mdp" ]
    then
        echo "Le mot de passe est $mot"
        exit 0
    fi
done

echo "Mot de passe non trouvé"