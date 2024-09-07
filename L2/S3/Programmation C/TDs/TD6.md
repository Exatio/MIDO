# TD6 - Allocation dynamique

## Exercice 1. Ensemble d'entiers

```C
#include <stdio.h>
#include <stdlib.h>

// 1.
typedef struct {
    int* tableau;
    int taille;
    int cardinal;
} Ensemble;

// 2.
Ensemble* creerEnsemble() {
    Ensemble* nouvelEnsemble = (Ensemble*) malloc(sizeof(Ensemble));
    nouvelEnsemble->tableau = (int*) malloc(5 * sizeof(int));
    nouvelEnsemble->taille = 5;
    nouvelEnsemble->cardinal = 0;
    return nouvelEnsemble;
}

// 3.
int estDansEnsemble(Ensemble* E, int x) {
    for (int i = 0; i < E->cardinal; ++i) {
        if (E->tableau[i] == x) {
            return 1;
        }
    }
    return 0;
}

// 4.
void ajouterElement(Ensemble* E, int x) {
    if (!estDansEnsemble(E, x)) {
        if (E->cardinal == E->taille) {
            E->taille *= 2;
            E->tableau = (int*) realloc(E->tableau, E->taille * sizeof(int));
        }
        E->tableau[E->cardinal++] = x;
    }
}

// 5.
void supprimerElement(Ensemble* E, int x) {
    for (int i = 0; i < E->cardinal; ++i) {
        if (E->tableau[i] == x) {
            for (int j = i; j < E->cardinal - 1; j++) {
                E->tableau[j] = E->tableau[j + 1];
            }
            E->cardinal--;
            return;
        }
    }
}

// 6.
void libererEnsemble(Ensemble* E) {
    free(E->tableau);
    free(E);
}

// 7.
Ensemble* unionEnsembles(Ensemble* X, Ensemble* Y) {
    Ensemble* Z = creerEnsemble();
    
    for (int i = 0; i < X->cardinal; ++i) {
        ajouterElement(Z, X->tableau[i]);
    }
    
    for (int i = 0; i < Y->cardinal; ++i) {
        ajouterElement(Z, Y->tableau[i]);
    }

    return Z;
}

// 8.
Ensemble* intersectionEnsembles(Ensemble* X, Ensemble* Y) {
    Ensemble* Z = creerEnsemble();
    
    for (int i = 0; i < X->cardinal; ++i) {
        if (estDansEnsemble(Y, X->tableau[i])) {
            ajouterElement(Z, X->tableau[i]);
        }
    }

    return Z;
}

int main() {

    Ensemble* ensemble1 = creerEnsemble();
    ajouterElement(ensemble1, 3);
    ajouterElement(ensemble1, 5);
    ajouterElement(ensemble1, 7);

    Ensemble* ensemble2 = creerEnsemble();
    ajouterElement(ensemble2, 5);
    ajouterElement(ensemble2, 8);

    Ensemble* unionEnsemble = unionEnsembles(ensemble1, ensemble2);
    Ensemble* intersectionEnsemble = intersectionEnsembles(ensemble1, ensemble2);

    printf("Union : ");
    for (int i = 0; i < unionEnsemble->cardinal; ++i) {
        printf("%d ", unionEnsemble->tableau[i]);
    }
    printf("\n");

    printf("Intersection : ");
    for (int i = 0; i < intersectionEnsemble->cardinal; ++i) {
        printf("%d ", intersectionEnsemble->tableau[i]);
    }
    printf("\n");

    libererEnsemble(ensemble1);
    libererEnsemble(ensemble2);
    libererEnsemble(unionEnsemble);
    libererEnsemble(intersectionEnsemble);

    return 0;
}
```

## Exercice 2. Tableau

```C
#include <stdio.h>
#include <stdlib.h>

// 1.
void generate(int** v, int* n) {
    printf("Saisir la taille du tableau : ");
    scanf("%d", n);

    *v = (int*) malloc(*n * sizeof(int));

    if (*v == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return;
    }

    for (int i = 0; i < *n; i++) {
        (*v)[i] = i * i;
    }
}

// 2.
void display(int* v, int n) {
    for (int i = n - 1; i >= 0; i--) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

// 3.
void free_mem(int** v) {
    free(*v);
    *v = NULL;
}

int main() {
    int* v = NULL; 
    int n; 

    generate(&v, &n);
    display(v, n);
    free_mem(&v);

    return 0;
}

```