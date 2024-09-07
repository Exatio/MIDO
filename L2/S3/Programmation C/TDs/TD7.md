# TD7 - Listes chaînées

## Exercice 1. Liste chaînée

```C
#include <stdio.h>
#include <stdlib.h>

// 1.
struct Maillon {
    int valeur;
    struct Maillon* suivant;
};

// 2.
struct Liste {
    int taille;
    struct Maillon* premier;
};

// 3.
struct Liste* creerListe() {
    struct Liste* nouvelleListe = (struct Liste*) malloc(sizeof(struct Liste));
    nouvelleListe->taille = 0;
    nouvelleListe->premier = NULL;
    return nouvelleListe;
}

// 4.
void ajoutDebut(struct Liste* liste, int valeur) {
    struct Maillon* nouveauMaillon = (struct Maillon*) malloc(sizeof(struct Maillon));
    nouveauMaillon->valeur = valeur;
    nouveauMaillon->suivant = liste->premier;
    liste->premier = nouveauMaillon;
    liste->taille++;
}

// 5.
void afficherListe(struct Liste* liste) {
    struct Maillon* courant = liste->premier;
    while (courant != NULL) {
        printf("%d ", courant->valeur);
        courant = courant->suivant;
    }
    printf("\n");
}

// 6.
void ajoutFin(struct Liste* liste, int valeur) {
    struct Maillon* nouveauMaillon = (struct Maillon*)malloc(sizeof(struct Maillon));
    nouveauMaillon->valeur = valeur;
    nouveauMaillon->suivant = NULL;

    if (liste->premier == NULL) {
        liste->premier = nouveauMaillon;
    } else {
        struct Maillon* courant = liste->premier;
        while (courant->suivant != NULL) {
            courant = courant->suivant;
        }
        courant->suivant = nouveauMaillon;
    }

    liste->taille++;
}

// 7.
int rechercheElement(struct Liste* liste, int valeur) {
    struct Maillon* courant = liste->premier;
    while (courant != NULL) {
        if (courant->valeur == valeur) {
            return 1;
        }
        courant = courant->suivant;
    }
    return 0;
}

// 8.
void afficherListeRecursive(struct Maillon* maillon) {
    if (maillon != NULL) {
        printf("%d ", maillon->valeur);
        afficherListeRecursive(maillon->suivant);
    }
}

// 9.
struct Maillon* popPremier(struct Liste* liste) {
    if (liste->premier == NULL) {
        return NULL; // Liste vide
    }

    struct Maillon* premierMaillon = liste->premier;
    liste->premier = premierMaillon->suivant;
    premierMaillon->suivant = NULL;
    liste->taille--;

    return premierMaillon;
}

// 10.
void detruireListe(struct Liste* liste) {
    while (liste->premier != NULL) {
        struct Maillon* maillonASupprimer = popPremier(liste);
        free(maillonASupprimer);
    }
    free(liste);
}

// 11.
void supprimerOccurrences(struct Liste* liste, int valeur) {
    struct Maillon* courant = liste->premier;
    struct Maillon* precedent = NULL;

    while (courant != NULL) {
        if (courant->valeur == valeur) {
            if (precedent == NULL) {
                liste->premier = courant->suivant;
            } else {
                precedent->suivant = courant->suivant;
            }

            struct Maillon* maillonASupprimer = courant;
            free(maillonASupprimer);
            liste->taille--;
        } else {
            precedent = courant;
        }
        courant = courant->suivant;
    }
}

int main() {
    // Exemple d'utilisation
    struct Liste* maListe = creerListe();

    ajoutDebut(maListe, 3);
    ajoutDebut(maListe, 2);
    ajoutDebut(maListe, 1);

    ajoutFin(maListe, 4);
    ajoutFin(maListe, 5);

    afficherListe(maListe);

    printf("Recherche de l'élément 3 : %d\n", rechercheElement(maListe, 3));
    printf("Recherche de l'élément 7 : %d\n", rechercheElement(maListe, 7));

    printf("Affichage récursif : ");
    afficherListeRecursive(maListe->premier);
    printf("\n");

    struct Maillon* premierMaillon = popPremier(maListe);
    printf("Premier maillon retiré : %d\n", premierMaillon->valeur);
    free(premierMaillon);

    afficherListe(maListe);

    supprimerOccurrences(maListe, 4);
    printf("Liste après suppression des occurrences de 4 : ");
    afficherListe(maListe);

    detruireListe(maListe);

    return 0;
}

```


## Exercice 2 : File pile

``file.h``

```C
#ifndef FILE_H
#define FILE_H

#include "liste.h"

struct File {
    struct Liste* liste;
};

struct File* FileInitialiser();
int FileVide(struct File* file);
int FileLongueur(struct File* file);
void Enfiler(struct File* file, int valeur);
int Defiler(struct File* file);
void FileDetruire(struct File* file);

#endif

```

``file.c``

```C
#include "file.h"
#include <stdlib.h>

struct File* FileInitialiser() {
    struct File* nouvelleFile = (struct File*)malloc(sizeof(struct File));
    nouvelleFile->liste = creerListe();
    return nouvelleFile;
}

int FileVide(struct File* file) {
    return file->liste->taille == 0;
}

int FileLongueur(struct File* file) {
    return file->liste->taille;
}

void Enfiler(struct File* file, int valeur) {
    ajoutFin(file->liste, valeur);
}

int Defiler(struct File* file) {
    if (FileVide(file)) {
        // Gestion d'erreur, la file est vide
        return -1;
    }

    struct Maillon* premierMaillon = popPremier(file->liste);
    int valeur = premierMaillon->valeur;
    free(premierMaillon);

    return valeur;
}

void FileDetruire(struct File* file) {
    detruireListe(file->liste);
    free(file);
}
```

``pile.h``

```C
#ifndef PILE_H
#define PILE_H

#include "liste.h"

struct Pile {
    struct Liste* liste;
};

struct Pile* PileInitialiser();
int PileVide(struct Pile* pile);
int PileHauteur(struct Pile* pile);
void Empiler(struct Pile* pile, int valeur);
int Depiler(struct Pile* pile);
void PileDetruire(struct Pile* pile);

#endif

```

``pile.c``

```C
#include "pile.h"
#include <stdlib.h>

struct Pile* PileInitialiser() {
    struct Pile* nouvellePile = (struct Pile*)malloc(sizeof(struct Pile));
    nouvellePile->liste = creerListe();
    return nouvellePile;
}

int PileVide(struct Pile* pile) {
    return pile->liste->taille == 0;
}

int PileHauteur(struct Pile* pile) {
    return pile->liste->taille;
}

void Empiler(struct Pile* pile, int valeur) {
    ajoutDebut(pile->liste, valeur);
}

int Depiler(struct Pile* pile) {
    if (PileVide(pile)) {
        // Gestion d'erreur, la pile est vide
        return -1;
    }

    struct Maillon* premierMaillon = popPremier(pile->liste);
    int valeur = premierMaillon->valeur;
    free(premierMaillon);

    return valeur;
}

void PileDetruire(struct Pile* pile) {
    detruireListe(pile->liste);
    free(pile);
}
```
