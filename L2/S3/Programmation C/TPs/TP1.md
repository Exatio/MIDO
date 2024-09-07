# TP1 : Premiers pas
## Exercice 1 : - de 18

Écrire un programme qui demande l’âge de l’utilisateur, puis qui affiche MINEUR ou MAJEUR selon sa réponse.

```C
#include <stdio.h>  
  
int main() {  
    int age = 0;  
  
    printf("Merci d'entrer votre âge : ");  
    scanf("%d", &age);  
  
    if(age >= 18) {  
        printf("MAJEUR");  
    } else {  
        printf("MINEUR");  
    }  
    return 0;  
}
```

## Exercice 2 : Debugage

L’équipe C a écrit une solution pour l’exercice calculant les solutions d’une équation du second degré. Malheureusement le programme ne fonctionne pas ! Vous allez devoir le corriger et le faire fonctionner. 

```C
#include <stdio.h>  
#include <stdlib.h>  
#include <math.h>  
  
  
int main() {  
    double a, b, c;  
    double x = 0, x1 = 0, x2 = 0;  
    printf("a ?");  
    scanf("%lf", &a);  
    printf("b ?");  
    scanf("%lf", &b);  
    printf("c ?");  
    scanf("%lf", &c);
  
    double delta = b*b - 4*a*c;  
  
    if (delta < 0)  
        printf("Il n'y a pas de solutions reelles.\n");  
    else if (delta == 0) {  
        x = -b / (2 * a);  
        printf("Solution double : %f\n", x);  
    } else {  
        printf("%lf %lf %lf", b, -b, sqrt(delta));  
        x1 = (-b + sqrt(delta)) / (2 * a);  
        x2 = (-b - sqrt(delta)) / (2 * a);  
        printf("Deux solutions : %f et %f\n", x1, x2);  
    }  
    return 0;
}
```

> Je ne suis pas sûr de l'ordre des réponses ici, j'ai juste corrigé le programme par rapport à ce que je voyais.

1. ``4ac`` ne veut rien dire, il faut remplacer par ``4*a*c`` 
   
