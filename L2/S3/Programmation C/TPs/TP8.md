# TP8 - Listes chaînées

## Exercice 1. Opérations de base

> L'affichage peut surprendre mais quand on ajoute un maillon ne pas oublier qu'il est ajouté en tête de liste.

```C
#include <stdio.h>  
#include <stdlib.h>  
  
typedef struct maillon {  
    int val;  
    struct maillon* suiv;  
} Maillon;  
  
typedef struct {  
    Maillon* premier;  
} Liste;  
  
// 1.  
Maillon* creer_maillon(int valeur) {  
    Maillon* nouveau_maillon = (Maillon*) malloc(sizeof(Maillon));  
    if (nouveau_maillon != NULL) {  
        nouveau_maillon->val = valeur;  
        nouveau_maillon->suiv = NULL;  
    }    return nouveau_maillon;  
}  
  
// 2.  
Liste* liste_init() {  
    Liste* nouvelle_liste = (Liste*) malloc(sizeof(Liste));  
    if (nouvelle_liste != NULL) {  
        nouvelle_liste->premier = NULL;  
    }    return nouvelle_liste;  
}  
  
//3.  
void liste_ajout_debut(Liste* liste, int valeur) {  
    Maillon* nouveau_maillon = creer_maillon(valeur);  
    if (nouveau_maillon != NULL) {  
        nouveau_maillon->suiv = liste->premier;  
        liste->premier = nouveau_maillon;  
    }
}  
  
// 4.  
void liste_saisie(Liste* liste) {  
    int nombre_maillons, valeur;  
    printf("Entrez le nombre de maillons : ");  
    scanf("%d", &nombre_maillons);  
  
    for (int i = 0; i < nombre_maillons; ++i) {  
        printf("Entrez la valeur du maillon %d : ", i + 1);  
        scanf("%d", &valeur);  
        liste_ajout_debut(liste, valeur);  
    }
}  
  
// 5. Optionnel  
  
// 6.  
void liste_affiche_it(Liste* liste) {  
    Maillon* courant = liste->premier;  
    while (courant != NULL) {  
        printf("%d ", courant->val);  
        courant = courant->suiv;  
    }    printf("\n");  
}  
  
// 7. Optionnel  
  
// 8.  
void maillon_affiche_rec(Maillon* maillon) {  
    if (maillon != NULL) {  
        printf("%d ", maillon->val);  
        maillon_affiche_rec(maillon->suiv);  
    }
}  
  
void liste_affiche_rec(Liste* liste) {  
    maillon_affiche_rec(liste->premier);  
    printf("\n");  
}  
  
// 9.  
void maillon_affiche_inv(Maillon* maillon) {  
    if (maillon != NULL) {  
        maillon_affiche_inv(maillon->suiv);  
        printf("%d ", maillon->val);  
    }
}  
  
void liste_affiche_inv(Liste* liste) {  
    maillon_affiche_inv(liste->premier);  
    printf("\n");  
}  
  
int main() {  
    Liste* ma_liste = liste_init();  
    if (ma_liste == NULL) {  
        printf("Erreur lors de l'initialisation de la liste.\n");  
        return 1;  
    }  
    liste_saisie(ma_liste);  
  
    printf("Liste affichée de manière itérative : ");  
    liste_affiche_it(ma_liste);  
  
    printf("Liste affichée de manière récursive : ");  
    liste_affiche_rec(ma_liste);  
  
    printf("Liste affichée de manière inversée récursive : ");  
    liste_affiche_inv(ma_liste);  
  
    Maillon* courant = ma_liste->premier;  
    while (courant != NULL) {  
        Maillon* suivant = courant->suiv;  
        free(courant);  
        courant = suivant;  
    }   
    free(ma_liste);  
  
    return 0;  
}

```

## Exercice 2. Recherches

