# TD3 : Chaînes de caractères et tableaux à deux dimensions

## Exercice 1. La taille compte

```C
int LgChaine(char ch1[]) {
	int lg = 0;
	for(int i = 0 ; ch1[i] != '\0' ; i++) lg++;
	return lg;
}
```

## Exercice 2. Comparaison

```C
int CompareChaines(char char1[], char char2[]) {  
    int i = 0;  
    while(char1[i] != '\0' && char2[i] != '\0') {  
        if(char1[i] != char2[i]) return char2[i] - char1[i];  
        i++;  
    }    if(char1[i] == '\0' && char2[i] == '\0') return 0;  
    else if(char1[i] == '\0') return -char2[i];  
    else return char1[i];  
}
```

## Exercice 3. Majuscules

```C
void Majuscules(char ch[]) {  
    for(int i = 0 ; ch[i] != '\0' ; i++) if(ch[i] >= 'a') ch[i] -= 'a' - 'A';  
}
```

## Exercice 4. Palindromes

### Écrire une fonction ``void Copie(char ch1[],char ch2[])`` qui copie le contenu de la chaîne ``ch1`` dans la chaîne ``ch2`` ; on considère qu’une place mémoire suffisante a été réservée pour ``ch2``.

```C
void Copie(char ch1[], char ch2[]) {
	for(int i = 0 ; ch1[i] != '\0' ; i++) ch2[i] = ch1[i];
}
```

### Écrire une fonction ``void Miroir(char ch[])`` qui inverse les caractères de la chaîne ``ch``, sans utiliser de tableau temporaire. Par exemple, la fonction transformera *trace* en *ecart*.

```C
void Miroir(char ch[]) {  
    int i = 0;  
    while(ch[i] != '\0') i++;  
    for(int j = 0 ; j < i/2 ; j++) {  
        char temp = ch[j];  
        ch[j] = ch[i-1-j];  
        ch[i-1-j] = temp;  
    }}
```


### Écrire une fonction ``void SupprOccur(char ch[], char c)`` qui supprime les occurrences de ``c`` dans ``ch``, sans utiliser de tableau annexe et sans boucle imbriquée.

```C
void SupprOccur(char ch[], char c) {  
    int i, j;  
  
    for (i = 0, j = 0; ch[i] != '\0'; i++) {  
        if (ch[i] != c) {  
            ch[j] = ch[i];  
            j++;  
        }
    }  
    ch[j] = '\0';  
}
```

### En déduire une fonction ``int EstPalindrome(char ch[])`` qui renvoie 1 si ``ch`` est un palindrome, 0 sinon.

```C
int EstPalindrome(char ch[]) {  
    SupprOccur(ch, ' ');  
    SupprOccur(ch, '.');  
    SupprOccur(ch, '?');  
    SupprOccur(ch, '!');  
    SupprOccur(ch, ',');  
  
    int lgChaine = 0;  
    while(ch[lgChaine] != '\0') lgChaine++;  
  
    char ch2[lgChaine];  
    for(int i = 0 ; ch[i] != '\0' ; i++) {  
        ch2[i] = ch[i];  
    }  
    Miroir(ch2);  
  
    for(int i = 0 ; ch[i] != '\0' ; i++) {  
        if(ch[i] != ch2[i]) return 0;  
    }  
    return 1;  
}
```

## Exercice 5. Table de multiplication

### Écrire une fonction ``RemplirTableauMult()`` qui prend en argument un tableau d’entiers à 2 dimensions ``tab`` et remplit ligne par ligne la table de multiplication de 1 à 10.

```C
void RemplirTableauMult(int tab[][10]) {  
    for(int i = 0 ; i < 10 ; i++)  
        for (int j = 0; j < 10; j++)  
            tab[i][j] = (i+1) * (j+1);  
}
```

> Une meilleure solution existe, mais il faut utiliser les pointeurs qui n'ont pas encore été vus en classe.

### Écrire une fonction qui l’affiche

```C
void AfficheTableau() {  
    int tab[10][10];  
    RemplirTableauMult(tab);
    for(int i = 0 ; i < 10 ; i++) {  
        for (int j = 0; j < 10; j++)  
            printf("%d ", tab[i][j]);  
        printf("\n");
	}
}
```

## Exercice 6. Tableaux de caractères à 2 dimensions

### Écrire une fonction ``CreerDamier()`` qui prend en argument un tableau de caractères à deux dimensions ``tab`` et un entier ``n`` où ``n ∗ n`` est la taille effective du tableau. Cette fonction modifie ``tab`` de sorte à modéliser un damier : les cases blanches sont codées par le caractère ``-`` et les cases noires par le caractère ``*``. La case d’indice (0, 0) est blanche.

```C
void CreerDamier(char tab[][10], int n) {
	for(int i = 0 ; i < n ; i++) {
		for(int j = 0 ; j < n ; j++) {
			if((i+j)%2 == 0) tab[i][j] = '-';
			else tab[i][j] = '*'; 
		}	
	}
}
```


### Écrire une fonction ``CreerCroix()`` qui prend en argument un tableau de caractères à deux dimensions, un entier ``n`` où ``n∗n`` est la taille effective du tableau et deux entiers ``i`` et ``j``. Cette fonction modifie tab de ``sorte`` que l’élément d’indice (i, j) de ``tab`` soit remplacé par le caractère ``*``. De plus, les deux diagonales qui passent par cet élément doivent contenir des ``+`` et il doit y avoir des ``.`` partout ailleurs dans le tableau.

```C
void CreerCroix(char tab[][7], int n, int i0, int j0) {  
    for(int i = 0 ; i < n ; i++) {  
        for(int j = 0 ; j < n ; j++) {  
            if(i==i0 && j==j0) tab[i][j] = '*';  
            else if(i0-i == j0-j || i0-i == j-j0 || i-i0 == j0-j || i-i0 == j-j0) tab[i][j] = '+';  
            else tab[i][j] = '.';  
        }
    }
}
```

