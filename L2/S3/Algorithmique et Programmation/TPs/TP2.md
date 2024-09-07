### Exercice 1.

```python
def evaluer(t):  
    annees = t // (1000 * 60 * 60 * 24 * 365.25)  
    t %= (1000 * 60 * 60 * 24 * 365.25)  
  
    mois = t // (1000 * 60 * 60 * 24 * 30.44)  
    t %= (1000 * 60 * 60 * 24 * 30.44)  
  
    jours = t // (1000 * 60 * 60 * 24)  
    t %= (1000 * 60 * 60 * 24)  
  
    heures = t // (1000 * 60 * 60)  
    t %= (1000 * 60 * 60)  

    minutes = t // (1000 * 60)  
    t %= (1000 * 60)  
  
    secondes = t // 1000  
  
    return [annees, mois, jours, heures, minutes, secondes]
```

### Exercice 2. 

En réutilisant la fonction ``evaluer`` précédente :

```python
import time

def affichage(tab):  
    print(f'{tab[0]} années, {tab[1]} mois, {tab[2]} jours, {tab[3]} heures, {tab[4]} minutes, {tab[5]} secondes.')
    
now = time.time()  
# Exécution d'une fonction, procédure, ...
affichage(evaluer(time.time() - now));
```

### Exercice 3.
	
```python
import time  
from math import log10  

# Les fonctions affichage et evaluer sont considerees présentes.

for n in [100, 500, 1000]:

	print(f'TESTS POUR N = {n}')
  
	print('pour nlog(n)')  
	affichage(evaluer(n*log10(n)))  
	print()  
	  
	print('pour n:')  
	affichage(evaluer(n))  
	print()  
	  
	print('pour log(n)')  
	affichage(evaluer(log10(n)))  
	print()  
	  
	print('pour n^2')  
	affichage(evaluer(n**2))  
	print()  
	  
	print('pour n^3')  
	affichage(evaluer(n**3))  
	print()  
	  
	print('pour 2^n')  
	affichage(evaluer(2**n))  
	print()
	print()
```


### Exercice 4.

```python
from random import randint  

def tab_alea(n):  
    return [randint(1,1000) for i in range(n)]  
  
print(tab_alea(10))
```

### Exercice 5.

Tri par insertion (Insertion sort)

```python
import time  

# on suppose que la fonction tab_alea est présente 

def insert_sort(tab):  
    for j in range(1,len(tab)):  
        i = j-1  
        key = tab[j]  
        while i>=0 and tab[i]>key:  
            tab[i+1] = tab[i]  
            i-=1  
        tab[i+1] = key  
    
t = tab_alea(10)  

print(t)  
insert_sort(t)  
print(t)

```

### Exercice 6.

Tri par bulles (Bubble sort)

```python
def bubble_sort(array):  
    n = len(array)  
  
    for i in range(n):  
        swapped = False  
  
        for j in range(0, n-i-1):  
  
            if array[j] > array[j+1]:  
                array[j], array[j+1] = array[j+1], array[j]  
                swapped = True  
        if not swapped:  
            break  
  
  
a = [100, 19, 72, 1, 5, 18]  
  
bubble_sort(a)  
print(a)
```
### Exercice 7.

Tri par fusion (Merge sort)

```python
import math  

# On suppose la fonction tab_alea présente

def merge(A,p,q,r):  
    L = A[p:q+1]  
    R = A[q+1:r+1]  
    L.append(math.inf)  
    R.append(math.inf)  
  
    i,j = 0,0  
    for k in range(p,r+1):  
        if L[i]>=R[j]:  
            A[k] = R[j]  
            j+=1  
        else:  
            A[k] = L[i]  
            i+=1  
  
def merge_sort(A,p,r):  
    if p<r:  
        q = (p+r)//2  
        merge_sort(A,p,q)  
        merge_sort(A,q+1,r)  
        merge(A,p,q,r)  
  
A = tab_alea(10)

print(A)  
merge_sort(A,0,9)  
print(A)
```

### Exercice 8.

Tri rapide (Quick Sort)

