# TP9 : Listes doublement chaînées 
## Exercice 1

```C
#include <stdio.h>  
#include <stdlib.h>  
  
// 1.  
typedef struct Maillon {  
    int val;  
    struct Maillon* prec;  
    struct Maillon* suiv;  
} Maillon;  
  
// 2.  
typedef struct Liste {  
    int taille;  
    Maillon* premier;  
    Maillon* dernier;  
} Liste;  
  
// 3.  
Maillon* creer_maillon(int valeur) {  
    Maillon* nouveau_maillon = (Maillon*) malloc(sizeof(Maillon));  
    if (nouveau_maillon != NULL) {  
        nouveau_maillon->val = valeur;  
        nouveau_maillon->prec = NULL;  
        nouveau_maillon->suiv = NULL;  
    }    return nouveau_maillon;  
}  
  
// 4.  
Liste* liste_init() {  
    Liste* nouvelle_liste = (Liste*) malloc(sizeof(Liste));  
    if (nouvelle_liste != NULL) {  
        nouvelle_liste->taille = 0;  
        nouvelle_liste->premier = NULL;  
        nouvelle_liste->dernier = NULL;  
    }    return nouvelle_liste;  
}  
  
// 5.  
void liste_ajout_debut(Liste* liste, int valeur) {  
    Maillon* nouveau_maillon = creer_maillon(valeur);  
    if (nouveau_maillon != NULL) {  
        if (liste->taille == 0) {  
            liste->premier = nouveau_maillon;  
            liste->dernier = nouveau_maillon;  
        } else {  
            nouveau_maillon->suiv = liste->premier;  
            liste->premier->prec = nouveau_maillon;  
            liste->premier = nouveau_maillon;  
        }        liste->taille++;  
    }}  
  
// 6.  
void liste_ajout_fin(Liste* liste, int valeur) {  
    Maillon* nouveau_maillon = creer_maillon(valeur);  
    if (nouveau_maillon != NULL) {  
        if (liste->taille == 0) {  
            liste->premier = nouveau_maillon;  
            liste->dernier = nouveau_maillon;  
        } else {  
            nouveau_maillon->prec = liste->dernier;  
            liste->dernier->suiv = nouveau_maillon;  
            liste->dernier = nouveau_maillon;  
        }        liste->taille++;  
    }}  
  
// 7.  
void liste_affiche(Liste* liste) {  
    Maillon* courant = liste->premier;  
    while (courant != NULL) {  
        printf("%d ", courant->val);  
        courant = courant->suiv;  
    }    printf("\n");  
}  
  
// 8.  
void liste_affiche_inverse_iteratif(Liste* liste) {  
    Maillon* courant = liste->dernier;  
    while (courant != NULL) {  
        printf("%d ", courant->val);  
        courant = courant->prec;  
    }    printf("\n");  
}  
  
void maillon_affiche_inverse_recursif(Maillon* maillon) {  
    if (maillon == NULL) {  
        return;  
    }  
    printf("%d ", maillon->val);  
    maillon_affiche_inverse_recursif(maillon->prec);  
}  
  
void liste_affiche_inverse_recursif(Liste* liste) {  
    maillon_affiche_inverse_recursif(liste->dernier);  
    printf("\n");  
}  
  
// 9.  
Maillon* liste_extraire_debut(Liste* liste) {  
    if (liste->taille == 0) {  
        return NULL;  
    }  
    Maillon* premier_maillon = liste->premier;  
  
    if (liste->taille == 1) {  
        liste->premier = NULL;  
        liste->dernier = NULL;  
    } else {  
        liste->premier = premier_maillon->suiv;  
        liste->premier->prec = NULL;  
    }  
    liste->taille--;  
    return premier_maillon;  
}  
  
// 10.  
Maillon* liste_extraire_fin(Liste* liste) {  
    if (liste->taille == 0) {  
        return NULL;  
    }  
    Maillon* dernier_maillon = liste->dernier;  
  
    if (liste->taille == 1) {  
        liste->premier = NULL;  
        liste->dernier = NULL;  
    } else {  
        liste->dernier = dernier_maillon->prec;  
        liste->dernier->suiv = NULL;  
    }  
    liste->taille--;  
    return dernier_maillon;  
}  
  
// 11.  
Maillon* liste_supprimer(Liste* liste, int valeur) {  
    Maillon* courant = liste->premier;  
  
    while (courant != NULL) {  
        if (courant->val == valeur) {  
            if (courant->prec == NULL) {  
                return liste_extraire_debut(liste);  
            } else if (courant->suiv == NULL) {  
                return liste_extraire_fin(liste);  
            } else {  
                courant->prec->suiv = courant->suiv;  
                courant->suiv->prec = courant->prec;  
                liste->taille--;  
                return courant;  
            }        }        courant = courant->suiv;  
    }  
    return NULL;  
}  
  
// 12.  
void liste_tourner_droite(Liste* liste) {  
    if (liste->taille <= 1) {  
        return;  
    }  
    Maillon* dernier_maillon = liste_extraire_fin(liste);  
    dernier_maillon->suiv = liste->premier;  
    dernier_maillon->prec = NULL;  
    liste->premier->prec = dernier_maillon;  
    liste->premier = dernier_maillon;  
    liste->taille++;  
}  
  
// 13.  
void liste_tourner_gauche(Liste* liste) {  
    if (liste->taille <= 1) {  
        return;  
    }  
    Maillon* premier_maillon = liste_extraire_debut(liste);  
    premier_maillon->prec = liste->dernier;  
    premier_maillon->suiv = NULL;  
    liste->dernier->suiv = premier_maillon;  
    liste->dernier = premier_maillon;  
    liste->taille++;  
}  
  
// 14.  
void liste_libere(Liste* liste) {  
    Maillon* courant = liste->premier;  
    while(courant != NULL) {  
        Maillon* maillon_a_supprimer = courant;  
        courant = courant->suiv;  
        free(maillon_a_supprimer);  
    }    free(liste);  
}  
  
int main() {  
  
    Liste* ma_liste = liste_init();  
  
    liste_ajout_debut(ma_liste, 3);  
    liste_ajout_debut(ma_liste, 2);  
    liste_ajout_debut(ma_liste, 1);  
  
    liste_affiche(ma_liste);  
  
    liste_ajout_fin(ma_liste, 4);  
    liste_ajout_fin(ma_liste, 5);  
  
    liste_affiche(ma_liste);  
    liste_affiche_inverse_iteratif(ma_liste);  
    liste_affiche_inverse_recursif(ma_liste);  
  
    free(liste_supprimer(ma_liste, 5));  
    liste_affiche(ma_liste);  
    
    liste_ajout_fin(ma_liste, 5);  
    liste_affiche(ma_liste);  
    
    liste_tourner_droite(ma_liste);  
    liste_affiche(ma_liste);  
    
    liste_tourner_gauche(ma_liste);  
    liste_affiche(ma_liste); 
     
    liste_libere(ma_liste);  
  
    return 0;  
}
```