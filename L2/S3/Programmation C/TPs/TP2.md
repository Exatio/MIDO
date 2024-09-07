# TP2 : Tableaux

## Exercice 1 : Tableaux

On désire faire fonctionner le programme suivant :

```C
#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>  
  
#define N 50  
  
int main() {  
    int tab1[N], tab2[N], tab3[N];  
    int nb;  
    srand(time(NULL));  
  
    do {  
        printf("Entrez le nombre de valeurs que vous désirez\n");  
        scanf("%d", &nb);  
    } while (nb > N);  
  
    Remplissage(tab1, nb);  
    Affichage(tab1, nb);  
    printf("%d %d\n", Position(tab1, nb, 2), Position(tab1, nb, 4));  
  
    Remplissage(tab2, nb);  
    Somme(tab1, tab2, tab3, nb);  
    Affichage(tab3, nb);  
  
    return 0;  
}
```

### Écrire une fonction ``Remplissage`` prenant un tableau et sa taille en arguments et qui remplit le tableau avec des valeurs aléatoires entre 0 et 10 (voir TP1).

```C
void Remplissage(int tab[], int elemCount) {  
    for(int i = 0 ; i < elemCount ; i++)  
        tab[i] = rand()%10;  
}
```

### Écrire une fonction ``Affichage`` qui prend en arguments un tableau et sa taille et qui l’affiche.

```C
void Affichage(int tab[], int elemCount) {  
    for(int i = 0 ; i < elemCount ; i++)  
        printf("%d ", tab[i]);  
    printf("\n");  
}
```

### Écrire une fonction ``Position`` prenant un tableau en paramètre, sa longueur, ainsi qu’un entier e, et renvoyant la première position de l’entier e dans le tableau, ou −1 si e n’est pas présent.

```C
int Position(int tab[], int elemCount, int e) {  
    for(int i = 0 ; i < elemCount ; i++)  
        if(tab[i] == e) return i;  
    return -1;  
}
```

### Écrire une fonction ``Somme`` prenant en argument deux tableaux ``tabA`` et ``tabB`` (que l’on suppose de même taille), ainsi qu’un tableau ``resultat``, t.q. $∀i ∈ [0, N −1], resultat[i] = tabA[i] + tabB[i]$.


```C
void Somme(int tabA[], int tabB[], int resultat[], int elemCount) {  
    for(int i = 0 ; i < elemCount ; i++)  
        resultat[i] = tabA[i] + tabB[i];  
}
```


## Exercice 2 : Histogramme

Écrire une fonction ``Histogramme`` recevant deux tableaux ``notes`` et ``histo`` ainsi que la longueur du tableau notes. Ce dernier contient des notes entre 0 et 20 dans chaque case. Le tableau ``histo`` a pour taille 21 et représente, après appel à la fonction ``Histogramme``, l’histogramme du premier tableau, i.e. ``histo[i]`` donne le nombre de valeurs égales à ``i`` dans ``notes``. Vous devez utiliser une seule **boucle** pour remplir ``histo`` après son initialisation. Tester.

```C
void Histogramme(int notes[], int histo[], int notesElemCount) {  
  
    for(int i = 0 ; i < 21 ; i++) {  
        histo[i] = 0;  
    } 
    
    for(int i = 0 ; i < notesElemCount ; i++) {  
        histo[notes[i]]++;  
    }
}
```

> On a bien précisé "une seule boucle" **après l'initialisation du tableau**.
> 
## Exercice 3 : Eratosthène

```C
void eratosthene(int N) {  
  
    int lgTab = N-1;  
  
    int tab[lgTab];  

	// On remplit le tableau avec ses valeurs initiales
	
    for(int i = 0 ; i < lgTab ; i++) {  
       tab[i] = i+2;  
    }  

	// On commence par enlever tous les multiples du 0 (1er) élement du tableau.
    int i = 0;  
  
    while( (tab[i] * tab[i]) < lgTab) {

		// Pour tous les éléments du tableau supérieurs ou égal à i+1 (puisqu'on ne veut pas enlever i)
	    for(int j = i+1 ; j < lgTab ; j++) {

			// On vérifie que tab[j] est un multiple de tab[i]
		    if(tab[j] % tab[i] == 0) {  
                tab[j] = -1;  
	        }
        } 

        // On augmente au minimum de 1 la valeur de i (puisqu'on a déjà retiré tous ses multiples). Si on tombe sur un des multiples précédents, on continue d'avancer tant qu'on a pas rencontré une valeur valide.
        do {
	        i++;
        } while(tab[i] == -1);
 
    } 

	// On affiche le tableau.
    for(i = 0 ; i < lgTab ; i++) {  
        if(tab[i] != -1) printf("%d ", tab[i]);  
    }  
}
```

## Exercice 4 *[Bonus]* : Pascal

> J'ai eu la flemme de faire cet exo

## Exercice 5 *[Bonus]* : Somme à k et comparaisons

> J'ai eu la flemme de faire cet exo
