
## Cours 1

### Introduction
Un langage formel est représenté par des mots, formés d'éléments d'un alphabet.

On s'intéresse dans ce cours à deux mécanismes :
- ceux qui génèrent les langages (expressions régulières, grammaires)
- ceux qui les acceptent ou les reconnaissent (automates)

La compilation est constitué de trois étapes : 
- Analyse lexicale : Est-ce que le mot est dans le dictionnaire
- Analyse syntaxique : Est-ce que la phrase est correcte grammaticalement
- Analyse sémantique : Quel est le sens de la phrase

### Rappels
#### Parties, partitions
Si $|A| = n$ alors $|P(A)| = 2^n$

Une partition de A est un ensemble de $A_{i}$ tel que $A_{i} \neq 0$, $A_{i} \subseteq A$, $A_{i} \cap A_{j} = \emptyset$ et l'union de tous les éléments forme A.

#### Fonctions
$f$ est injective si $f(x) = f(y) \implies x = y$, surjective si $f(A) = B$ avec $f : A \to B$

#### Relations
Une relation binaire R entre les éléments de deux ensembles $E$ et $F$ est un sous ensemble $G$ du produit cartésien $E \times F$, et alors $x$ R $y$ si $(x,y) \in G$
Exemple : $\leq$ est une relation binaire avec $E$ et $F$ des sous-ensembles des réels.

Une relation d'arité $n$ est une entre les éléments d'ensembles $E_{1}, \dots, E_{n}$ est un sous-ensemble du produit cartésien $E_{1} \times \dots \times E_{n}$

R une relation binaire sur $X$ est :
- réflexive si $x$ R $x$, $\forall x \in X$
- antiréflexive si $!(x$ R $x)$, $\forall x \in X$
- symétrique si $\forall$

