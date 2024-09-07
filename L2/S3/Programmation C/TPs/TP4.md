# TP4 : Récursivité

## Exercice 1. Croissons

```C
#include <stdio.h>

void croissRec(int a) {
	if (a == 0) {
		return;
	} else {
		croissRec(a-1);
		printf("%d\n", a);
	}
}
```

1. Si on l'appelle avec un entier positif, cette fonction affiche tous les entiers de 1 à a (compris).
2. Il suffit d'afficher avant de passer au nombre précédent :

```C
#include <stdio.h>

void decroissRec(int a) {
	if (a == 0) {
		return;
	} else {
		printf("%d\n", a);
		decroissRec(a-1);
	}
}
```
## Exercice 2. Factorielle

### 1. Écrire une fonction prenant un entier a et retournant a! de manière itérative

```C
int factIterative(int a) {  
    int factorielle = 1;  
    for(int i = 2 ; i <= a ; i++) {  
        factorielle *= i;  
    }    return factorielle;  
}
```

### 2. Écrire une fonction calculant cette même factorielle mais de manière récursive, sachant que $0! = 1$ et $n! = n · (n − 1)!$.

```C
int factRec(int a) {  
  
    if(a == 0) {  
        return 1;  
    } else {  
        return a * factRec(a-1);  
    }  
}
```



## Exercice 3. PGCD

### 1. Calculer à la main $PGCD(142,12)$

C'est 2

###  2. Que se passe t-il si on applique l’algorithme aux entiers 12 et 142 ? (et plus généralement si $a < b$ ?).

Si $a < b$, alors $PGCD(a, b) = PGCD(b, r)$ avec $a = 0\times b + r$ d'où $r = a$.
Alors, à la première application de l'algorithme, on transforme $PGCD(a, b)$ en $PGCD(b, a)$, donc tout fonctionne correctement. 

### 3. Écrire une fonction récursive calculant le PGCD de deux entiers $a$ et $b$. On suppose que l’un de ces deux entiers est non nul.

```C
int pgcd(int a, int b) { 
	if (b == 0) { 
		return a; 
	} else { 
		return pgcd(b, a % b); 
	} 
}
```

## Exercice 4. La puissance (du C)

### 1. Écrire une fonction prenant un entier $a$ et un entier strictement positif $n$ et qui renvoie $a^n$ de manière itérative.

```C
int puissanceIterative(int a, int n) {  
    int resultat = 1;  
    for(int i = 0 ; i < n ; i++) {  
        resultat *= a;  
    }    
    return resultat;  
}
```

### 2. Écrire une fonction récursive calculant cette même puissance. Tester

```C
int puissanceRecursive(int a, int n) {  
    if(n == 0) {  
        return 1;  
    } else {  
        return puissanceRecursive(a, n-1) * a;  
    }
}
```

### 3. À l’aide d’un pointeur, calculer le nombre d’appels à la fonction récursive (faire l’affichage du compteur après le calcul de la fonction).

```C
#include <stdio.h>

int puissanceRecursive(int a, int n, int* nbAppels) {  
    *nbAppels += 1;  
    if(n == 0) {  
        return 1;  
    } else {  
        return puissanceRecursive(a, n-1, nbAppels) * a;  
    }
}  
  
  
int main() {  
    int nbAppels = 0;  
    printf("%d\n",puissanceRecursive(5, 3, &nbAppels));  
    printf("%d appels", nbAppels);  
}
```

### 4. Sachant que $a^0 = 1$, $a^n = (a^2 )^{n/2}$ si n est pair et $a^n = a·(a^2)^{(n−1)/2}$ si n est impair, écrire une fonction récursive **maligne** calculant cette même puissance. Tester, et comparer le nombre d’appels effectués à la fonction récursive (cette fonction étant maligne, elle doit utiliser moins d’appels que la fonction précédente).

