# TP6 - Structures

## Exercice 1. Complexes

```C
#include <stdio.h>

// 1.
typedef struct {
    float reel;
    float imaginaire;
} Complexe;

// 2.
void saisirComplexe(Complexe *c) {
    printf("Saisir la partie réelle : ");
    scanf("%f", &(c->reel));
    printf("Saisir la partie imaginaire : ");
    scanf("%f", &(c->imaginaire));
} 
// ne marche pas avec const car le mot-clé garantit que les valeurs ne seront pas modifiées

// 3.
void afficherComplexe(const Complexe *c) {
    printf("%f + %fi\n", c->reel, c->imaginaire);
}

// 4.
int sontEgaux(const Complexe *c1, const Complexe *c2) {
    return (c1->reel == c2->reel) && (c1->imaginaire == c2->imaginaire);
}

// 5.
Complexe sommeComplexe(const Complexe *c1, const Complexe *c2) {
    Complexe resultat;
    resultat.reel = c1->reel + c2->reel;
    resultat.imaginaire = c1->imaginaire + c2->imaginaire;
    return resultat;
}

// 6.
int main() {
    Complexe complexe1, complexe2, somme;
    
    printf("Saisie du premier complexe :\n");
    saisirComplexe(&complexe1);

    printf("\nSaisie du deuxième complexe :\n");
    saisirComplexe(&complexe2);

    printf("\nAffichage du premier complexe : ");
    afficherComplexe(&complexe1);

    printf("Affichage du deuxième complexe : ");
    afficherComplexe(&complexe2);

    if (sontEgaux(&complexe1, &complexe2)) {
        printf("\nLes deux complexes sont égaux.\n");
    } else {
        printf("\nLes deux complexes ne sont pas égaux.\n");
    }

    somme = sommeComplexe(&complexe1, &complexe2);
    printf("\nLa somme des deux complexes est : ");
    afficherComplexe(&somme);

    return 0;
}
```
## Exercice 2. Tableau de complexes

```C
#include <stdio.h>

typedef struct {
    float reel;
    float imaginaire;
} Complexe;

// 1.
typedef struct {
    Complexe table[100]; // Taille maximale définie par une constante (100 ici)
    int cardinalite;
} EnsembleComplexes;

// 2.
void saisirComplexe(Complexe *c) {
    printf("Saisir la partie réelle : ");
    scanf("%f", &(c->reel));
    printf("Saisir la partie imaginaire : ");
    scanf("%f", &(c->imaginaire));
}

void saisirEnsemble(EnsembleComplexes *ensemble) {
    printf("Saisir le nombre de complexes dans l'ensemble : ");
    scanf("%d", &(ensemble->cardinalite));

    for (int i = 0; i < ensemble->cardinalite; ++i) {
        printf("Saisir le complexe %d :\n", i + 1);
        saisirComplexe(&(ensemble->table[i]));
    }
}

// 3.
void afficherComplexe(const Complexe *c) {
    printf("%.2f + %.2fi\n", c->reel, c->imaginaire);
}

void afficherEnsemble(const EnsembleComplexes *ensemble) {
    printf("Ensemble de complexes :\n");

    for (int i = 0; i < ensemble->cardinalite; ++i) {
        printf("Complexe %d : ", i + 1);
        afficherComplexe(&(ensemble->table[i]));
    }
}

// 4.
int main() {
    EnsembleComplexes ensemble;

    saisirEnsemble(&ensemble);
    afficherEnsemble(&ensemble);

    return 0;
}

```
## Exercice 3. Jeu des 7 erreurs

```C
// Dans tout l'exercice on a augmenté le nombre d'éléments du tableau de 10 à 50  
// pour éviter les dépassements de tableau (strncpy, strcpy)
  
#include <stdio.h> // erreur 1 : <stdoi.h> -> <stdio.h>  
#include <string.h> // erreur 2 : ajout de <string.h>  
  
typedef struct {  
    char nom[50];  
    char prenom[50];  
    int numero;  
} Etudiant; // erreur 3 : point-virgule manquant, car typedef est une instruction  
  
Etudiant CreerEtudiant(char *p, char *n, int num) { // erreur 4 : point-virgule manquant, car typedef est une instruction  
    Etudiant res;  
    res.numero = num;  
    strncpy(res.nom,n,50);  
    strcpy(res.prenom,p);  
    return res;  
}  
  
void AfficherEtudiant(const Etudiant *e) {  
    printf("%d %s %s\n",e->numero, e->prenom, e->nom); // erreur 5 : %d %d %s -> %d %s %s et e.numero -> e->numero car e est un pointeur.  
}  
  
int main() {  
    Etudiant e1;  
    Etudiant e2;  
    e1 = CreerEtudiant("Nada","Mimouni",2);  
    AfficherEtudiant(&e1); // erreur 6 : e1 -> &e1 car la fonction attend un pointeur  
    e2 = CreerEtudiant("Ernest-Antoine","Seilliere",1);  
    AfficherEtudiant(&e2); // erreur 7 : AfficherEtudiants -> AfficherEtudiant car la fonction AfficherEtudiants n'existe pas  
    return 0;  
}
```
