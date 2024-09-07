
## 1. Multiplication de Karatsuba

### 1. Ecrivez la méthode de multiplication naïve pour deux nombres $x, y \in \mathbb{Z}$

En supposant que $x$ et $y$ ont bien le même $n$ nombre de chiffres : 
```Python
def multiplication_naive(intx, inty): 
	# Décomposer x en somme de multiple de 10
	x = [int(chiffre) for chiffre in str(intx)]
	y = [int(chiffre) for chiffre in str(inty)]
		
    n = len(x)  # La longueur des tableaux x et y  
    t = [0] * (2 * n - 1)  # Initialiser le tableau de résultat avec des zéros  
  
    for i in range(n):  
        for j in range(n):  
            t[i + j] += x[i] * y[j]  # Effectuer la multiplication et ajouter le résultat à la position appropriée  
  
    return sum([t[i] * 10 ** (2 * n - 1 - i - 1) for i in range(2 * n - 1)])  
  
  
print(multiplication_naive(12, 30))  # Affiche 360
```
Cet algorithme est bien de complexité $\theta(n^2)$.

### 2. Ecrivez l'algorithme récursive de Karatsuba, qui prend comme paramètres deux nombres $x, y \in \mathbb{Z}$. A chaque fois, considérez $k = \lfloor \frac{n}{2} \rfloor$.

```Python
def Karatsuba(x, y):  
    if x < 10 or y < 10:  
        return x * y  
  
    n = max(len(str(x)), len(str(y)))  
    n2 = n // 2  
  
    B = 10 ** n2  
  
    a = x // B  
    b = x % B  
    c = y // B  
    d = y % B  
  
    z2 = Karatsuba(a, c)  
    z0 = Karatsuba(b, d)  
    z1 = Karatsuba((a + b), (c + d)) - z2 - z0  
  
    result = (z2 * (10 ** (n2 * 2))) + (z1 * (10 ** n2)) + z0  
    return result  
  
print(Karatsuba(30, 12))
```

### 3. Comparez les temps d'exécution

On remarque que les temps d'exécution sont très très similaires jusqu'à un très grand n.
## 2. Algorithme inconnu

En python, on implémenterait cet algorithme de la manière suivante :

```Python
def inconnu(a, b):
	c = 0
	while 0 < b:
		if b%2 == 1:
			c += a
		a *= 2
		b = b//2
	return c 
```

Cette algorithme permet de renvoyer la multiplication des nombres a et b.

Supposons, au risque de les intervertir, $a > b$
$a$ et $b$ peuvent se représenter sous une forme binaire : 
$a = \sum_{i=0}^p a_{i}2^i$ et $b = \sum_{i=0}^{p'} b_{i}2^i$

où les $a_i$ et les $b_i$ sont des chiffres binaires, c'est-à-dire soit 0, soit 1.

L'algorithme effectue la multiplication de ces deux sommes en utilisant une boucle. Pour chaque bit $a_i$ de `a` :

- Si $b_i$ est égal à 0, cela signifie qu'il y a 0 fois $2^i$ dans `b`, et donc $b_i 2^i$ est égal à 0. Dans ce cas, nous n'avons pas besoin d'ajouter quoi que ce soit au résultat.
- Si $b_i$ est égal à 1, cela signifie qu'il y a 1 fois $2^i$ dans `b`, et donc $b_i 2^i$ est égal à $2^i$. Dans ce cas, nous ajoutons $2^i$ aux termes correspondants de `a`, de sorte que $a_i 2^i$ devienne $(a_i + 1)2^i$.

L'algorithme se poursuit jusqu'à ce que `b` soit réduit à zéro, et le résultat final est stocké dans la variable `c`, qui est retournée à la fin de la fonction. Ainsi, l'algorithme calcule efficacement le produit de `a` et `b` en exploitant la représentation binaire des nombres.
  
## 3. Propagation de la Covid

### 1. Ecrivez une fonction qui, étant donné une grille comme celle de l’exemple, calcule l’état de la grille à l’heure suivante. Qu’est-ce que nous pouvons conclure si la grille ne change pas ?

```Python
def next_hour(grid):  
    next_hour_grid = [[cell for cell in row] for row in grid]  
  
    for i in range(4):  
        for j in range(4):  
            if grid[i][j] == '0':  
                infected_neighbors = 0  
  
                for (x, y) in [(i - 1, j), (i + 1, j), (i, j - 1), (i, j + 1)]:  
                    if 0 <= x < 4 and 0 <= y < 4 and grid[x][y] == 'X':  
                        infected_neighbors += 1  
  
                if infected_neighbors >= 2:  
                    next_hour_grid[i][j] = 'X'  
  
    return next_hour_grid  
  
  
def get_grid_of_hour(x):  
    i = 0  
    grid = [  
        ['X', '0', '0', 'X'],  
        ['0', '0', 'X', '0'],  
        ['0', '0', '0', '0'],  
        ['X', '0', '0', '0']  
    ]  
    while i < x:  
        grid = next_hour(grid)  
        i += 1  
  
    return grid  
  
  
for hour in range(10):  
    print(f'Hour {hour}')  
    for row in get_grid_of_hour(hour):  
        print(' '.join(row))  
    print()
```

### 2. Combien de personnes malades faut-il pour contaminer éventuellement toute une grille ? Est-ce que leur distribution initiale dans la grille peut affecter le résultat final ?

On remarque qu'avec 0 ou 1 malade il est impossible de contaminer qui que ce soit.
Avec 2 malades, en fonction  de leur répartition il est possible de contaminer 1 personne au maximum.
Avec 3 malades, dans la meilleure disposition on ne peut contaminer que 3 personnes supplémentaires, pour un total de 6 malades.
Avec 4 malades, dans la meilleure disposition (diagonale) on peut contaminer indéfiniment toutes les personnes.
Plus généralement, pour une grille à $n \times n$ personnes, il suffit d'avoir la diagonale de malade pour contaminer tout le monde, c'est-à-dire il suffit d'avoir $n$ malades dans la meilleure disposition et en $n-1$ heures tout le monde sera contaminé.
 
### 3. Considérez la grille de l’exemple. Combien d’heures faut-il attendre pour que tous soient infectés ?

Grâce au code de la question 1, on remarque qu'il faut attendre 9 heures pour que tout le monde soit infecté.