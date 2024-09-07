# Introduction

La création du compilateur pour la machine virtuelle a été plutôt fastidieuse, mais après un certain temps de réflexion nous avons réussi à trouver une solution pour le rendre :\
- très modulable (grande facilité d'ajouter de nouvelles instructions si nécessaire)
- clair (les erreurs s'expliquent d'elles-mêmes)
Ce document va essayer de détailler les méthodes utilisées.

# Déroulement de la programmation
## Idée du modèle utilisé

Pour détecter les erreurs de syntaxe, nous nous sommes basés sur le modèle suivant :\
Une ``INSTRUCTION`` est constituée de son nom (`add` par exemple) ainsi que des attentes qu'elles a en tant qu'arguments.\
Par exemple, l'instruction de sortie a pour nom `out` et a pour attente uniquement un registre, qui sera compilé dans les bits de `dest`.
C'est pour quoi l'instruction de sortie est créée de la manière suivante : \
`{"out", {{MEM_DEST, TOKEN_ARG_REGISTER}}}`
> Afin d'avoir les mêmes indices d'instruction que sur l'énoncé, nous avons dû créer des instructions "vides" ne servant qu'à prendre un index en plus, pour être sûr que les indices correspondaient.
> Le programme est facilement modifiable pour les retirer cependant.


Dans ce cas, `MEM_DEST` et `TOKEN_ARG_REGISTER` sont des entiers, définis par leur nom grâce au type `enum` en C.\
L'utilisation d'énumération permet de grandement améliorer la lisibilité du code.\
Chaque instruction peut avoir jusqu'à 3 arguments, et grâce à l'utilisation d'énumération, ne pas en donner leur met par défaut la valeur 0, correspondant à `TOKEN_NO_TOKEN`, qui signifie donc qu'on s'attend à une fin de ligne dès qu'on a reçu tous les arguments.

Sachant ceci, on peut dérouler l'exécution de la compilation.

## Création de `tagList`

Premièrement, on itère sur toutes les lignes du fichier, et on regarde si le premier "mot" (séparé par des espaces) est une étiquette ou non.
Ceci est utile pour créer une liste d'étiquettes valides, ainsi que sauvegarder leur adresse. Je reviendrais plus tard sur l'utilité de cette liste.

Ensuite, on replace le curseur au début du fichier et on recommence une nouvelle itération sur toutes les lignes du fichier.

## Itération principale

Cette fois, on envoie la ligne à la fonction `processLine` qui s'occupe de regarder si une ligne est correcte, de la traduire si c'est le cas et d'afficher une erreur si ça ne l'est pas.
Tout au long de la fonction, on va garder un tableau `nextTokenExpectations`, créé et modifié de telle façon que peu importe l'endroit ou nous sommes dans la ligne, `nextTokenExpectations[0]` renvoie le type de token que nous sommes censés récupérer.
Au début d'une ligne, on s'attend à recevoir une étiquette ou une instruction, d'où la valeur par défaut de  `nextTokenExpectations[0]` : `TOKEN_TOI` (tag or instruction).
Ensuite, grâce à la fonction strtok, on va découper la ligne en "mots" par les espaces.
Ainsi pour la ligne `add r1, r2, #5` on itérera sur les tokens `add`, `r1,`, `r2,`, et `#5`.
Pour chaque token, on tentera d'identifier le type de token qu'on a actuellement : on regarde s'il commence par un `r` pour savoir s'il s'agit d'une instruction, ou par  `#` pour s'avoir s'il s'agit d'un argument décimal par exemple. On comparera également le token avec les la liste d'instructions (pour savoir s'il s'agit d'une instruction ou non), mais également avec tous les éléments de la liste des étiquettes.
C'est le moyen que nous avons trouvé pour contourner un problème : quid du cas où l'étiquette est définie après la ligne courante dans le code. Maintenant, on peut tout simplement regarder dans la liste des étiquettes, et si elle est dedans, on peut directement accéder à la valeur qui doit remplacer cette dernière dans le fichier compilé.
Ensuite, en fonction du token reçu, on met à jour la liste des arguments attendus à la suite de la ligne.
Par exemple, s'il s'agit d'une instruction, on récupère les arguments attendus de l'instruction et on les met tous dans le tableau.
S'il s'agit d'un argument, on décale tous les arguments vers la gauche, etc.
Une fois que le type de token attendu et le type du token actuel sont déterminés, on les compare, et on renvoie une erreur si les deux sont différents. Sinon, ça signifie que le token est valide, et qu'on peut donc le charger dans le fichier hexadécimal.
Pour cela, on regarde simplement le type actuel, et le type de mémoire dans lequel on doit le sauvegarder (c'est une information enregistrée avec l'instruction).
Par exemple, si le type est `TOKEN_ARG_REGISTER` et le type de mémoire `MEM_DEST`, je sais que je dois mettre le numéro de registre dans rd.
Une fois que j'ai passé sur tous mes tokens, si l'entièreté de la ligne est valide, je concatène tous les bits (enregistrés au préalable en binaire) dans l'ordre (s'ils n'ont pas été définis, ils sont à 0 par défaut), puis grâce à une astuce (on récupère le string comme entier puis on le convertit en hexa), je met directement l'entièreté de la ligne dans le fichier compilé en hexadécimal. 

Voici donc l'essentiel de ce que fait le code du compilateur. J'ai légèrement survolé la détection des token en tant qu'argument qui est particulièrement longue (puisque plein de cas différents : faire en sorte que `#5 (r6)#5 #hFFFF (r5) r21` fonctionnent mais pas `#-50000000 #aze r50)`), mais elle n'est pas compliquée à comprendre, seulement fastidieuse et il n'y a aucun intérêt à détailler cette partie.

# Autres

## Github
Nous avons mis en place un repo Github afin de pouvoir travailler en collaboration en binôme

## Difficultés rencontrées
L'organisation du temps et des rôles n'était pas particulièrement efficace.
Le débogage a été particulièrement long, et il est difficile d'être sûr que nous avons correctement tout vérifié.
Nous avons fait beaucoup de tests (d'où les fichiers `demo` que nous mettons également à disposition), mais on ne peut jamais être sûr d'à quel point les utilisateurs peuvent dépasser nos attentes en terme de non-respect de syntaxe. 

## Améliorations possibles
Malgré le fait que cela nécessite un effort très fastidieux, il serait intéressant de vérifier à la compilation la validité de programme (fera toujours une boucle infinie, code jamais exécuté) comme sur la majorité des éditeurs de texte moderne.