```C
// Définitions des fonctions et structures de l'exo 1

// 1.  
Maillon* liste_recherche(Liste* liste, int valeur) {  
    Maillon* courant = liste->premier;  
    while (courant != NULL) {  
        if (courant->val == valeur) {  
            return courant;  
        }        courant = courant->suiv;  
    }    return NULL;  
}  
  
// 2.  
Maillon* liste_min(Liste* liste) {  
    if (liste->premier == NULL) {  
        return NULL; // Liste vide  
    }  
  
    Maillon* min_maillon = liste->premier;  
    Maillon* courant = liste->premier->suiv;  
  
    while (courant != NULL) {  
        if (courant->val < min_maillon->val) {  
            min_maillon = courant;  
        }        courant = courant->suiv;  
    }  
    return min_maillon;  
}  
  
// 3.  
Maillon* liste_dernier(Liste* liste) {  
    if (liste->premier == NULL) {  
        return NULL; // Liste vide  
    }  
  
    Maillon* courant = liste->premier;  
    while (courant->suiv != NULL) {  
        courant = courant->suiv;  
    }  
    return courant;  
}  
  
int main() {  
    Liste* ma_liste = liste_init();  
    if (ma_liste == NULL) {  
        printf("Erreur lors de l'initialisation de la liste.\n");  
        return 1;  
    }  
    liste_ajout_debut(ma_liste, 10);  
    liste_ajout_debut(ma_liste, 5);  
    liste_ajout_debut(ma_liste, 8);  
  
    int valeur_recherche = 5;  
    Maillon* maillon_recherche = liste_recherche(ma_liste, valeur_recherche);  
  
    if (maillon_recherche != NULL) {  
        printf("La valeur %d a été trouvée dans la liste.\n", valeur_recherche);  
    } else {  
        printf("La valeur %d n'a pas été trouvée dans la liste.\n", valeur_recherche);  
    }  
    Maillon* min_maillon = liste_min(ma_liste);  
    if (min_maillon != NULL) {  
        printf("La valeur minimale dans la liste est : %d\n", min_maillon->val);  
    } else {  
        printf("La liste est vide.\n");  
    }  
    Maillon* dernier_maillon = liste_dernier(ma_liste);  
    if (dernier_maillon != NULL) {  
        printf("La valeur du dernier maillon dans la liste est : %d\n", dernier_maillon->val);  
    } else {  
        printf("La liste est vide.\n");  
    }  

	Maillon* courant = ma_liste->premier;  
    while (courant != NULL) {  
        Maillon* suivant = courant->suiv;  
        free(courant);  
        courant = suivant;  
    }   
    free(ma_liste);  
    
    return 0;  
}
```
## Exercice 3. Insertion

```C
// 1.  
void liste_insere_fin(Liste* liste, int valeur) {  
    Maillon* nouveau_maillon = creer_maillon(valeur);  
    if (nouveau_maillon != NULL) {  
        if (liste->premier == NULL) {  
            liste->premier = nouveau_maillon;  
        } else {  
            (liste_dernier(liste))->suiv = nouveau_maillon;  
        }    }}  
  
// 2.  
void liste_insere_apres(Liste* liste, int valeur, int apres) {  
    Maillon* courant = liste->premier;  
    while (courant != NULL) {  
        if (courant->val == apres) {  
            Maillon* nouveau_maillon = creer_maillon(valeur);  
            if (nouveau_maillon != NULL) {  
                nouveau_maillon->suiv = courant->suiv;  
                courant->suiv = nouveau_maillon;  
            }            break;  
        }        courant = courant->suiv;  
    }}  
  
int main() {  
    Liste* ma_liste = liste_init();  
    if (ma_liste == NULL) {  
        printf("Erreur lors de l'initialisation de la liste.\n");  
        return 1;  
    }  
    liste_ajout_debut(ma_liste, 10);  
    liste_ajout_debut(ma_liste, 5);  
    liste_ajout_debut(ma_liste, 8);  
    liste_affiche_it(ma_liste); // 8 5 10  
  
    liste_insere_apres(ma_liste, 7, 5);  
    liste_affiche_it(ma_liste); // 8 5 7 10  
  
    liste_insere_fin(ma_liste, 40);  
    liste_affiche_it(ma_liste); // 8 5 7 10 40  
  
    Maillon* courant = ma_liste->premier;  
    while (courant != NULL) {  
        Maillon* suivant = courant->suiv;  
        free(courant);  
        courant = suivant;  
    }    free(ma_liste);  
  
    return 0;  
}
```
## Exercice 4. Concaténation

