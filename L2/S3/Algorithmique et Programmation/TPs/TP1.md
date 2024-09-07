## Exercice 1

Ecrire une fonction itérative qui calcule la factorielle d’un nombre.
```python
def factorielle(n):
	fact = 1
	for i in range(n, 1, -1):
		fact *= i
	return fact
```

## Exercice 2

De façon équivalente, on peut définir la factorielle inductivement par $0! = 1$ et $\forall n \geq 1, n\neq n*(n-1)!$ 
Ecrire une fonction récursive de la précédente fonction.

```python
def fact(n):
	if n == 1:
		return 1
	else:
		return n * fact(n-1)
```


## Exercice 3

La définition de la suite de Fibonacci est la suivante :

$$
f_{n} = \begin{cases}
0 & si\ n = 0 \\
1 & si\ n = 1 \\
f_{n-1}+f_{n-2} & si\ n \geq 2
\end{cases}
$$
Ecrivez un algorithme récursif **fibo_rec** qui, étant donné un entier *n*, calcule $f_n$

```python
def fibo_rec(n):
	if n == 0:
		return 0
	elif n == 1:
		return 1
	else:
		return fibo_rec(n-1) + fibo_rec(n-2)
		
```

## Exercice 4

Ecrivez une fonction **fibo_it** qui implémente l'algorithme 1.

```python
def fibo_it(n):
	if n == 0:
		return 0
	else:
		x = 0
		y = 1
		for i in range(2, n+1):
			temp = x + y
			x = y
			y = temp
		return y
```

## Exercice 5

Les deux fonctions affichent bien le même résultat, en revanche, la fonction récursive prend plus de temps à s'exécuter.

## Exercice 6

```python
def fibo_smart_rec_aux(n):  
    if n<=1:  
        return (n,0)  
    else:  
        fn_1,fn_2 = fibo_smart_rec_aux(n-1)  
        return (fn_1+fn_2,fn_1)

def fibo_smart_rec(n):  
    if n<=1:  
        return n
    (x,y)=fibo_smart_rec_aux(n-1)  
    return x+y

```

Le temps ne change pas tant que ça

## Exercice 7

### 1.
$p_n = j_{n-1} + p_{n-1}$ 
$j_n = p_{n-1}$

Donc:

$p_n = j_n + j_{n-1}  \forall n \in \mathbb{N}$

### 2.

$p_n = p_{n-1} + p_{n-2}$   
$j_{n+1} = j_n + j_{n-1}$

### 3.

$l_n = p_n + j_n$

### 4.

$n$: 0 1 2 3 4 5 6 7 
$f_n$: 0 1 1 2 3 5 8 13
$j_n$: 0 1 1 2 3 5 8 13
$p_n$: 1 1 2 3 5 8 13 21 
$l_n$: 1 2 3 5 8 21 34

On voit que 
$j_n = f_n$  
$p_n = f_{n+1}$  
$j_n = f_{n+2}$

### 5.

Les algorithmes des exercices 3 et 4 donnent les valeurs de la suite de Fibonacci qui est une manière de modéliser l'évolution d'une population


## Exercice 8

```python
def puissance_it(a,n):  
    res = 1  
    for i in range(n):  
        res*=a  
    return res  
  
print(puissance_it(2,8))
```

## Exercice 9

```python
def puissance_rec(a,n):  
    if n==0:  
        return 1  
    return a*puissance_rec(a,n-1)  
  
print(puissance_rec(2,8))
```


## Exercice 10

```python
def puissance_smart_rec(a,n):  
    if n==0:  
        return 1  
    if n%2==0:  
        x = puissance_smart_rec(a,n/2)  
        return x*x  
    else:  
        x = puissance_smart_rec(a,n//2)  
        return a*x*x  
  
print(puissance_smart_rec(2,8))
```

Asymptotiquement on divise par 2 les puissances de manière successive donc le nombre d'opérations est en $\theta(log(n))$