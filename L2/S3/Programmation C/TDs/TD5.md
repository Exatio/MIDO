# TD5 : Structures

## Exercice 1 : Rationnels

### 1. Définir une structure ``Rationnel`` permettant de représenter un nombre rationnel.

```C
struct Rationnel { 
	int numerateur; 
	int denominateur;
	int signe;
};
```


### 2. Écrire une fonction ``RemplirRationnel()`` qui demande à l’utilisateur la saisie d’un nombre rationnel. La fonction prend en paramètre l’adresse d’un rationnel et le modifie.

```C
void RemplirRationnel(struct Rationnel *nombre) {  
    printf("Entrez le numérateur : ");  
	scanf("%d", &(nombre->numerateur));  
	  
	do {  
	    printf("Entrez le dénominateur (!= 0) : ");  
		scanf("%d", &(nombre->denominateur));  
	} while (nombre->denominateur == 0);  

	do {  
	    printf("Entrez le signe (1 pour +, 0 pour -) : ");  
		scanf("%d", &(nombre->signe));  
	} while (nombre->signe != 0 && nombre->signe != 1);  
}
```


### 3. Écrire une fonction `AfficheRationnel()` qui affiche le rationnel donné en argument. On rappelle qu’un passage par valeur copie entièrement la structure, contrairement à un passage par adresse.

```C
void AfficheRationnel(struct Rationnel nombre) {
	printf("Nombre rationnel : %c %d/%d\n", nombre.signe == 1 ? '+' : '-' , nombre.numerateur, nombre.denominateur);
}
```

### 4. Écrire une fonction effectuant la multiplication entre deux rationnels. Choisir une signature de fonction adaptée. On ignorera la simplification.

```C
struct Rationnel multi(struct Rationnel *a, struct Rationnel *b) {
    struct Rationnel resultat;
    resultat.numerateur = a->numerateur * b->numerateur;
    resultat.denominateur = a->denominateur * b->denominateur;
	resultat.signe = (a->signe && b->signe) || (!(a->signe) && !(b->signe));
    return resultat;
}
```

### 5. Écrire une fonction ``main()`` testant ces fonctions.

```C
void main() {
    struct Rationnel nombre1; 
    struct Rationnel nombre2;

	RemplirRationnel(&nombre1);
	RemplirRationnel(&nombre2);

    printf("Nombre 1 : ");
    AfficheRationnel(nombre1);
    printf("Nombre 2 : ");
    AfficheRationnel(nombre2);

    struct Rationnel resultat = multi(&nombre1, &nombre2);

    printf("Le résultat de la multiplication est : ");
    AfficheRationnel(resultat);
}
```

## Exercice 2 : Classe d'étudiants

Un étudiant est modélisé par un nom, un numéro d’étudiant et une série de notes.
### 1. Écrire une structure symbolisant un étudiant.

```C
struct Etudiant {
	char nom[50];
	int numeroEtudiant;
	float notes[5];
};
```

### 2. Écrire une fonction permettant la saisie d’un étudiant à l’utilisateur.

```C
void saisirEtudiant(struct Etudiant *etudiant) {
    printf("Entrez le nom de l'etudiant: ");
    scanf("%s", etudiant->nom);

    printf("Entrez le numero d'etudiant: ");
    scanf("%d", &etudiant->numeroEtudiant);

    printf("Entrez les notes de l'etudiant (5 notes) :\n");
    for (int i = 0; i < 5; ++i) {
        printf("Note %d : ", i + 1);
        scanf("%f", &etudiant->notes[i]);
    }
}
```

### 3. Écrire une fonction affichant un étudiant.

```C
void afficherEtudiant(const struct Etudiant *etudiant) {
    printf("Nom: %s\n", etudiant->nom);
    printf("Numero d'etudiant: %d\n", etudiant->numeroEtudiant);
    printf("Notes: ");
    for (int i = 0; i < 5; ++i) {
        printf("%.2f ", etudiant->notes[i]);
    }
    printf("\n");
}
```


### 4. Écrire une fonction renvoyant la moyenne d’un étudiant.

```C
float calculerMoyenne(const struct Etudiant *etudiant) {
    float somme = 0.0;

    for (int i = 0; i < 5; ++i) {
        somme += etudiant->notes[i];
    }

    return somme / 5.0;
}
```


### 5. Écrire une fonction permettant l’ajout d’une note à un étudiant. Cette fonction renvoie 1 si l’ajout a été possible, 0 sinon.

```C
int ajouterNote(struct Etudiant *etudiant, float nouvelleNote) {

    if (sizeof(etudiant->notes) / sizeof(etudiant->notes[0]) >= 5) {
        printf("Impossible d'ajouter une nouvelle note. Le nombre maximum de notes est atteint.\n");
        return 0; 
    }
    etudiant->notes[sizeof(etudiant->notes) / sizeof(etudiant->notes[0])] = nouvelleNote;

    return 1; 
}
```


### 6. Écrire une fonction ``main()`` testant ces fonctions.

