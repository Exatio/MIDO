# TD4 : Pointeurs

## Exercice 1 : Echange

```C
#include <stdio.h>

// Echange classique par une variable temporaire. Cependant, a et b étant des variables locales à la fonction ech1, elles n'ont aucune incidence sur les a et b du main.
void ech1(int a, int b) {
	int tmp = a;
	a = b;
	b = tmp;
}


// On met la valeur déréférencée du pointeur a (càd la valeur contenue dans l'adresse mémoire stockée par a) dans tmp.
// Ensuite, on assigne à la valeur déréférencée du pointeur a par la valeur déréférencée du pointeur b.
// Ensuite, on assigne à la valeur déréférencée du pointeur b la valeur contenue dans tmp.
// Ici, on a bien modifié les valeurs contenues dans l'adresse mémoire stockée dans les pointeurs a et b, c'est-à-dire qu'on a modifié les a et b originaux (ceux transmis dans la fonction en paramètres)
void ech2(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// La même chose que ech2, mais a n'est modifié que localement donc seulement la valeur de b est modifiée en dehors de la fonction.
void ech3(int a, int* b) {
	int tmp = a;
	a = *b;
	*b = tmp;
}

int main() {
	int a = 1, b = 2;
	ech1(a, b);
	printf("a=%d b=%d\n", a, b);
	ech2(&a, &b);
	printf("a=%d b=%d\n", a, b);
	ech3(a, &b);
	printf("a=%d b=%d\n", a, b);
	return 0;
}
```

Ce programme affiche :
```
a=1 b=2
a=2 b=1
a=2 b=2
```

## Exercice 2  :  Quelle heure est-il ?

### Ecrire une fonction ``timeCutting()`` prenant un nombre de minutes en argument et permettant à la fonction appelant ``timeCutting()`` d’obtenir le nombre d’heures et de minutes correspondant. Par exemple, si on l’appelle avec 30, on doit avoir 0 heure et 30 minutes, et si on l’appelle avec 90, on doit avoir 1 heure et 30 minutes. Pour cela, réfléchir à un moyen pour qu’une fonction puisse transmettre plus d’une valeur à la partie du programme qui l’appelle.

```C
#include <stdio.h>  
  
void timeCutting(int *minutes, int *hours) {  
    int minute = (*minutes)% 60;  
    *hours = (*minutes - minute) / 60;  
    *minutes = minute;  
}  
  
int main() {  
    int minutes = 187;  
    int hours;  
    timeCutting(&minutes, &hours);  
    printf("%d heure(s) %d minute(s)", hours, minutes);  
    return 0;  
}
```

### Ecrire une fonction ``main()`` qui demande à l’utilisateur de saisir un nombre de minutes puis affiche le nombre d’heures et de minutes correspondant déterminé à l’aide de ``timeCutting()``.

```C
int main() {  
    int minutes;  
    int hours;  
    printf("Saissez le nombre de minutes : ");  
    scanf("%d", &minutes);  
    timeCutting(&minutes, &hours);  
    printf("%d heure(s) %d minute(s)", hours, minutes);  
    return 0;  
}
```
## Exercice 3 : MinMax

Écrire une fonction qui passe à la partie du programme qui l’appelle la valeur minimum et la valeur maximum d’une suite de n entiers saisis par l’utilisateur (on demande alors dans un premier temps de saisir ce n)

```C
int main() {
	int n;
	printf("Saisissez n : ");
	scanf("%d", &n);
}
```
> g rien compris a l'exo

## Exercice 4 : Déréférencement

```C
int var = 10; // variable var = 10, emplacement mémoire = m1  
int var2 = var; // variable var2 = 10, emplacement mémoire = m2  
int* p = &var; // pointeur p = m1, emplacement mémoire = m3  
*p = 20; // déréférencenement de p : on modifie la valeur contenue dans l'adresse mémoire contenue par p. Donc, on modifie la valeur de m1, donc var = 20  
  
printf("%d %d %d %d\n", var, var2, p, *p);  
// Affichage de: valeur de var, valeur de var2, valeur de p (emplacement mémoire de var), valeur déréférencée de p (valeur de var)  
  
int* p2; // déclaration du pointeur p2  
*p2 = 15; // valeur de p2 : 15  
printf("%d\n", *p2); // On affiche la valeur de l'emplacement mémoire contenue par p2. Càd qu'on affiche la valeur de l'emplacement mémoire 15 (qui est aléatoire)
```

