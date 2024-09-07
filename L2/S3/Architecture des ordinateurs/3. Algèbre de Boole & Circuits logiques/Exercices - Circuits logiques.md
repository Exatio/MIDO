## Exercice 7

Soit un entier de 0 à 7 représenté par 3 bits $b_{2}b_{1}b_{0}$. Soit F la fonction de $[0, 7] \to {0, 1}$ telle que $F(0) = F(3) = F(4) = F(7) = 1$ et $F(1) = F(2) = F(5) = F(6) = 0.$

### 1. Donner la table de vérité de F

$b_{2}$ | $b_1$ | $b_{0}$ | Sortie
:---: | :---: | :---: | :---: 
0 | 0 | 0 | 001
0 | 0 | 1 | 000
0 | 1 | 0 | 000
0 | 1 | 1 | 001
1 | 0 | 0 | 001
1 | 0 | 1 | 000
1 | 1 | 0 | 000
1 | 1 | 1 | 001

### 2. Donner l'expression algébrique de F

$$
\begin{align}
F(b_{2}, b_{1}, b_{0}) &= \overline{b_{2}}\cdot \overline{b_{1}}\cdot \overline{b_{0}} + \overline{b_{2}}\cdot b_{1}\cdot b_{0} + b_{2} \cdot \overline{b_{1}}\cdot \overline{b_{0}} + b_{0}\cdot b_{1}\cdot b_{2}
\end{align}
$$
### 3. Simplifier F

$$
\begin{align}
F(b_{2}, b_{1}, b_{0}) &= \overline{b_{2}}\cdot \overline{b_{1}}\cdot \overline{b_{0}} + \overline{b_{2}}\cdot b_{1}\cdot b_{0} + b_{2} \cdot \overline{b_{1}}\cdot \overline{b_{0}} + b_{0}\cdot b_{1}\cdot b_{2} \\
&=\overline{b_{2}}(\overline{b_{1}}\cdot \overline{b_{0}} + b_{1} \cdot b_{0}) + b_{2}(\overline{b_{1}}\cdot \overline{b_{0}} + b_{1} \cdot b_{0}) \\
&= (\overline{b_{2}}+b_{2})\cdot(\overline{b_{1}}\cdot \overline{b_{0}} + b_{1} \cdot b_{0}) \\
&= \overline{b_{1}}\cdot \overline{b_{0}} + b_{1} \cdot b_{0} \\
XOR&= \overline{(b_{1} \oplus b_{0})} \\
\end{align}
$$

### 4. Représenter le circuit logique de F uniquement à l'aide de portes NAND.

$$
\begin{align}
F(b_{2}, b_{1}, b_{0}) &= \overline{(b_{1} \oplus b_{0})} \\
\\
&= \overline{(\overline{b_{1}}\cdot \overline{b_{0}}) \cdot (\overline{b_{1} \cdot b_{0}})} \\
 \\
&= \overline{\overline{(\overline{b_{1}} \cdot \overline{b_{1}}) \cdot (\overline{b_{0}\cdot b_{0}})} \cdot \overline{b_{1}\cdot b_{0}}}
\end{align}
$$
On a ici transformé les ``NON(b1)`` en ``NON(b1 et b1)``, c'est-à-dire ``NAND(b1, b1)``


## Exercice 8
Soit une machine qui travaille sur des nombres binaires signés de 3 bits. La valeur signée d’un mot $a_2a_1a_0$ est égale à $a_0 + 2a_1 − 4a_2$ (c’est la représentation classique en complément à 2). On désire construire un circuit qui donne en sortie $b_2b_1b_0$ l’opposé de la valeur binaire d'entrée (par exemple, si on a 2 en entrée, on veut la valeur binaire -2 à la sortie).

### 1. Toutes les valeurs sont-elles autorisées en entrée ? Autrement dit, le circuit donne-t-il toujours une valeur correcte ?

Sur 3 bits en représentation complément à 2, on peut représenter 8 nombres, ceux de $-3$ à $4$.
Donc on peut représenter tous les opposés sauf celui de $4$.

### 2. Donner la table de vérité du circuit pour toutes les valeurs autorisées.

|$a_2$|$a_1$|$a_0$|$b_2$|$b_1$|$b_0$|$e$|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|0|0|0|0|0|0|0|
|0|0|1|1|1|1|0|
|0|1|0|1|1|0|0|
|0|1|1|1|0|1|0|
|1|0|0|-|-|-|1|
|1|0|1|0|1|1|0|
|1|1|0|0|1|0|0|
|1|1|1|0|0|1|0|

### 3. Donner les expressions logiques des 3 bits de sortie en fonction des 3 bits d'entrée en simplifiant au maximum les expressions et en ne tenant pas compte des valeurs interdites.

$$
\begin{align}
b_{0} = F_{b_{0}}(a_{2}, a_{1}, a_{0}) &= a_{0}\\ \\