```C
void main() {
    struct Etudiant etudiant1;

    saisirEtudiant(&etudiant1);

    printf("\nInformations de l'etudiant saisi :\n");
    afficherEtudiant(&etudiant1);

    float moyenne = calculerMoyenne(&etudiant1);
    printf("\nLa moyenne de l'etudiant est : %.2f\n", moyenne);

    int ajoutPossible = ajouterNote(&etudiant1, 75.0);
    if (ajoutPossible) {
        printf("Note ajoutee avec succes.\n");
    } else {
        printf("Impossible d'ajouter la note.\n");
    }
    
    printf("\nInformations de l'etudiant apres ajout de la note :\n");
    afficherEtudiant(&etudiant1);
}
```

### 7. Écrire une structure symbolisant une classe d’étudiants.

```C
struct ClasseEtudiants {
    char nomClasse[50];
    int nombreEtudiants;
    struct Etudiant listeEtudiants[30];
};
```


### 8. Écrire une fonction permettant l’affichage d’une classe.


```C
void afficherClasse(const struct ClasseEtudiants *classe) {
    printf("Nom de la classe: %s\n", classe->nomClasse);
    printf("Nombre d'etudiants: %d\n", classe->nombreEtudiants);

    for (int i = 0; i < classe->nombreEtudiants; i++) {
        printf("\nInformations de l'etudiant %d :\n", i + 1);
        afficherEtudiant(&classe->listeEtudiants[i]);
    }
}
```

### 9. Écrire une fonction permettant l’ajout d’un étudiant dans une classe.

```C
int ajouterEtudiant(struct ClasseEtudiants *classe, const struct Etudiant *nouvelEtudiant) {
    if (classe->nombreEtudiants >= 30) {
        printf("Impossible d'ajouter un nouvel etudiant.\n");
        return 0; 
    }
    classe->listeEtudiants[classe->nombreEtudiants] = *nouvelEtudiant;
    classe->nombreEtudiants++;

    return 1;
}
```

### 10. Écrire une fonction prenant en argument un nom d’étudiant et une classe et renvoyant la moyenne de cet étudiant, ou -1 s’il n’existe pas dans la classe.

```C
float moyenneEtudiant(const char *nomEtudiant, const struct ClasseEtudiants *classe) {
    for (int i = 0; i < classe->nombreEtudiants; ++i) {
        if (strcmp(nomEtudiant, classe->listeEtudiants[i].nom) == 0) { // dans string.h permet de vérifier que deux chaînes de caractères sont identiques. on peut le faire à la main si besoin
            float somme = 0.0;
            for (int j = 0; j < 5; ++j) {
                somme += classe->listeEtudiants[i].notes[j];
            }
            return somme / 5.0;
        }
    }
    return -1.0;
}
```

### 11. Écrire une fonction renvoyant l’étudiant ayant la meilleure moyenne de la classe.

```C
// Fonction pour trouver l'étudiant avec la meilleure moyenne de la classe
struct Etudiant meilleurEtudiant(const struct ClasseEtudiants *classe) {
    struct Etudiant meilleur = classe->listeEtudiants[0];
    float meilleureMoyenne = calculerMoyenne(&meilleur);

    for (int i = 1; i < classe->nombreEtudiants; ++i) {
        float moyenneActuelle = calculerMoyenne(&classe->listeEtudiants[i]);
        if (moyenneActuelle > meilleureMoyenne) {
            meilleur = classe->listeEtudiants[i];
            meilleureMoyenne = moyenneActuelle;
        }
    }

    return meilleur;
}
```

### 12. Écrire une fonction ``main()`` testant ces fonctions.


```C
int main() {
    // Création d'une classe d'étudiants
    struct ClasseEtudiants classe1 = {"Informatique", 3,
                                      {{"Alice", 1001, {85.0, 90.5, 78.0, 92.5, 88.0}},
                                       {"Bob", 1002, {76.5, 88.0, 90.0, 85.5, 92.0}},
                                       {"Charlie", 1003, {92.0, 84.5, 88.5, 90.0, 87.5}}}
                                     };

	afficherClasse(&classe1);

	struct Etudiant nouvelEtudiant = {"Pierre", 1004, {80.0, 85.5, 88.0, 92.0, 89.5}};
	int ajoutPossible = ajouterEtudiant(&classe1, &nouvelEtudiant);
	if (ajoutPossible) {
		printf("\nNouvel etudiant ajoute avec succes.\n");
	} else {
		printf("\nImpossible d'ajouter le nouvel etudiant.\n");
	}
	printf("\nInformations de la classe1 apres l'ajout :\n");
	afficherClasse(&classe1);
	
    char nomRecherche = "Charlie";
    float moyenneCharlie = moyenneEtudiant(&nomRecherche, &classe1);
    if (moyenneCharlie != -1.0) {
        printf("\nLa moyenne de l'etudiant %s dans la classe est : %.2f\n", nomRecherche, moyenneCharlie);
    } else {
        printf("\nL'etudiant %s n'a pas ete trouve dans la classe.\n", nomRecherche);
    }

    // Test de la fonction pour trouver l'étudiant avec la meilleure moyenne de la classe
    struct Etudiant meilleurDeLaClasse = meilleurEtudiant(&classe1);
    printf("\nMeilleur etudiant de la classe :\n");
    printf("Nom: %s\n", meilleurDeLaClasse.nom);
    printf("Numero d'etudiant: %d\n", meilleurDeLaClasse.numeroEtudiant);
    printf("Moyenne: %.2f\n", calculerMoyenneEtudiant(&meilleurDeLaClasse));

    return 0;
}

```

