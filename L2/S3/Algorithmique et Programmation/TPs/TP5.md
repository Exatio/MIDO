## Exercice 1. Multiplication classique

```python
import numpy as np  
  
  
def classic_matrix_mult(a, b):  
    n = a.shape[0]  
    c = np.zeros((n, n))  
    for aLigne in range(n):  
        for bColonne in range(n):  
            somme = 0  
            for i in range(n):  
                somme += a[aLigne, i] * b[i, bColonne]  
            c[aLigne, bColonne] = somme  
    return c
  
  
a = np.zeros((2, 2))  
a[0, 0] = 5  
a[0, 1] = 2  
a[1, 0] = 3  
a[1, 1] = 0  
  
print(a)  
  
b = np.zeros((2, 2))  
b[0, 0] = 4  
b[0, 1] = 2  
b[1, 0] = 1  
b[1, 1] = 0  
  
print(b)  
  
print(classic_matrix_mult(a, b))  
print()  
print(np.dot(a, b)) # Vérification des résultats avec la fonction originelle de multiplication de matrices.
```

## Exercice 2. Algorithme de Strassen pour les matrices de taille $2^k$

Le but de cet exercice est d’implanter l’algorithme de Strassen (rappelé en page suivante).

### 1. Ecrivez une fonction ``matrix_plus`` qui, étant donné deux matrices a et b de mêmes dimensions, renvoie leur somme. De même, écrivez une fonction ``matrix_minus`` qui renvoie la différence $a − b$.

```Python
def matrix_plus(a, b):  
    n = a.shape[0]  
    c = np.zeros((n, n))  
    for i in range(n):  
        for j in range(n):  
            c[i, j] = a[i, j] + b[i, j]  
    return c  
  
def matrix_minus(a, b):  
    n = a.shape[0]  
    c = np.zeros((n, n))  
    for i in range(n):  
        for j in range(n):  
            c[i, j] = a[i, j] - b[i, j]  
    return c
```

### 2. On considère à présent des matrices carrées dont la taille est une puissance de 2. Ecrivez une fonction ``strassen_matrix_mult`` qui, étant donné deux matrices a et b, utilise l’algorithme de Strassen pour renvoyer leur produit.

```Python
def strassen_matrix_mult(a, b):  
    n = a.shape[0]  
  
    if n == 2:  
        return classic_matrix_mult(a, b)  
  
    middle = n // 2  # = n/2 mais permet de l'avoir en entier  
  
    a_1_1 = a[0: middle, 0: middle]  
    a_1_2 = a[0: middle, middle: n]  
    a_2_1 = a[middle: n, 0: middle]  
    a_2_2 = a[middle: n, middle: n]  
  
    b_1_1 = b[0: middle, 0: middle]  
    b_1_2 = b[0: middle, middle: n]  
    b_2_1 = b[middle: n, 0: middle]  
    b_2_2 = b[middle: n, middle: n]  
  
    p_1 = strassen_matrix_mult(matrix_plus(a_1_1, a_2_2), matrix_plus(b_1_1, b_2_2))  
    p_2 = strassen_matrix_mult(matrix_plus(a_2_1, a_2_2), b_1_1)  
    p_3 = strassen_matrix_mult(a_1_1, matrix_minus(b_1_2, b_2_2))  
    p_4 = strassen_matrix_mult(a_2_2, matrix_minus(b_2_1, b_1_1))  
    p_5 = strassen_matrix_mult(matrix_plus(a_1_1, a_1_2), b_2_2)  
    p_6 = strassen_matrix_mult(matrix_minus(a_2_1, a_1_1), matrix_plus(b_1_1, b_1_2))  
    p_7 = strassen_matrix_mult(matrix_minus(a_1_2, a_2_2), matrix_plus(b_2_1, b_2_2))  
  
    c_1_1 = matrix_plus(matrix_minus(matrix_plus(p_1, p_4), p_5), p_7)  
    c_1_2 = matrix_plus(p_3, p_5)  
    c_2_1 = matrix_plus(p_2, p_4)  
    c_2_2 = matrix_plus(matrix_minus(matrix_plus(p_1, p_3), p_2), p_6)  
  
    # La ligne suivante permet de créer c grâce à ses sous-matrices  
    c = np.vstack((np.hstack((c_1_1, c_1_2)), np.hstack((c_2_1, c_2_2))))  
  
    return c
```

### 3. Sur quelques exemples, vérifiez que les fonctions ``classic_matrix_mult`` et ``strassen_matrix_mult`` renvoient le même résultat.

```python
k = 3  
for i in range(10):  
    a = np.random.rand(2**k, 2**k)  
    b = np.random.rand(2**k, 2**k)  
  
    print(classic_matrix_mult(a, b))  
    print(strassen_matrix_mult(a, b))
```

Grâce à ce programme principal, on voit bien que les deux renvoient le même résultat.

## Exercice 3. Temps d'exécution

### 1. Rappelez la complexité en pire cas des deux algorithmes ci-dessus.

La complexité de la manière classique est $\theta(n^3)$
La complexité de l'algorithme de Strassen est $\theta(n^{\log_{2}7})$ (formule du cours).
### 2. Sur quelques exemples, comparez leur temps d'exécution. Que remarquez vous ? Comment l'expliquer ?

```python
for k in range(1, 10):  
    a = np.random.rand(2**k, 2**k)  
    b = np.random.rand(2**k, 2**k)  
  
    print(f'cas k = {k}')  
  
    t = time.time()  
    classic_matrix_mult(a, b)  
    tot = time.time() - t  
    print(f'temps classique : {tot}')  
  
    t = time.time()  
    strassen_matrix_mult(a, b)  
    tot = time.time() - t  
    print(f'temps strassen : {tot}')
```

On remarque que jusqu'à $k = 6$, la méthode classique est plus rapide que la méthode Strassen.
Mais à partir de $k=7$, la méthode Strassen est de plus en plus rapide comparée à la méthode classique.
### 3. (Question bonus) Comment pouvez-vous rendre plus efficace votre implémentation de l’algorithme de Strassen ? écrivez une fonction ``strassen_matrix_mult_2`` qui implante cette amélioration.


### 4. (Question bonus) Le package ``NumPy`` possède aussi une fonction pour calculer le produit de deux matrices : ``np.dot(a, b)``. Comparez son temps d’exécution avec les fonctions précédentes. Que remarquez vous ? Comment l’expliquer ?


## Exercice 4. Généralisation aux matrices carrées de taille quelconque.

### 1. (Question bonus). Ecrivez une fonction ``strassen_matrix_mult_3`` qui, étant donné deux matrices a et b carrées de même taille quelconque, renvoie leur produit. Pour cela, faites appel à la fonction ``strassen_matrix_mult_2`` définie précédemment.

