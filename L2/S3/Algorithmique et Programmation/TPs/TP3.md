## Exercice 1 :  Racine carrée

### Ecrivez cet algorithme

```python
from random import random  
from math import sqrt  
  
def racine_carree(a):  
    x = a/2 # ou random()  
    epsilon = 0.000001  
    while epsilon < abs(x ** 2 - a):  
        x = 1 / 2 * (x + a / x)  
    return x  
  
  
print(racine_carree(121))
```

### Comparez l'algorithme avec la fonction ``sqrt`` de Python. Ensuite, calculez la racine carrée de tous les entiers entre 1 et 1 milliard et voyez le nombre d'itérations utilisées.

Mon PC n'a pas supporté le calcul d'itérations pour les 1 milliards+ de valeurs

### Pourquoi est-ce que cet algorithme fonctionne ?

Cet algorithme fonctionne car on calcule les termes de la suite:<br>
$U_0 \in \mathbb{R}$ <br>
$\forall n \in \mathbb{N}, U_{n+1} = f(U_n)$<br>
Avec $f:\mathbb{R}^{*} \rightarrow \mathbb{R}$ <br>
$x \rightarrow \frac{1}{2}(x+\frac{A}{x})$ <br>
On montre assez facilement que si $U_0 \in \mathbb{R}^{+}$ alors $U_n \in \mathbb{R}^{+}, \forall n \in \mathbb{N}$ <br>
De même on peut montrer que $U_n$ converge, ainsi f étant continue la suite $U_n$ tend vers une limite $l \in \mathbb{R}^{+}$ telle que $f(l)=l$ <br>
La résolution de cette équation nous donne deux solutions $\sqrt{A}$ et $-\sqrt{A}$ $l$ étant positif la limite est donc $\sqrt{A}$ Cela prouve que la limite de $(U_n)$ obtenue en composant un nombre assez grand de fois est $\sqrt{A}$ et la fonction donne le premier terme de la suite tel que $U_n$ est $\epsilon$ proche de $\sqrt{A}$.

## Exercice 2 : La bifurcation de Feigenbaum

### Ecrivez une fonction qui calcule la suite de Feigenbaum étant donné $\mu$ et $x_{0}$.

```python
def Feigenbaum(mu, x0, n):  
    k = 0  
    xk = x0  
    while k <= n:  
        xk = 1 - mu * xk * xk  
        k += 1  
    return xk  
  

mu = 2
x0 = 0.9

for i in range(1, 6):  
    print(Feigenbaum(mu, x0, i))
```

### A partir du même point initial $x_0$ étudiez les différentes suites obtenues quand on considère les valeurs suivantes pour $\mu$.

$0 \leq \mu \leq 0.75$
$0.75 \leq \mu \leq 1.25$
$1.25 \leq \mu \leq 1.368$
$1.368 \leq \mu \leq 1.401$
$1.401 \leq \mu \leq 2$


```python
import matplotlib.pyplot as plt  
import numpy as np  
  
  
def Feigenbaum(mu, x0, n):  
    k = 0  
    xk = x0  
    while k <= n:  
        xk = 1 - mu * xk * xk  
        k += 1  
    return xk  
  
  
x0Values = [0, 0.01, 0.02]  
  
hor = np.linspace(0, 50, 50)  
  
mu = 1.5  
  
for x0 in x0Values:  
    ver = [Feigenbaum(mu, x0, y) for y in hor]  
    plt.plot(hor, ver, label=f'{x0}')  
    plt.legend()  
  
plt.xlabel('n')  
plt.ylabel('Feigenbaum(n)')  
plt.title(f'Paramètre Mu = {mu}')  
plt.show()
```

On teste ici avec $\mu= 1,5$ pour les 50 premiers $n$, mais on peut le faire varier dans le code.
Grâce aux captures d'écran ci-dessous, on en déduit: 

Pour $\mu \in [0,0.75]$ les suites tendent vers une même limite <br>
Pour $\mu \in [0.75,1.25]$ les suites oscillent entre 2 valeurs <br>
Pour $\mu \in [1.25,1.368]$ les suites oscillent entre 4 valeurs <br>
Pour $\mu \in [1.368,1.401]$ les suites oscillent entre 8 valeurs

Pour $\mu \in [1.401,2]$ les suites oscillent entre 16 valeurs <br>

![[Pasted image 20231018182033.png]]

![[Pasted image 20231018182109.png]]
![[Pasted image 20231018182123.png]]

![[Pasted image 20231018182152.png]]

![[Pasted image 20231018182202.png]]![[Pasted image 20231018182349.png]]