```C
// 1.
void liste_concatenation(Liste* liste1, Liste* liste2) {  
    Maillon * dernier = liste_dernier(liste1);  
    if(dernier != NULL) {  
        dernier->suiv = liste2->premier;  
    } else {  
        liste1->premier = liste2->premier;  
    }   
}  
  
int main() {  
    Liste* ma_liste = liste_init();  
    if (ma_liste == NULL) {  
        printf("Erreur lors de l'initialisation de la liste.\n");  
        return 1;  
    }  
    liste_ajout_debut(ma_liste, 10);  
    liste_ajout_debut(ma_liste, 5);  
    liste_ajout_debut(ma_liste, 8);  
  
    liste_affiche_it(ma_liste);  
  
    Liste* ma_liste_2 = liste_init();  
    if (ma_liste_2 == NULL) {  
        printf("Erreur lors de l'initialisation de la liste.\n");  
        return 1;  
    }  
    liste_ajout_debut(ma_liste_2, 5);  
    liste_ajout_debut(ma_liste_2, 4);  
    liste_ajout_debut(ma_liste_2, 3);  
  
    liste_affiche_it(ma_liste_2);  
  
    liste_concatenation(ma_liste, ma_liste_2);  

    liste_affiche_it(ma_liste);  
  
    Maillon* courant = ma_liste->premier;  
    while (courant != NULL) {  
        Maillon* suivant = courant->suiv;  
        free(courant);  
        courant = suivant;  
    }
    
	free(ma_liste_2);
    free(ma_liste);  
	
    return 0;  
}
```
## Exercice 5. Suppressions

> Pour le seuil, c'est un inférieur ou égal

```C
// 1.  
void libere_liste(Liste* liste) {  
    Maillon* courant = liste->premier;  
    while (courant != NULL) {  
        Maillon* suivant = courant->suiv;  
        free(courant);  
        courant = suivant;  
    }    free(liste);  
}  
  
// 2.  
void liste_suppr(Liste* liste, int valeur) {  
    Maillon* courant = liste->premier;  
    Maillon* precedent = NULL;  
  
    while (courant != NULL && courant->val != valeur) {  
        precedent = courant;  
        courant = courant->suiv;  
    }  
    if (courant != NULL) {  
        if (precedent != NULL) {  
            precedent->suiv = courant->suiv;  
        } else {  
            liste->premier = courant->suiv;  
        }
        free(courant);  
    }
}  
  
// 3.  
void liste_suppr_inf(Liste* liste, int seuil) {  
    Maillon* courant = liste->premier;  
    Maillon* precedent = NULL;  
  
    while (courant != NULL) {  
        if (courant->val <= seuil) {  
            if (precedent != NULL) {  
                precedent->suiv = courant->suiv;  
                free(courant);  
                courant = precedent->suiv;  
            } else {  
                liste->premier = courant->suiv;  
                free(courant);  
                courant = liste->premier;  
            }        } else {  
            precedent = courant;  
            courant = courant->suiv;  
        }    }}  
  
int main() {  
    Liste* ma_liste = liste_init();  
    if (ma_liste == NULL) {  
        printf("Erreur lors de l'initialisation de la liste.\n");  
        return 1;  
    }  
    liste_ajout_debut(ma_liste, 10);  
    liste_ajout_debut(ma_liste, 5);  
    liste_ajout_debut(ma_liste, 8);  
    liste_ajout_debut(ma_liste, 5);  
    liste_ajout_debut(ma_liste, 12);  
  
    liste_affiche_it(ma_liste);  
  
    liste_suppr(ma_liste, 5);  
    liste_affiche_it(ma_liste);  
  
    liste_suppr_inf(ma_liste, 10);  
    liste_affiche_it(ma_liste);  
  
    libere_liste(ma_liste);  
  
    return 0;  
}
```