> Pour p2, on essaie d'accéder à la valeur de l'emplacement mémoire non géré par le programme, donc soit on aura une valeur aléatoire soit un crash.

## Exercice 5 : Pointeurs et tableau

Soient le tableau ``t`` suivant et le pointeur ``p`` pointant sur ``t``.

```C
int t[] = {3, 8, 12, 78, 43, 90, 177, 64};
int* p = t;
```

Un tableau est un pointeur vers le premier élément de ce dernier.
Donc
- t est un pointeur vers le premier élément du tableau (il contient l'adresse mémoire contenant t[0] en tant que valeur).
- p représente l'adresse mémoire du premier élément de t. 
- \*p représente la valeur contenue dans l'adresse mémoire contenue dans le pointeur vers le premier élément de t, c'est-à-dire t.
- \*p + 2 représente donc la valeur du premier élément de p à laquelle on ajoute 2 (5)
- \*(p+2) représente la valeur contenue dans le pointeur vers le 3ème élément de t, c'est-à-dire 12.
- t + 3 représente l'adresse mémoire du premier élément de t à laquelle on ajoute 3 adresses mémoires, chaque adresse mémoire faisant 4 octets (on manipule des int dans ce tableau), il s'agira donc concrètement de la valeur de t + 12.

## Exercice 6 : Pointeurs et tableau 2

```C
int tab[3]; // On initialise un tableau de taille 3
int* p; // On crée un pointeur p vers un entier
p = tab; // p pointe vers le premier élément du tableau
p = tab+2; // puisque tab est un tableau d'entiers prenant 4 octets chacun, tab+2 concrètement vaut l'adresse mémoire de tab à laquelle on ajoute 8 adresses mémoires donc on pointe vers le 3eme élément de tab.
tab[1] = 5; // le 2 ème élément du tableau devient 5
p[-1] = 6; // Le 2 ème élément du tableau devient 6
tab = p; // ERREUR; ne compile pas : on ne peut pas changer l'adresse mémoire d'une variable
```

## Exercice 7.

Donner les valeurs de `a`, `b`, `c`, `p1` et `p2` après exécution de chacune des instruction suivantes.

```C
int a = 1, b = 2, c = 3; // a vaut 1, b vaut 2, c vaut 3.
int* p1 = &a; // p1 pointe vers la variable a.
int* p2 = &c; // p2 pointe vers la variable c
*p1 = (*p2)++; // on fait d'abord *p1 = *p2 puis *p2 = *p2 + 1. D'où a = 3, c = 4
p1 = p2; // p1 pointe désormais vers la variable c
p2 = &b; // p2 pointe désormais vers la variable b
*p1 -= *p2; // c = c - b d'où c = 2
++*p2; // b = b+1 d'où b = 3
*p1 *= *p2; // c = c * b d'où c = 6
a = ++*p2**p1 // voir ci-dessous
```

On décompose ``a = ++*p2**p1`` : ``a = ++*p2 * *p1``
C'est-à-dire d'abord ``b = b+1`` d'où ``b = 4``
Ensuite `` a = b * c`` d'où ``a = 24``

> Un point important de cet exercice est de comprendre le fonctionnement de `++`.
> Si jamais il se trouve avant une variable (`a = ++b`), alors on fera d'abord l'incrémentation ensuite le reste (assignation). Donc `b = b+1` puis `a = b` 
> Si jamais il se trouve après une variable (`a = b++`), alors on fera d'abord le reste (assignation), et ensuite l'incrémentation. Donc `a = b` puis `b = b+1`
> On voit bien que dans les deux cas `a` n'a pas la même valeur.

