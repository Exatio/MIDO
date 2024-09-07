Dans un ordinateur il y a :
- 2 types d'informations : 0 et 1
- des composants élémentaires : **transistor** regroupés en **portes logiques**, regroupées en **circuits**

Il y a plusieurs types de circuits :
- **Circuits combinatoires** : on néglige le temps de propagation dans les circuits
- **Circuits séquentiels** : on peut avoir un retour des sorties vers les entrées avec une étude temporelle.

## 1. Fonctions booléennes

Les fonctions booléennes sont des fonctions de $\{0,1\}^n \to \{0,1\}$. Il y a donc $2^n$ entrées possibles.
On caractérise une fonction par sa valeur pour chacune des  $2^n$ entrées par sa **table de vérité**.
S'il y a plusieurs sorties à une fonction, on les étudie indépendamment 
### OU-EXCLUSIF : XOR