```python
def partition(a, p, r):  
  
    x = a[r]  
    i = p - 1  
    for j in range(p, r):  
        if a[j] <= x:  
            i = i + 1  
            (a[i], a[j]) = (a[j], a[i])  
    (a[i + 1], a[r]) = (a[r], a[i + 1])  
    return i + 1  
  
  
def quicksort(a, p, r):  
    if p < r:  
        q = partition(a, p, r)  
        quicksort(a, p, q - 1)  
        quicksort(a, q + 1, r)  
  
  
a = [1, 5, 4, 2, 2, 1]

quicksort(a, 0, len(a) - 1)  
print(a)
```

### Exercice 9

```python
import math  
import time  
from random import randint  
  
  
# On suppose la fonction tab_alea présente  
def tab_alea(n):  
    return [randint(1, 1000) for i in range(n)]  
  
  
def bubble_sort(array):  
    n = len(array)  
  
    for i in range(n):  
        swapped = False  
  
        for j in range(0, n - i - 1):  
  
            if array[j] > array[j + 1]:  
                array[j], array[j + 1] = array[j + 1], array[j]  
                swapped = True  
        if not swapped:  
            break  
  
  
def insert_sort(tab):  
    for j in range(1, len(tab)):  
        i = j - 1  
        key = tab[j]  
        while i >= 0 and tab[i] > key:  
            tab[i + 1] = tab[i]  
            i -= 1  
        tab[i + 1] = key  
  
  
def merge(A, p, q, r):  
    L = A[p:q + 1]  
    R = A[q + 1:r + 1]  
    L.append(math.inf)  
    R.append(math.inf)  
  
    i, j = 0, 0  
    for k in range(p, r + 1):  
        if L[i] >= R[j]:  
            A[k] = R[j]  
            j += 1  
        else:  
            A[k] = L[i]  
            i += 1  
  
  
def merge_sort(A, p, r):  
    if p < r:  
        q = (p + r) // 2  
        merge_sort(A, p, q)  
        merge_sort(A, q + 1, r)  
        merge(A, p, q, r)  
  
  
def partition(a, p, r):  
    x = a[r]  
    i = p - 1  
    for j in range(p, r):  
        if a[j] <= x:  
            i = i + 1  
            (a[i], a[j]) = (a[j], a[i])  
    (a[i + 1], a[r]) = (a[r], a[i + 1])  
    return i + 1  
  
  
def quicksort(a, p, r):  
    if p < r:  
        q = partition(a, p, r)  
        quicksort(a, p, q - 1)  
        quicksort(a, q + 1, r)  
  
  
def affichage(tab):  
    print(f'{tab[0]} années, {tab[1]} mois, {tab[2]} jours, {tab[3]} heures, {tab[4]} minutes, {tab[5]} secondes.')  
  
def evaluer(t):  
    t *= 1000  
  
    annees = t // (1000 * 60 * 60 * 24 * 365.25)  
    t %= (1000 * 60 * 60 * 24 * 365.25)  
  
    mois = t // (1000 * 60 * 60 * 24 * 30.44)  
    t %= (1000 * 60 * 60 * 24 * 30.44)  
  
    jours = t // (1000 * 60 * 60 * 24)  
    t %= (1000 * 60 * 60 * 24)  
  
    heures = t // (1000 * 60 * 60)  
    t %= (1000 * 60 * 60)  
  
    minutes = t // (1000 * 60)  
    t %= (1000 * 60)  
  
    secondes = t // 1000  
  
    return [annees, mois, jours, heures, minutes, secondes]  
  
  
n = 10000  
A = tab_alea(n)  
  
t0 = time.time()  
B = A[::]  
insert_sort(B)  
t1 = time.time()  
print(f'Insert-sort pour n = {n}: ')  
affichage(evaluer(t1 - t0))  
print()  
  
t0 = time.time()  
B = A[::]  
bubble_sort(B)  
t1 = time.time()  
print(f'Bubble-sort pour n = {n}: ')  
affichage(evaluer(t1 - t0))  
print()  
  
t0 = time.time()  
B = A[::]  
merge_sort(B, 0, len(B) - 1)  
t1 = time.time()  
print(f'Merge-sort pour n = {n}: ')  
affichage(evaluer(t1 - t0))  
print()  
  
t0 = time.time()  
B = A[::]  
quicksort(B, 0, len(B) - 1)  
t1 = time.time()  
print(f'Quick-sort pour n = {n}: ')  
affichage(evaluer(t1 - t0))  
print()
```