2. Ligne 17 : ``else if ((delta = 0)) {`` 
   On n'effectue pas une comparaison ici mais une assignation qui renvoie toujours 0 (c'est-à-dire le correspondant du booléen ``false``).
   Pour faire une comparaison, on remplacer par ``else if (delta == 0) {``
   
3. La fonction racine carrée (``sqrt``) n'est pas importée, pour cela il faut importer le fichier d'en-tête ``math.h``
   
4. Ce n'est pas le résultat voulu : Le fait que l'on ``scanf`` en mode ``%d`` au lieu de ``%lf`` cause la valeur de c de ne pas être correcte. 
   
5. Il s'affiche quand même car il n'y a pas les accolades qui encadrent le bloc du else.
   
6. Le résultat attendu est 1 et 3; pourtant le code n'est pas fonctionnel car on doit remplacer les 2\*a par des (2\*a) pour que la division soit correcte.
   Le programme fonctionnait plus tôt car a était égal à 1 donc la multiplication ou division n'avait aucun effet. J'aurais probablement pensé à ce problème avant de le tester.



## Exercice 3 : Comptage

Écrire un programme qui demande à l’utilisateur le nombre d’entiers qu’il désire saisir, puis compte le nombre d’entiers positifs, négatifs ou nuls entrés par l’utilisateur. Ne pas utiliser de tableau.

```C
#include <stdio.h>  
  
int main() {  
  
    int nb = 0, pos=0, neg=0, nuls=0;  
  
    printf("Combien d'entiers souhaitez-vous entrer au total ? ");  
    scanf("%d", &nb);  
  
    for(int i = 0 ; i < nb ; i++) {  
        int current = 0;  
        printf("Entrez chiffre %d : ", i+1);  
        scanf("%d", &current);  
  
        if(current > 0) pos++;  
        else if(current == 0)  nuls++;  
        else neg++;  
    }  
    printf("Nombres positifs : %d\nNégatifs : %d\nNuls : %d", pos, neg, nuls);  
    return 0;  
}
```

## Exercice 4 : Akinator

Écrire un programme qui demande à l’utilisateur de trouver un nombre entre 0 et 100. Ce programme indique à chaque étape si la valeur saisie est inférieure ou supérieure au nombre secret. L’utilisateur doit trouver en au plus 10 essais. S’il gagne, le programme doit l’informer du nombre de coups qui ont été nécessaires.

```C
#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>  
  
int main() {  
  
    srand(time(NULL));  
    int guess = rand()%100;  
  
    printf("AKINATOR ! BIENVENUE DANS LE JEU SPECIAL ! Devinez le chiffre aléatoire !\n");  
  
    int userGuess = guess+1, counter=0;  
  
    do {  
  
        if(counter != 0) {  
            if(userGuess > guess) printf("Trop grand\n");  
            else printf("Trop petit\n");  
        }  
        printf("Nouveau choix : ");  
        scanf("%d", &userGuess);  
  
        counter++;  
    } while(userGuess != guess);  
  
    printf("Gagné ! En seulement %d coups !", counter);  
  
    return 0;  
}
```

## Exercice 5 : Rectangles

```C
#include <stdio.h>  

int main() {  
  
    int hauteur, largeur;  
  
    printf("Saissez hauteur : ");  
    scanf("%d", &hauteur);  
    printf("Saissez largeur : ");  
    scanf("%d", &largeur);  
  
    printf("\n\n");  
  
    // VERSION "PLEINE"  
    for(int i = 0 ; i < hauteur; i++) {  
        for(int j = 0 ; j < largeur ; j++) {  
            printf("*");  
        }        printf("\n");  
    }  
    printf("\n\n");  
  
    // VERSION "CREUSE"  
    for(int i = 0 ; i < hauteur; i++) {  
        for(int j = 0 ; j < largeur ; j++) {  
            if(i==0 || j == 0 || i == hauteur-1 || j == largeur-1) printf("*");  
            else printf(" ");  
        } 
        
        printf("\n");  
    }  
    return 0;  
}
```

## Exercice 6 : Nombre parfait

### Écrire un programme déterminant si un entier entré par l’utilisateur est parfait.

```C
#include <stdio.h>  
  
int main() {  
  
    int nb;  
    printf("Ecrivez un nombre : ");  
    scanf("%d", &nb);  
  
    int sommeDiviseur = 0;  
  
    for(int i = 1 ; i < nb/2 + 1 ; i++) {  
        if(nb%i == 0) sommeDiviseur += i;  
    }  
    printf("%d\n", sommeDiviseur);  
    if(sommeDiviseur == nb) printf("Parfait !");  
    else printf("Pas parfait!");  
  
    return 0;  
}
```

### En déduire un programme qui affiche les nombres parfaits inférieurs à n, et un autre affichant les n premiers nombres parfaits.

1. Plus petit que n :
   
```C
#include <stdio.h>  
  
int verifierParfait(int nb);  
  
int main() {  
  
    int n;  
    printf("n = ");  
    scanf("%d", &n);  
  
    for(int i = 1 ; i < n ; i++) {  
        if(verifierParfait(i)) printf("%d ", i);  
    }  
    return 0;  
}  
  
int verifierParfait(int nb)  
{  
    int sommeDiviseur = 0;  
  
    for(int i = 1 ; i < nb/2 + 1 ; i++) {  
        if(nb%i == 0) sommeDiviseur += i;  
    }  
    if(sommeDiviseur == nb) return 1;  
    return 0;  
}
```

2. Les n premiers

```C
#include <stdio.h>  
  
int verifierParfait(int nb);  
  
int main() {  
  
    int n, count = 0;  
    printf("n = ");  
    scanf("%d", &n);  
  
    for(int i = 1 ; count != n ; i++) {  
        if(verifierParfait(i)) {  
            printf("%d ", i);  
            count++;  
        }            
    }
    
    return 0;  
}  
  
int verifierParfait(int nb)  
{  
    int sommeDiviseur = 0;  
  
    for(int i = 1 ; i < nb/2 + 1 ; i++) {  
        if(nb%i == 0) sommeDiviseur += i;  
    }  
    if(sommeDiviseur == nb) return 1;  
    return 0;  
}
```

## Exercice 7 : Gare aux flottants

### Afficher le résultat de l’opération 1.2e18 + 55.55

Il s'agit de ``1200000000000000000.000000``

### Essayer de deviner le résultat du programme suivant :

```C
#include <stdio.h>  
int main() {  
    float f = 0.0;  
    int i;  
  
    for(i = 0 ; i < 10 ; i++)  
        f += 0.1;  
  
    if(f == 1.0)  
        printf("f egal a 1.0\n");  
    else  
        printf("f different de 1.0\n");  
  
    printf("%.12f, %.12f\n", f, 1.);  
    return 0;  
}
```

On s'attend à ce qu'après avoir ajouté 0.1 10 fois à 0, on atteigne 1.0 mais en réalité lorsqu'on ajoute 0.1 on n'ajoute pas une valeur exacte (car pas représentable en binaire).
Ainsi, 0.1 + 0.1 + ... 10 fois n'est pas égal à 1.0


## Exercice 8 :  Gare aux entiers aussi

```C
#include <stdio.h>  
#include <limits.h>  
  
int main() {  
  
    int n = INT_MAX;  
    printf("n vaut : %d\n", n);  
    n++;  
    printf("n + 1 vaut : %d\n", n);  
    return 0;  
}

```

1. ``INT_MAX`` représente l'entier le plus grand représentable en binaire dans le type ``int``.
   Si on y ajoute un (en binaire), puisque l'on travaille en complément à 2, on se retrouve à ``(-INT_MAX-1)``, c'est-à-dire le plus petit entier représentable dans les négatifs.
   
2. Ci-dessous

```C
#include <stdio.h> 

int main() {

	unsigned i = 1, j = -1;
	printf("i = %u, j = %u", i, j);
	return 0;
	
}
```
   
   On obtient ici les résultats suivants : 
   - i = 1 (comme attendu)
   - j = 4294967295 (qui correspond au plus grand entier non signé représentable)
     
   Ce comportement peut être expliqué par la représentation en complément à 2 des entiers en binaire.

3. On pourrait s'attendre à ce que le code affiche les 10 premiers entiers naturels, mais en réalité, puisque i est de type ``unsigned int``, lorsque i sera égal à 0 et qu'on lui enlèvera 1, on passera à -1 qui, en représentation complémentaire à 2 est également égal à j (selon le type - signé ou non) de la question précédente. En l'occurrence, il prendra la valeur de j puisque dans un type ``unsigned``. Donc i sera toujours positif, et on vient de former une **boucle infinie**.
   
```C
#include <stdio.h>  
  
int main() {   
    for (unsigned int i = 10 ; i >= 0 ;i--)  
        printf("%u\n", i);  
    return 0;  
}
```

4. Ci-dessous

```C
#include <stdio.h>  
#include <limits.h>  
  
int main() {  
  
    printf("Pour les int, on a :\nMin = %d\nMax = %d\n\n", INT_MIN, INT_MAX);  
    printf("Pour les unsigned int, on a :\nMin = %u\nMax = %u\n\n", 0, UINT_MAX);  
    printf("Pour les long, on a :\nMin = %ld\nMax = %ld\n\n", LONG_MIN, LONG_MAX);  
  
    return 0;  
  
}
```

 
 
 
 
 La sortie console est : 

```
Pour les int, on a :
Min = -2147483648
Max = 2147483647

Pour les unsigned int, on a :
Min = 0
Max = 4294967295

Pour les long, on a :
Min = -2147483648
Max = 2147483647

```

> On remarque par ailleurs que si au lieu de %u on avait utilisé %d pour représenter UINT_MAX, le programme aurait affiché -1 !


## Exercice 9 *[bonus]* : Mini Calculette

Voici ma soumission pour cet exercice :

```C
#include <stdio.h>  
  
int main() {  
  
    int operande1, operande2;  
    char operateur;  
    double resultat;  
  
    // Demander à l'utilisateur d'entrer l'opération  
    printf("Entrez une opération...\n");  
    scanf("%d %c %d", &operande1, &operateur, &operande2);  
  
    switch(operateur) {  
  
        case '+':  
            resultat = operande1 + operande2;  
            break;  
  
        case '-':  
            resultat = operande1 - operande2;  
            break;  
  
        case '*':  
            resultat = operande1 * operande2;  
            break;  
  
        case '/':  
            if(operande2 == 0) {  
                printf("Erreur: division par zéro");  
                return -5;  
            }            resultat = ((double) operande1)/ operande2;  
            break;  
  
        default:  
            printf("Les seules opérations valides sont + - * et /. Merci de réessayer.");  
            return -2;  
    } 
    
    printf("Résultat : %lf", resultat);  
  
  
    return 0;  
  
}
```

> Les return -2 et -5 sont des valeurs arbitraires que j'ai choisies au hasard. En règle générale, lorsqu'un programme ne s'effectue pas comme prévu et qu'on est forcé de l'arrêter, on l'arrête avec une valeur spécifiquement choisie pour représenter le type d'erreur, pour pouvoir, si quelqu'un utilise notre programme et voit que celui-ci a crash et return par exemple -2, savoir que l'erreur vient d'un opérateur invalide.

## Exercice 10 *[bonus]* : Puissances de 5

> J'ai eu la flemme de faire celui-là