```C
int puissanceRecursiveMaligne(int a, int n, int* nbAppels) {  
    *nbAppels += 1;  
    if(n == 0) {  
        return 1;  
    } else {  
        if(n%2 == 0) {  
            return puissanceRecursiveMaligne(a*a, n/2, nbAppels);  
        } else {  
            return puissanceRecursiveMaligne(a*a, (n-1)/2, nbAppels) * a;  
        }
    }
}
```

On voit que pour calculer $10^{10}$ on passe de 11 à 5 appels de la fonction récursive.


## Exercice 5. Fibo

### Écrire une fonction récursive qui calcule le $n$-ème nombre de Fibonacci. À l’aide d’un pointeur, vérifier que le nombre d’appels à la fonction récursive est bien $2\times F_{n+1} − 1$.

```C
#include <stdio.h>  
  
int fibonacci(int n, int* nbAppels) {  
    (*nbAppels)++;  
  
    if (n <= 0) {  
        return 0;  
    } else if (n == 1) {  
        return 1;  
    } else {  
        return fibonacci(n - 1, nbAppels) + fibonacci(n - 2, nbAppels);  
    }}  
  
  
int main() {  
    int nbAppels = 0;  
    int n = 10;  
    printf("%d\n",fibonacci(n, &nbAppels));  
    printf("%d appels\n", nbAppels);  
    printf("nombre d'appels supposes : %d\n", 2 * fibonacci(n+1, &nbAppels) - 1);  
}
```

> A noter: dans le code main, la valeur de nbAppels est incorrecte à la fin car on l'a réutilisée 2 fois.

### Écrire une fonction itérative qui calcule le $n$-ème nombre de Fibonacci. Combien y a t-il de passages dans la boucle ?

```C
#include <stdio.h>  
  
int fibonacciRec(int n) {  
    int nbAppels = 0;  
  
    int fnMoins2 = 0;  
    int fnMoins1 = 1;  
    int fn = 1;  
    for(int i = 2 ; i <= n ; i++) {  
        fn = fnMoins1 + fnMoins2;  
        fnMoins2 = fnMoins1;  
        fnMoins1 = fn;  
        nbAppels++;  
    }    printf("%d\n", nbAppels);  
    return fn;  
  
}  
  
  
int main() {  
    printf("%d\n",fibonacciRec(10));  
}
```

Il y a $n-1$ passages dans la boucle.
## Exercice 6. Palindrome

*Écrire une fonction récursive renvoyant $1$ si la chaîne prise en argument est un palindrome et $0$ sinon (on pourrait supposer que la chaîne ne contient pas d’espaces et est en minuscules). Tester avec ``kayak`` et ``kiwi`` par exemple.*

```C
#include <stdio.h>  
  
int estPalindrome(char chaine[], int n) {  
    if(n == 1) {  
        printf("verifie %c\n", chaine[0]);  
        return 1;  
    } else if (n == 2) {  
        printf("verifie %c et %c\n", chaine[0], chaine[1]);  
        return chaine[0] == chaine[1];  
    } else {  
        printf("renvoie palindrome de \"%s\" avec n = %d\n", chaine+1, n-2);  
        return estPalindrome(chaine+1, n-2);  
    }    return 0;  
}  
  
  
int main() {  
    char chaine[] = "kayak";  
    int n = 0;  
    while(chaine[n] != '\0') n++; // Calculer longueur de la chaîne  
    printf("%d\n", estPalindrome(chaine, n));  
}
```

> Ceci est ma réponse initiale mais je n'aime pas trop la façon de faire de celle-ci (avec les pointeurs). Je trouve celle ci-dessous plus jolie.

```C
#include <stdio.h>  
#include <string.h>  
  
int estPalindrome(char *chaine, int debut, int fin) {  
    if (debut >= fin) {  
        return 1;  
    }  
    if (chaine[debut] != chaine[fin]) {  
        return 0;  
    }  
    return estPalindrome(chaine, debut + 1, fin - 1);  
}  
  
int main() {  
    char chaine[] = "kayak";  
    int n = 0;  
    while(chaine[n] != '\0') n++;  
    printf("%d\n", estPalindrome(chaine, 0, n - 1));  
    return 0;  
}
```