b_{1} = F_{b_{1}}(a_{2}, a_{1}, a_{0}) &= \overline{a_{2}} \cdot \overline{a_{1}} \cdot a_{0} + \overline{a_{2}} \cdot a_{1} \cdot \overline{a_{0}} + a_{2} \cdot \overline{a_{1}} \cdot a_{0} + a_{2} \cdot a_{1} \cdot \overline{a_{0}} \\
&= \overline{a_{2}} \cdot (\overline{a_{1}} \cdot a_{0} + a_{1}\cdot \overline{a_{0}}) + a_{2} \cdot (\overline{a_{1}} \cdot a_{0} + a_{1}\cdot \overline{a_{0}}) \\
&= (a_{2} + \overline{a_{2}}) \cdot (\overline{a_{1}} \cdot a_{0} + a_{1}\cdot \overline{a_{0}}) \\
&= \overline{a_{1}} \cdot a_{0} + a_{1}\cdot \overline{a_{0}} \\
XOR &= a_{1} \oplus a_{0} \\ \\
 
b_{2} = F_{b_{2}}(a_{2}, a_{1}, a_{0}) &= \overline{a_{2}} \cdot \overline{a_{1}}\cdot a_{0} +\overline{a_{2}}\cdot a_{1} \cdot \overline{a_{0}} + \overline{a_{2}} \cdot a_{1} \cdot a_{0}\\
&= \overline{a_{2}} \cdot(\overline{a_{1}} \cdot a_{0} + a_{1} \cdot \overline{a_{0}} + a_{1} \cdot a_{0}) \\
&= \overline{a_{2}}\cdot(a_{1} + a_{0})
\end{align}
$$

### 4. Donner l'expression logique d'un bit supplémentaire en sortie, $e$ (débordement), qui indiquerait qu'une valeur interdite est présente sur les entrées.

La seule valeur interdite étant $4_{10} = 100_{2}$, l'expression logique du bit $e$ de débordement est :
$$
e = a_{2} \cdot \overline{a_{1}} \cdot \overline{a_{0}} 
$$
### 5. Pouvez-vous généraliser certaines de ces expressions à des nombres de $n$ bits ? Plus précisément, montrer que pour un circuit donnant l'opposé d'un nombre signé sur $n$ bits, le bit de poids fort et le bit de poids faible de la sortie s'expriment facilement en fonction des bits d'entrée. Même question pour le bit de débordement.

Sur $n$ bits :
- En représentation complément à 2, on peut représenter les valeurs dans $[-2^{n}+1,2^{n}]$$
- On aura toujours $b_{0} = a_{0}$ car $a_{0}$ représente la parité de l'entier d'entrée (puisque tous les autres sont des multiples de 2), et l'inverse d'un nombre pair sera toujours pair.
- $b_{n-1}=\overline{a_{n-1}}\cdot(a_{n-2} + \dots + a_{1} + a_{0})$
- Le bit de débordement se notera toujours $e = a_{n} \cdot \overline{a_{n-1}} \cdot (\dots) \cdot \overline{a_{1}}$, puisqu'en représentation en complément à 2, le seul élément dont on ne peut représenter l'inverse sera le plus grand dans les positifs.


## Exercice 10
> à rattraper
## Exercice 11
> à rattraper
## Exercice 12 
> à rattraper
### 1. Donner la table de vérité d’un demi-additionneur 1 bit. Donner le schéma logique d’un demi-additionneur en utilisant une porte ET et une porte XOR

### 2. Donner la table de vérité d’un additionneur complet. Donner le schéma logique d’un additionneur complet en utilisant deux demi-additionneurs et une porte OU.

### 3. Donner le schéma d’un additionneur 4 bits.

### 4. On suppose que le passage d’un signal électrique dans une porte « coûte » 10 ns. On dit alors qu’un circuit travaille en p ns si tous les signaux en sortie sont disponibles en au maximum p ns. En combien de temps un demi-additionneur, un additionneur complet et un additionneur 4 bits travaillent ils ?

### 5. On va construire un additionneur 4 bits à retenue anticipée, c’est-à-dire un circuit où le calcul des retenues intermédiaires se fait plus rapidement. Soit une fonction de génération de retenue G = ab et une fonction de propagation de retenue P = a + b; montrer que la retenue de sortie d’un additionneur complet peut se calculer par la formule r ′ = Pr + G, où a et b sont les entrées et r la retenue d’entrée.

### 6. Dans notre additionneur 4 bits, on note Gi = aibi et Pi = ai + bi, et ri la retenue intermédiaire d’un étage, normalement calculée à partir des entrées ai, bi et de la retenue précédente ri−1. Exprimer r0, r1, r2 et r3 = r en fonction de G0, G1, G2, G3, P0, P1, P2 et P3.

### 7. En supposant que l’on dispose de plusieurs portes OU et ET à 2, 3 et 4 entrées, et que chacune travaille en 10 ns, en combien de temps se fait le calcul des Gi, Pi et ri ? Est-ce intéressant ? Quelle différence y a-t-il entre le temps de travail d’un additionneur 8 bits normal et d’un additionneur 8 bits à retenue anticipée (avec les bonnes portes OU et ET) ?
