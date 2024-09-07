# TD2 : Fonctions et tableaux

## Exercice 1 : Tableaux

### Écrire une fonction qui prend en arguments un tableau d’entiers ainsi que sa taille, et qui l’affiche. Pourquoi avons-nous besoin de la taille en argument ?

```C
void afficheTableau(int elemCount, int tab[]) {  
    for(int i = 0 ; i < elemCount ; i++)  
    {        
	    printf("Element %d : %d\n", i+1, tab[i]);  
    }
}
```

On a la taille en argument car un tableau est en réalité une référence (un pointeur) au premier élément d'un tableau.
On ne sait pas en mémoire si la prochaine "case mémoire" contient un élément du tableau ou de la mémoire qui n'a rien à voir avec notre programme.
Pour ne pas déborder, on a besoin de garder un suivi de la taille du tableau pour ne pas "dépasser les cases de mémoires réservées au tableau".

### Écrire une fonction qui prend en arguments un tableau d’entiers ainsi que sa taille n, et qui demande la saisie de n entiers à placer dans le tableau.

```C
void saisirElementsTableau(int elemCount, int tab[]) {  
    for(int i = 0 ; i < elemCount ; i++)  
    {        printf("Element %d : \n", i+1);  
        scanf("%d", &tab[i]);  
    }
}
```

### Écrire une fonction qui prend en arguments un tableau d’entiers et sa taille, et qui renvoie la somme des entiers présents dans le tableau.

```C
int sommeElementsTableau(int elemCount, int tab[]) {  
    int somme = 0;  
    for(int i = 0 ; i < elemCount ; i++)  
    {
	    somme += tab[i];  
    }
    return somme;  
}
```

### Écrire une fonction main() qui définit un tableau de taille 4 et appelle les 3 fonctions précédentes.

```C
int main() {  
  
    int tab[4];  
    saisirElementsTableau(4, tab);  
    afficheTableau(4, tab);  
    printf("Somme éléments dudit tableau : %d\n", sommeElementsTableau(4, tab));  
    return 0;  
}
```

### Que faut-il faire si on veut maintenant un tableau de taille 10 ? Modifier la taille du tableau à l’aide d’une constante N. Modifier la fonction main() pour qu’il demande à l’utilisateur le nombre de valeurs désirées (et redemande tant que ce nombre est plus grand que N).

```C
int main() {  
	int n = 0;
	printf("Combien d'éléments dans le tableau ?\n");
	scanf("%d", &n);
	
    int tab[n];  
    saisirElementsTableau(n, tab);  
    afficheTableau(n, tab);  
    printf("Somme éléments dudit tableau : %d\n", sommeElementsTableau(n, tab));  
    return 0;  
}
```


## Exercice 2 : Doublons

### Écrire une fonction i``nt nbOccurrencesTab(int tab[], int n, int a)`` renvoyant le nombre d’occurrences de ``a`` dans le tableau ``tab`` de taille ``n``.

> Par souci de clarté, j'ai renommé la variable a.

```C
int nbOccurrencesTab(int tab[], int n, int countElem) {  
    int nCount = 0;  
    for(int i = 0 ; i < countElem ; i++)  
        if(tab[i] == n) nCount++;  
    return nCount;  
}
```

### En déduire une fonction ``int contientDoublons(int tab[], int n) ``qui renvoie 1 si ``tab`` contient un doublon et 0 sinon.

```C
int contientDoublons(int tab[], int n) {  
  
    int doublon = 0;  
    for(int i = 0 ; i < n ; i++)  
        if(nbOccurrencesTab(tab, tab[i], n) != 1) doublon = 1;  
    return doublon;  
  
}
```

## Exercice 3 : Second plus grand 

Écrire une fonction qui prend en arguments un tableau tab et sa taille. Cette fonction retourne l’indice du second plus grand élément du tableau (on suppose que le tableau est de taille au moins 2).


Pour moi, la manière la plus intuitive de réaliser cette fonction est la suivante : 

```C
int secondPlusGrand(int elemCount, int tab[]) {  
  
    int max = tab[0], scdMax = tab[0];  
  
    for(int i = 1 ; i < elemCount ; i++)  
    {
	    if(tab[i] > max) max = tab[i];  
    }  
    
    for(int i = 1 ; i < elemCount ; i++)  
    {
	    if(tab[i] > scdMax && tab[i] != max) scdMax = tab[i];  
    }  
    
    return scdMax;  
}
```


## Exercice 4 : Sommes à k

