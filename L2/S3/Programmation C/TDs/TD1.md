# TD1 : Révisions
## Exercice 1 : Comprendre un programme

```C
// Création de la fonction principale
int main() {
	// Affichage d'une chaîne de caractères
	printf("Je suis 1 programme C.\n");
	// Renvoi de 0 à la fonction principale : "Tout est OK."
	return 0;
}
```

```C
// Création de la fonction principale
int main() {
	// Initialisation d'une variable de type entier
	int nombre;
	// Affichage du nombre 7 dans une chaîne de caractères formatée
	printf("Voici un nombre : %d\n", 7);
	// Assignation de l'entier 20 à la variable nombre
	nombre = 20;
	// Affichage de l'expression évaluée (nombre+22) = 42 dans une chaîne de caractères formatée
	printf("En voici un autre : %d\n", nombre+22);
	// Renvoi de 0 à la fonction principale : "Tout est OK."
	return 0;
}
```

```C
// Création de la fonction principale
int main() {
	// Initialisation des variables i et j de type entier et assignation respective de 3 et 5 à i et j 
	int i = 3, j = 5;
	// Initialisation des variables x y et z de type flottant (nombre réel).
	float x, y, z;
	// Assignation du réel 3.0 à la variable x
	x = 3.0;
	// Affichage des variables i et j et du résultat de l'expression i+j dans une chaîne de caractères formatée
	printf("i=%d, j=%d, somme=%d\n", i, j, i+j);
	// Evaluation de j/2 en tant qu'entier : 2 puis assignation à j
	i = j/2;
	// Evaluation de x/2 : 1.5 puis assignation à y
	y = x/2;
	// Evaluation de j/2 en tant qu'entier car pas de float dans l'opération : 2 puis cast en float 2.00 puis assignation à z
	z = j/2;
	// Evaluation de j/2.0 en tant que float : 2.5 puis cast en entier car j est un int et assignation à j.
	j = j/2.0;
	// Affichage de la chaine de caractères formatée avec deux entiers (%d) et deux décimaux (%f)
	printf("i=%d\ny=%f z=%f j=%d\n", i, y, z, j);
	// Renvoi de 0 à la fonction principale : "Tout est OK."
	return 0;
}
```

## Exercice 2 : Affichages

Indiquer si les instructions suivantes provoquent des erreurs de compilation. Donner l'affichage de ce programme.

```C
#include <stdio.h>
int main() {
	int i, k;
	float x, y;
	char c, d;
	i = 48;
	printf("%c, %d\n", i, i);
	i = 304%256
	printf("%c, %d\n", i, i);
	c = 'a';
	printf("%c, %d\n", c, c);
	c++;
	printf("%c, %d\n", c, c);
	d = 'A';
	printf("%c, %d\n", d, d);
	k = 'd';
	printf("%c, %d\n", k, k);
	k = d;
	printf("%c, %d\n", k, k);
	y = 'a';
	x = 65;
	printf("%f, %f\n", y, x);
	return 0;
}
```
Il n'y aura pas d'erreur de compilation dans ce programme. 
L'affichage que produit ce programme est :
``` 
0, 48
0, 48
a, 97
b, 98
A, 65
d, 100
A, 65
97.000000, 65.000000
```

## Exercice 3 : Lecture au clavier

Ecrire un programme C qui demande à l'utilisateur de saisir un entier au clavier et qui l'affiche ensuite entre deux lignes vides. On se servira de l'instruction ``scanf("%d", &i);`` qui permet de saisir un entier et de le mettre dans la variable **i**.

```C
#include <stdio.h>
int main() {
	int i = 0;
	printf("Saisissez un entier svp : ");
	scanf("%d", &i);
	printf("Vous avez saisi :\n\n%d\n", i);
	return 0;
}
```

## Exercice 4 : En moyenne

Ecrire un programme qui demande à l'utilisateur de saisir une série d'entiers. Lorsque l'utilisateur entre le nombre 0 (qui ne fait pas partie de la série), le programme se termine après avoir affiché le nombre d'entiers saisis, leur moyenne, le plus petit entier entré et le plus grand.

```C
#include <stdio.h>
int main() {
	int entier_actuel;
	
	int nombre_entiers = 0;
	int somme_entiers = 0;

	scanf("%d", &entier_actuel);
	int plus_petit = entier_actuel;
	int plus_grand = entier_actuel;
	
	while(entier_actuel != 0) {
		if(entier_actuel < plus_petit) plus_petit = entier_actuel;
		if(entier_actuel > plus_grand) plus_grand = entier_actuel;
		nombre_entiers++;
		somme_entiers += entier_actuel;
		scanf("%d", &entier_actuel);
	}
	
	float moyenne = somme_entiers/((float) nombre_entiers);
	
	printf("Nombre d'entiers : %d\nPlus petit nombre tapé : %d\nPlus grand nombre tapé : %d\n", nombre_entiers, plus_petit, plus_grand);
	printf("Moyenne : %f\n", moyenne);
}
```

## Exercice 5 : Alphabet

Afficher tous les caractères compris entre 'a' et 'z' pour chacun leur code ASCII exprimé en décimal. Même chose pour les caractères compris entre 'A' et 'Z'. Pour répondre à cette exercice, il n'y a pas besoin de connaître le code ASCII de 'a'. Utiliser une fois une boucle while et une fois une boucle for.

```C
#include <stdio.h>
int main() {
	char current_char = 'a';
	while(current_char != 'z') {
		printf("%c, %d\n", current_char, current_char);
		current_char++;
	}
	printf("%c, %d\n", current_char, current_char);

	for(char current = 'A' ; current != 'Z'; current++) {
		printf("%c, %d\n", current, current);
	}
	printf("%c, %d\n", 'Z', 'Z');
	return 0;
}
```

## Exercice 6 : Décomposition

Ecrire un programme qui lit un entier au clavier et affiche chaque chiffre du nombre sur une ligne en commençant par le chiffre des unités.


```C
#include <stdio.h>
int main() {
	int x = 0;
	scanf("%d", &x);
	while(x) {
		printf("%d\n", x%10);
		x=x/10;
	}
	return 0;
}
```


## Exercice 6 : Décomposition ~ Variation

Ecrire un programme qui prend un nombre en argument de ligne de commande et affiche chaque chiffre du nombre sur une ligne en commençant par le chiffre des unités.


```C
#include <stdio.h>  
  
int printnums(char *str);  
  
int main(int argc, char *argv[]) {  
  
    if(argc != 2) {  
        printf("Argc is not 1 ! Exiting...");  
        return -6;  
    }  
    printnums( argv[1]);  
  
    return 0;  
}  
  
  
int printnums(char *str) {  
  
    char current;  
  
    int counter, i, final = 0;  
  
    for(counter = 0 ; str[counter] != '\0' ; counter++) {  
  
        current = str[counter];  
        printf("%c\n", current);  
  
        if (current >= 57 || current <= 48) {  
            return 0;  
        }
    }
      
    for(i = 0 ; i < counter ; i++) {  
        current = str[i];  
        final += (current-48) * 10^(counter-i);  
    }  
    
    return final;  
}
```



