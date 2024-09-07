# TD8 - Liste chaînée triée

## Exercice 1.

```C
#include <stdio.h>  
#include <stdlib.h>  
  
struct Maillon {  
    int valeur;  
    struct Maillon* suivant;  
};  
  
struct Liste {  
	// omission volontaire de la taille psk c osef dans l'exercice
    struct Maillon* premier;  
};  
  
// 1.  
struct Maillon* RechercheTrie(struct Liste* L, int valeur) {  
    struct Maillon* courant = L->premier;  
    while (courant != NULL && courant->valeur != valeur) {  
        courant = courant->suivant;  
    }  
    return courant;  
}  
  
// 2.  
int EgaleTrie(struct Liste* un, struct Liste* deux) {  
    struct Maillon* courantUn = un->premier;  
    struct Maillon* courantDeux = deux->premier;  
  
    while (courantUn != NULL && courantDeux != NULL) {  
        if (courantUn->valeur != courantDeux->valeur) {  
            return 0;  
        }  
        courantUn = courantUn->suivant;  
        courantDeux = courantDeux->suivant;  
    }  
    return (courantUn == NULL && courantDeux == NULL);  
}  
  
// 3.  
void SupprimerDoublons(struct Liste* liste) {  
    struct Maillon* courant = liste->premier;  
  
    while (courant->suivant != NULL) {  
        if (courant->valeur == courant->suivant->valeur) {  
            struct Maillon* maillonASupprimer = courant->suivant;  
            courant->suivant = courant->suivant->suivant;  
            free(maillonASupprimer);  
        } else {  
            courant = courant->suivant;  
        }    
    }
}  
  
// 4.  
void InsertionTrie(struct Liste* liste, int valeur) {  
    struct Maillon* nouveauMaillon = (struct Maillon*) malloc(sizeof(struct Maillon));  
    nouveauMaillon->valeur = valeur;  
  
    if (liste->premier == NULL || valeur < liste->premier->valeur) {  
        nouveauMaillon->suivant = liste->premier;  
        liste->premier = nouveauMaillon;  
    } else {  
        struct Maillon* courant = liste->premier;  
        while (courant->suivant != NULL && valeur > courant->suivant->valeur) {  
            courant = courant->suivant;  
        }  
        nouveauMaillon->suivant = courant->suivant;  
        courant->suivant = nouveauMaillon;  
    }
}  
  
// 5.  
struct Maillon* EnleverElement(struct Liste* liste, int valeur) {  
    struct Maillon* maillonASupprimer = NULL;  
  
    if (liste->premier != NULL && liste->premier->valeur == valeur) {  
  
        maillonASupprimer = liste->premier;  
        liste->premier = liste->premier->suivant;  
    } else {  
  
        struct Maillon* courant = liste->premier;  
        while (courant->suivant != NULL && courant->suivant->valeur != valeur) {  
            courant = courant->suivant;  
        }  
        if (courant->suivant != NULL) {  
            maillonASupprimer = courant->suivant;  
            courant->suivant = courant->suivant->suivant;  
        }
    }  
    return maillonASupprimer;  
}  
  
// 6. A  
struct Liste* FusionnerListes(struct Liste* Un, struct Liste* Deux) {  
    struct Liste* resultat = (struct Liste*)malloc(sizeof(struct Liste));  
    resultat->premier = NULL;  
  
    struct Maillon* courantUn = Un->premier;  
    struct Maillon* courantDeux = Deux->premier;  
    struct Maillon* courantResultat = NULL;  
  
    while (courantUn != NULL && courantDeux != NULL) {  
        struct Maillon* nouveauMaillon = (struct Maillon*) malloc(sizeof(struct Maillon));  
  
        if (courantUn->valeur < courantDeux->valeur) {  
            nouveauMaillon->valeur = courantUn->valeur;  
            courantUn = courantUn->suivant;  
        } else {  
            nouveauMaillon->valeur = courantDeux->valeur;  
            courantDeux = courantDeux->suivant;  
        }  
        nouveauMaillon->suivant = NULL;  
  
        if (courantResultat == NULL) {  
            resultat->premier = nouveauMaillon;  
            courantResultat = nouveauMaillon;  
        } else {  
            courantResultat->suivant = nouveauMaillon;  
            courantResultat = nouveauMaillon;  
        }    
        
    }  
 
    while (courantUn != NULL) {  
        struct Maillon* nouveauMaillon = (struct Maillon*)malloc(sizeof(struct Maillon));  
        nouveauMaillon->valeur = courantUn->valeur;  
        nouveauMaillon->suivant = NULL;  
  
        if (courantResultat == NULL) {  
            resultat->premier = nouveauMaillon;  
            courantResultat = nouveauMaillon;  
        } else {  
            courantResultat->suivant = nouveauMaillon;  
            courantResultat = nouveauMaillon;  
        }  
        courantUn = courantUn->suivant;  
    }  

    while (courantDeux != NULL) {  
        struct Maillon* nouveauMaillon = (struct Maillon*)malloc(sizeof(struct Maillon));  
        nouveauMaillon->valeur = courantDeux->valeur;  
        nouveauMaillon->suivant = NULL;  
  
        if (courantResultat == NULL) {  
            resultat->premier = nouveauMaillon;  
            courantResultat = nouveauMaillon;  
        } else {  
            courantResultat->suivant = nouveauMaillon;  
            courantResultat = nouveauMaillon;  
        }  
        courantDeux = courantDeux->suivant;  
    }  
    return resultat;  
}  
  
// Eviter les fuites de mémoire  
void DetruireListe(struct Liste* liste) {  
    struct Maillon* courant = liste->premier;  
    while (courant != NULL) {  
        struct Maillon* maillonASupprimer = courant;  
        courant = courant->suivant;  
        free(maillonASupprimer);  
    }  
    free(liste);  
}  
  
int main() {  
    struct Liste* liste = (struct Liste*) malloc(sizeof(struct Liste));  
    liste->premier = NULL;  
  
    InsertionTrie(liste, 5);  
    InsertionTrie(liste, 2);  
    InsertionTrie(liste, 10);  
    InsertionTrie(liste, 8);  
    InsertionTrie(liste, 2);  
    InsertionTrie(liste, 10);  
  
    struct Maillon* courant = liste->premier;  
    while (courant != NULL) {  
        printf("%d ", courant->valeur);  
        courant = courant->suivant;  
    }    printf("\n");  
  
    struct Maillon* resultatRecherche = RechercheTrie(liste, 8);  
    if (resultatRecherche != NULL) {  
        printf("Element 8 trouve dans la liste.\n");  
    } else {  
        printf("Element 8 non trouve dans la liste.\n");  
    }  
    free(EnleverElement(liste, 8));  
  
    resultatRecherche = RechercheTrie(liste, 8);  
    if (resultatRecherche != NULL) {  
        printf("Element 8 trouve dans la liste.\n");  
    } else {  
        printf("Element 8 non trouve dans la liste.\n");  
    }  
    SupprimerDoublons(liste);  
  
    courant = liste->premier;  
    while (courant != NULL) {  
        printf("%d ", courant->valeur);  
        courant = courant->suivant;  
    }    printf("\n");  
  
    struct Liste* listeUn = (struct Liste*)malloc(sizeof(struct Liste));  
    listeUn->premier = NULL;  
    InsertionTrie(listeUn, 2);  
    InsertionTrie(listeUn, 5);  
    InsertionTrie(listeUn, 7);  
  
    struct Liste* listeDeux = (struct Liste*)malloc(sizeof(struct Liste));  
    listeDeux->premier = NULL;  
    InsertionTrie(listeDeux, 3);  
    InsertionTrie(listeDeux, 6);  
    InsertionTrie(listeDeux, 8);  
  
    struct Liste* resultatFusion = FusionnerListes(listeUn, listeDeux);  
  
    courant = resultatFusion->premier;  
    while (courant != NULL) {  
        printf("%d ", courant->valeur);  
        courant = courant->suivant;  
    }    printf("\n");  
  
  
    DetruireListe(liste);  
    DetruireListe(listeUn);  
    DetruireListe(listeDeux);  
    DetruireListe(resultatFusion);  
  
    return 0;  
}
```