### Écrire une fonction qui prend en arguments un tableau tab, sa taille et un entier k. Cette fonction recherche (et affiche) les paires d’éléments du tableau dont la somme vaut k. La fonction retourne le nombre de paires trouvées.

```C
int paires(int elemCount, int tab[], int k) {  
  
    int pairesTrouvees = 0;  
  
    for(int i = 0 ; i < elemCount ; i++) {  
        for(int j = i+1 ; j < elemCount  ; j++) {   
			if(tab[j]+tab[i] == k) {  
                printf("{%d, %d} de coordonnées {%d, %d}\n", tab[i], tab[j], i, j);  
                pairesTrouvees++;  
            }
        }
    }
      
    return pairesTrouvees;  
}
```

> On fait un petit peu d'optimisation, on s'embête pas à vérifier les i indices avant puisqu'on les a déjà vérifiés auparavant.
> On ne vérifie pas non plus la dernière ligne, puisqu'elle a déjà été comparée à toutes les autres.
> Cela permet également d'éviter les doublons !

### Écrire une fonction main() qui appelle la fonction de saisie d’un tableau (déjà écrite) puis cette fonction et qui affiche le nombre de paires trouvées.

Rien de plus simple : 

```C
int main() {  
    int tab[] = {1, 7, 5, 3};  
    printf("%d paires.", paires(4, tab, 8));  
    return 0;
}
```

On a alors en résultat :

```
{1, 7} de coordonnées {0, 1}
{5, 3} de coordonnées {2, 3}
2 paires.
```

### Question *[bonus]* 

> Le nombre d’opérations dans le pire cas de la fonction précédente est de l’ordre de la taille du tableau au carré.

C'est faux ! avec nos optimisations on a réduit cela drastiquement.

**On va dans un premier temps mettre toutes les cases de ``tab2`` à -1. Puis, on va stocker i dans ``tab2[tab[i]]``, pour chaque case de ``tab``** 

La taille nécessaire pour ``tab2`` est la valeur du plus grand élément de ``tab``.
D'où l'utilisation de ma fonction ``max`` suivante :

```C
int max(int elemCount, int tab[]) {  
  
    int max = tab[0];  
  
    for(int i = 1 ; i< elemCount ; i++)  
    {
	    if(tab[i] > max) max = tab[i];  
    }  
    return max;  
  
}
```

Pour se servir ensuite de ce tableau pour déterminer s'il existe un complément à ``k`` pour un ``tab[i]``, c'est en fait très simple : si ``tab[2] = 7`` et qu'on cherche l'existence d'un complément à 8, on calcule ``8-7=1``, et ensuite on vérifie l'existence de 1 dans ``tab``.
Pour cela, on regarde ``tab2[1]`` qui vaudra -1 si 1 n'est pas dans le tableau, ou son indice dans tab autrement.

En résumé, on peut réaliser la fonction suivante :

```C
int paires(int elemCount, int tab[], int k) {

	// On suppose l'existence d'une fonction max qui renvoie le plus grand des éléments du tableau. Ainsi tab2[tab[i]] existera pour tout i
	int tab2[max(elemCount, tab)]; 
	int paires = 0;
	
	for(int i = 0 ; i < elemCount ; i++) {
		tab2[i] = -1;
	}
	
	for(int i = 0 ; i < elemCount ; i++) {  
	    tab2[tab[i]] = i;  
	}
	
	// Pour chaque élément du tableau, on vérifie la présence du complémentaire :
	for(int i = 0 ; i < elemCount ; i++) {
	
		if(tab2[k - tab[i]] != -1) {		
			printf("{%d, %d} de coordonnées {%d, %d}", tab[i], k - tab[i], i, tab2[k - tab[i]]); 
			paires++
		}
		
	}

	return paires/2; // (on a compté chaque paire 2 fois)
}
```

On a : 
- ``i`` indice de l'élément actuel
- `` tab[i]`` valeur de l'élément actuel
-  ``k - tab[i]`` la valeur de l'élément cherché 
- `` tab2[k - tab[i]]`` l'indice de la valeur cherchée, -1 si elle n'est pas dans le tableau.

On obtient (avec le même programme main que dans la question 2) :

```
{1, 7} de coordonnées {0, 1}
{7, 1} de coordonnées {1, 0}
{5, 3} de coordonnées {2, 3}
{3, 5} de coordonnées {3, 2}

2 paires.
```

> A noter que cette fonction n'est valide **SI ET SEULEMENT SI** tous les entiers du tableau sont différents. Sinon le nombre de paires comptées ne sera pas correct.


