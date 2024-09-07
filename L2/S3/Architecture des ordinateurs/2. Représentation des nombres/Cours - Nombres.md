## 1. Arithmétique binaire

**Bit de poids faible**: Le 1 le plus "à droite"
**Bit de poids fort**: Le 1 le plus "à gauche"

### Addition
0 + 0 = 0
0 + 1 = 1
1 + 0 = 1
1 + 1 = 0 avec 1 de retenue
### Soustraction
0 - 0 = 0
0 - 1 = 1 avec 1 de retenue
1 - 0 = 1
1 - 1 = 0
### Multiplication
Simplement une succession d'additions

### Ressources

<iframe src="https://www.youtube.com/embed/kgw5tCE2nPA?si=Rdr--JHuRa8ryyj-" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>
<iframe src="https://www.youtube.com/embed/HrogRbmBCVE?si=QnGalYGbu9Vw7UzO" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>


## 2. Nombres entiers, positifs & négatifs

### Méthode 1 : "signe & valeur absolue"

On représente les entiers de $-2^{n-1}+1$ et $2^{n-1}$ 
Puisqu'on ne peut utiliser que des bits, on représente un entier relatif avec son signe + sa valeur absolue.
C'est-à-dire :
Sur n bits, le bit de poids fort (appelé dans ce cas **bit de signe**) représente le signe (1=négatif) et les n-1 bits restants sont la valeur absolue du nombre.

___Exemple :___
On veut représenter -85 :
85 se note 0101 0101.
-85 se note 1101 0101 car le bit de poids fort (bit de signe) montre la présence d'un -

### Méthode 2 (standard) : "en complément à 2"

On représente les entiers de $-2^{n-1}$ et $2^{n-1}$ 
Un nombre positif est représenté tel quel avec les puissances de 2.
Pour représenter un nombre négatif, **on inverse tous les bits & on ajoute 1** (en laissant tomber une retenue finale).

___Exemple :___
On veut représenter -52.
52 se note 00110100
On inverse : 11001011
On ajoute 1 : 11001100

### Quelques propriétés (complément à 2)

___Propriété :___ 
Soit X un nombre. $C_2(X)$ est la valeur binaire pure du complémentaire à 2 de X.
C'est-à-dire, on a : $X+C_2(X)=2^n [n] \iff C_2(X) = 2^n-x$
On a donc $C_2(C_2(X)) = X$

___Exemple :___ 
On veut -56 sur 8 bits.
On cherche $C_2(56)=2^8-56=200$
Alors, $-56=200=11001000$


___Propriété :___
Soit $A=a_{n-1} a_{n-2}...a_1 a_0$ une écriture binaire.
$VB(A)$ est la valeur obtenue en lisant A en binaire pur.
$$
VB(A)=\sum_{i=0}^{n-1} a_i 2^i=\sum_{i=0}^{n-2} a_i 2^i + a_{n-1} 2^{n-1}
$$
$VS(A)$ est la valeur obtenue en lisant A en représentation complémentaire à 2.
$$
VS(A)=\sum_{i=0}^{n-2}a_i 2^i -a_{n-1}2^{n-1}
$$

D'où :
$$
VB(A)-VS(A)=a_{n-1}2^{n-1} - (-a_{n-1}2^{n-1}) = a_{n-1}2^{n}
$$
Si $a_{n-1}=0$, alors $VB(A)=VS(A)$
Si $a_{n-1}=1$, alors $VB(A)=VS(A) + 2^n \iff VS(A) = VB(A)-2^n$


___Exemple : Valeur signée de 10001001___
$VB(10001001)=137$
$VS(10001001)=VB(10001001)-2^8 = 137-256=-119$

## 3. Nombres réels

### Représentation en virgule fixe

On impose la place de la virgule. 
Les bits à gauche => puissances de 2 $\geq 0$
Les bits à droite => puissances de 2 $< 0$ 

Sur n bits, la virgule se trouve après les p bits de poids faible.
$$
\begin{aligned}
x_{n-p-1} x_{n-p-2} ... x_1 x_0 x_{-1} ... x_{-p}
& = x_{n-p-1} 2^{n-p} + ... + x_0 2^0 + x_{-1} 2^{-1} + x_{-p} 2^{-p} \newline
& = \sum_{i=-p}^{n-p-1} x_i 2^i
\end{aligned}
$$
max : $2^{n-p}-2^{-p}$

### Représentation en virgule flottante (standard)

On se ramène à l'écriture

$N=\pm 1,{pm} \times 2^e$ 
$pm$ est la **pseudo-mantisse**, tandis que $1,pm$ est la **mantisse**.

___Exemple :___
$$
\begin{aligned}
1,5 &= 1,5 \times 2^0 \\ 
3,5 &= 1,75 \times 2^1 \\
500 &= 1,953125 \times 2^8 \\
0,5 &= 1 \times 2^{-1} \\
0,3125 &= 1,25 \times 2^{-2}
\end{aligned}
$$

L'écriture binaire contient 3 champs.

- signe : 1 bit (0 positif / 1 négatif)
- pseudo-mantisse : représente les puissances $<0$ de 2
$$
b_{-1} ...b_{-p} = \sum_{i=-1}^{-p} b_i2^i 
$$
 - exposant : on écrit la valeur binaire pure de (exposant vrai + biais)


___Exemple :___
exposant : $e_{n-1}e_{n-2}...e_1e_0$
valeur vraie de l'exposant : $\displaystyle\sum_{i=0}^{n-1} e_i 2^i - (2^{n-1} - 1)$


Il y a 2 normalisations : 

1. Simple précision (float en C) : 32 bits / 4 octets
	1 bit signe, 8 bits d'exposant (biais 127), 23 bits de pseudo-mantisse
	- Valeur max :
		- Exposant max : 1111 1111
		- Valeur : 255
		- biais : $2^7 - 1 = 127$
		- vrai exposant max : $255-127=128$
		- d'où valeur max $\approx 2^{128} \approx 10^{38}$
	- ``float`` en C
  
2. Double précision (double en C) : 64 bits / 8 octets
	1 bit signe, 11 bits d'exposant (biais 1023), 52 bits de pseudo-mantisse
	- Valeur max :
		- Exposant max : 0111 1111 1111
		- Valeur : $2^{11} - 1 = 2047$
		- Biais : $2^{10} - 1 = 1023$
		- Vrai exposant max : $2047 - 1023 = 1024$
		- d'où valeur max : $\approx  2^{1024}$
	- ``double`` en C, ``float`` en Python

___Exemple :___
$1,75 = 1,75 \times 2^0$ 

Simple précision (32 bits)
- Signe : + => 0
- Exposant vrai : 0 ==> Exposant décalé $0+127 = 127$ => 0111 1111
- Mantisse : 1,75 ==> Pseudo-mantisse : $0,75 = 0,5 + 0,25 = 2^{-1} + 2^{-2}$ ==> 110 0000 0000 0000 0000 0000
- En mémoire, on a donc : 0011 1111 1110 0000 0000 0000 0000 0000