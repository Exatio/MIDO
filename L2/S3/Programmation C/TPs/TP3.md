# TP3 : Chaînes de caractères

## Exercice 1 : Concaténation

Écrire une fonction recevant deux chaînes de caractères et recopiant la seconde à la suite de la première. Attention à vérifier qu’il y a assez d’espace dans le tableau recevant le résultat ! La fonction renvoie 0 s’il n’y avait pas assez de place et 1 sinon. Le tableau obtenu doit rester une chaîne de caractères. Utiliser le ``main``donné.

```C
#include <stdio.h>  
#define N 18  
  
char concat(char s1[], char s2[]) {  
    int lg1 = 0;  
    while(s1[lg1] != '\0') lg1++;  
    int lg2 = 0;  
    while(s2[lg2] != '\0') lg2++;  
  
    if(lg1+lg2 > N) return 0;  
  
    for(int i = 0 ; i < lg2 ; i++)  
       s1[i+lg1] = s2[i];  
  
    return 1;  
}  
  
int main() {  
    char s1[N] = "salut ";  
    char s2[N] = "c'est cool !";  
    printf("%s%s\n", s1, s2);  
    if(concat(s1, s2))  
       printf("%s\n", s1);  
    else  
       printf("Not enough space\n");  
    return 0;  
}
```

## Exercice 2 : Remplacer

```C
#include <stdio.h>  
  
int replace(char str[], char toReplace, char replacement)  
{  
    int replacements = 0;  
    for(int i = 0 ; str[i] != '\0' ; i++) {  
        if(str[i] == toReplace) {  
            str[i] = replacement;  
            replacements++;  
        }  
    }  
    return replacements;  
}  
  
int main() {  
    char str[] = "Jabababa";  
    int i = replace(str, 'a', 'o');  
    printf("%s, %d", str, i);  
    return 0;  
}
```


## Exercice 3 : César

```C
#include <stdio.h>  
  
void cesar(char str[], int d)  
{  
	d = d%26;
    for(int i = 0 ; str[i] != '\0' ; i++) {  
        if(str[i] <= 'Z' - d) {  
            str[i] += d;  
        } else {  
            str[i] = 'A' - 1 + d - 'Z' + str[i] ;  
        }  
    }  
}  
  
void inverseCesar(char str[], int d) {  
    cesar(str, 26 - d%26);  
}  
  
int main() {  
    char str[] = "XYLOPHONE";  
    cesar(str, 2);  
    printf("%s\n", str);  
    inverseCesar(str, 2);  
    printf("%s\n", str);  
    return 0;  
}
```

## Exercice 4 : Anagramme

```C
#include <stdio.h>  
  
short anagramme(char str1[], char str2[]) {  
    int ascii[256];  
  
    for(int i = 0 ; i < 256 ; i++) {  
        ascii[i] = 0;  
    }  
  
    for(int i = 0 ; str1[i] != '\0' ; i++) {  
        ascii[str1[i]] += 1;  
    }  
  
    for(int i = 0 ; str2[i] != '\0' ; i++) {  
        ascii[str1[i]] -= 1;  
    }  
  
    for(int i = 0 ; i < 256 ; i++) {  
        if(ascii[i] != 0) return 0;  
    }  
  
    return 1;  
}  
  
int main() {  
    char str[] = "TSARINE";  
    char str2[] = "ENTRAIS";  
    printf("%d\n", anagramme(str, str2));  
    return 0;  
}
```

## Exercice 5 : Occurrence joker 

```C
#include <stdio.h>  
  
int occurenceJoker(char str[], char str2[]) {  
    for(int i = 0 ; str[i] != '\0' ; i++) {  
        for(int j = 0 ; str2[j] != '\0' ; j++) {  
            if(str[i] == str2[j]) return i;  
        }  
    }  
    return -1;  
}  
  
int main() {  
    char str[] = "bonjour";  
    char str2[] = "zaf";  
    printf("%d\n", occurenceJoker(str, str2));  
    return 0;  
}
```


## Exercice 6 : Grep

```C
#include <stdio.h>  
  
int grep(char str[], char str2[]) {  
    for(int i = 0 ; str[i] != '\0' ; i++) {  
        for(int j = 0 ; str2[j] != '\0' ; j++) {  
            if(str[i] == str2[j]) {  
                int allEquals = 1;  
                for(int k = 0 ; str2[k] != '\0' ; k++) {  
                    if(str[i+k] != str2[k]) {  
                        allEquals = 0;  
                        break;  
                    }  
                }  
                if(allEquals) return i;  
            }  
        }  
    }  
    return -1;  
}  
  
int main() {  
    char str[] = "bonzafjour";  
    char str2[] = "zaf";  
    printf("%d\n", grep(str, str2));  
    return 0;  
}
```

