## Exercice 1

$$
\begin{aligned}
100_2 &=1100100 \\
100_3 &=10201 \\
100_4 &=1210 \\
100_5 &=40 \\
100_6 &=244 \\
100_7 &=202 \\
100_8 &=144 \\
100_9 &= 121 \\
100_{16} &= 64 \\
\end{aligned}
$$

## Exercice 2


$$
\begin{align}
& 0111 \\
\times & 0101 \\
\_&\_\_\_\_ \\
& 0111 \\
+ 0&000 \\
+ 01&11 \\
+ 000&0 \\
\_\_\_\_\_&\_\_\_\_ \\
=010&0011
\end{align}
$$
## Exercice 3

$94_2=1011110$, $94_8 = 136$, $94_{16} = 5E$
$141_2 = 10001101$, $141_8=215$, $141_{16}=8D$
$163_2=10100011$, $163_8=243$, $163_{16}=A3$
$197_2=11000101$, $197_8=305$, $197_{16}=C5$

_Signe et valeur absolue_
$$
\begin{aligned}
45 &= 00101101 \\
73 &= 01001001 \\
84 &= 01010100 \\
-99 &= 11100011 \\
-102 &= 11100110 \\
-118 &= 11110110 \\
\end{aligned}
$$
_Complément à 1_
$$
\begin{aligned}
45 &= 00101101 \\
73 &= 01001001 \\
84 &= 01010100 \\
-99 &=10011100 \\
-102 &=10011001 \\
-118 &=10001001 \\
\end{aligned}
$$


_Complément à 2_
$$
\begin{aligned}
45 &= 00101101 \\
73 &= 01001001 \\
84 &= 01010100 \\
-99 &= 10011101 \\
-102 &= 10011010 \\
-118 &= 10001010 \\
\end{aligned}
$$

**Lorsqu'on calcule complément à 1 et complément à 2, bien penser à prendre les 8 bits avant de les inverser (y compris les 0 avant)**

**Attention : $C_2(x) \neq x_{C(2)}$ (Prendre le complément à 2 de x / la représentation en complément à 2 de x).

$122_2=01111010$, $43_2=00101011$
$122_{C(2)}=01111010$, $C_2(43)=11010101$
Alors, $-43_{C(2)}=11010101$

$122 + 43 = 122 + (-43) = 122_{C(2)} + -43_{C(2)} = 01111010 + 11010101 = 01001111$


## Exercice 4

### **Question 1*** : 

Un programme peut donner deux résultats différents à l'opération 101 + 99. Ce résultat dépend du type de 101 et 99 en mémoire : 
- s'ils sont traités comme des _unsigned byte_, c'est-à-dire strictement positifs ou tout autre type supportant des valeurs supérieures à 200, le résultat sera bien 200.   
- s'ils sont traités comme des _byte_, c'est-à-dire comme des représentations en compléments à 2 des entiers entre -128 et 127, alors le résultat sera $(101_{C(2)}+99_{C(2)})_{C(2)} = (01100101 + 01100011)_{C(2)} = (11001000)_{C(2)} = (C_2(11001000))_{SEV}= 00111000_{SEV} = -56$ négatif car $C_2$ commence par un 1.

### **Question 2** : 

On sait qu'il y a environ $50 000$ caractères. 
Le programme affiche $-14532$ caractères.
Le bug que l'on a fait est dépasser les entiers positifs maximum sur l'encodage du nombre (dépend du type).

Nos entiers sont donc codés sur environ $35000$ dans les positifs.
La seule puissance de 2 qui s'en rapproche est $2^{16}=65536$ qui permet d'afficher les entiers de $-32768$ à $32767$ (``short`` en C).


Le programme a commencé à 0 caractères. Il a ajouté les $32767$ prochains caractères.
Il en a ajouté un, et est passé à l'entier $-32768$. Il a ensuite avancé de 1 de $-32768$ jusqu'à $-14532$ c'est-à-dire qu'il a avancé de $18236$ caractères.
On a donc $32767 + 1 + 18236=51004$ caractères.
En réalité, ça peut même être $51004+2^{16}\mathbb{N}$ puisque l'on revient toujours à la valeur trouvée.
### **Question 3 :**

Considérons le programme C suivant :
```C
#include <stdio.h>
#include <string.h>  /* fichier dans lequel sont contenues les en-têtes des fonctions gets et strlen */

main() {
	char c;
	char str[500];
	gets(str);       /* récupère une chaîne au clavier et la met dans str*/
	c = strlen(str); /* renvoie la longueur de la chaîne */
	printf("longueur : %d\n", c);
}
```

#### Pensez-vous que ce programme affiche toujours la bonne valeur ?

Non ! En effet, la longueur de la chaîne est contenue dans la variable **c** de type *char*. Or, les char ne peuvent contenir les entiers que dans l'intervalle [−128 ; +127]. Ainsi, pour toutes chaîne dépassant 127 caractères, la valeur renvoyée par le programme sera fausse.
Pour régler cela, il faudrait remplacer le type ``char`` par un ``short`` ou un ``int``, par exemple.

#### Quelles sont ses limites de fonctionnement ?

Ses limites de fonctionnement reposent sur la création du tableau de caractères str : il ne permet de recueillir qu'un **maximum de 500 caractères**, ainsi, si on entre une chaîne de plus de 500 caractères, le programme ne sera plus correct.

> Note : Cette affirmation n'est vrai qu'en théorie... en pratique, il peut arriver que les cases mémoires suivant le tableau ne soient pas utilisées, et la fonction strlen ne s'arrêtant que lors de l'apparition d'un caractère de fin de chaîne `\0`, il y a des cas où la fonction peut produire le bon résultat - il ne faut quand même pas l'utiliser puisque le résultat est incertain.

### **Question 4** :

Considérons le programme C suivant :
```C
#include <stdio.h>

main() {
	short i;
	unsigned short j;
	i = -1;
	j = i;
	printf("%d\n", j);
}
```

#### Quelle serait la valeur affichée ?

Nous savons que les short sont à valeurs dans[−32 768 ; +32 767]  et les unsigned short à valeurs dans [0 ; 65 535].
Si on écrit implicitement ``j=i``, **??????????**
Ainsi, la valeur affichée sera 65 535.
#### Quelle serait la valeur affichée si la représentation des nombres était "signe et valeur absolue" ? Et si c'était la représentation en complément à 1 ?

**??????????**

### **Question 5** : 

#### Le langage C possède plusieurs types pour représenter les nombres entiers. Lesquels ?

Il s'agit des types ``char``, ``short``, ``int``, ``long``, et ``long long`` pour les entiers signés et ``unsigned char``, ``unsigned short``, ``unsigned int``, ``unsigned long`` ainsi que ``unsigned long long`` pour les entiers non signés.

#### Quelle question vous posez-vous avant de choisir un type pour votre variable ? Quelles sont les valeurs critiques ?

On se pose la question "*Quelle valeur ma variable peut-elle/doit-elle prendre dans mon programme ?*"
Les valeurs critiques sont répertoriées dans le tableau suivant : 

Entiers signés | Valeurs possibles | Entier non signés | Valeurs possibles
:---: | :---: | :---: | :---: 
char | [−128 ; +127] | unsigned char |  [0 ; 255]
short | [−32 768 ; +32 767] | unsigned short | [0 ; 65 535]
int (16 bits) | [−32 768 ; +32 767] | unsigned int (16 bits)| [0 ; 65 535]
int (32 bits) | [−2 147 483 648 ; +2 147 483 647] | unsigned int (32 bits) | [0 ; 4 294 967 295]
long | [−2 147 483 648 ; +2 147 483 647] | unsigned long | [0 ; 4 294 967 295] 
long long | [−9 223 372 036 854 775 808 ; +9 223 372 036 854 775 807] | unsigned long long |[0 ; +18 446 744 073 709 551 615]




## Exercice 5

On considère la représentation simplifiée des réels en virgule flottante suivante :
$X \in R$  est représentation par 10 bits ``s eeee mmmmm`` où $X = (-1)^s \times 1,m \times 2^{e-7}$ avec un exposant sur 4 bits ($0 < e \leq 15$, un exposant égal à 0 désigne 0 quelle que soit la mantisse) et une pseudo-mantisse sur 5 bits (représentant les puissances négatives de 2).

### 1. Quelles sont le plus grand et le plus petit nombre strictement positifs représentables ?

Ils sont positifs donc $s = 0$.

Le plus petit exposant possible est représenté par $0001$ dans la mesure où $0000$ en exposant représente l'entier nul. Il vaut ainsi $2^{1-7}=2^{-6}$
La plus petite pseudo-mantisse représentable sur 5 bits est représentée par $00000$, c'est-à-dire 0.
On a alors ``0 0001 00000`` qui représente $(-1)^0 \times 1,0 \times 2^{-6} = 2^{-6} = 0,015625$

Le plus grand exposant possible est représenté par $1111$. Il vaut ainsi $2^{15-7}=2^8$
La plus grande pseudo-mantisse représentable sur 5 bits est représentée par $11111$, c'est-à-dire :
$2^{-1} + 2^{-2} + 2^{-3} + 2^{-4} + 2^{-5} = \frac{1}{2} + \frac{1}{4} + \frac{1}{8} + \frac{1}{16} + \frac{1}{32} = 0,5 + 0,25 + 0,125 + 0,0625 + 0,03125 = 0.96875$.
On a alors ``0 1111 11111`` qui représente $(-1)^0 \times 1,96875 \times 2^8 = 504$

### 2. Comment se représente le nombre 1 ? La précision $\epsilon$ d'une représentation est l'écart entre 1 et le nombre représentable suivant. Combien vaut $\epsilon$ pour cette représentation ?

On souhaite avoir l'exposant vrai égal à 0 et la pseudo mantisse égale à 0 également. Donc on prend l'exposant égal à 7.
Le nombre un se représente sous la forme $(-1)^0 \times 1,0 \times 2^{0}$ avec X étant la plus grande pseudo-mantisse possible.
Il se représente donc par ``0 0111 00000`` qui représente exactement le nombre 1.

Le nombre immédiatement suivant est le nombre auquel on ajoute 1 à la pseudo-mantisse, c'est-à-dire ``0 0111 00001``. On a donc ajouté $\epsilon=2^{-5}=0.03125$.

### 3. Peut on représenter 7,2 et 57,6 ? Quelles sont les nombres qui encadrent 7,2 et 57,6 dans cette représentation ?

On remarque que $7,2=1,8*2^2$. On sait déjà que l'on veut un exposant vrai égal à 2, c'est-à-dire un exposant égal à 9.
On souhaite la mantisse la plus proche de 0,8.  Or, $2^{-1} + 2^{-2} + 2^{-5} < 0,8 < 2^{-1} + 2^{-2} + 2^{-4}$.
On peut donc encadrer 7,2 par les nombres représentés de la manière suivantes : ``0 1001 11001`` et ``0 1001 11010``, qui sont les représentations respectives de $1,78125 \times 2^2 = 7,125$ et $1,8125 \times 2^2 = 7,25$

De la même manière, 52,6 est encadré par 57 et 58.

### 4. Que donne en décimal la multiplication de 7,25 et 28,5 ? Ecrivez les dans la représentation proposée et effectuez la multiplication. Quels sont les deux arrondis possibles pour le résultat et leur valeur décimale ?

On remarque que $7,25 = 1,8125 \times 2^2$, et $0,8125 = 2^{-1} + 2^{-2} + 2^{-4}$
Alors, on représente 7,25 en virgule flottante sous la forme ``0 1001 11010``, $1,11010_2 \times 2^2$

On remarque par ailleurs que $28,5=1,78125\times 2^4$ et $0,78125=2^{-1} + 2^{-2} + 2^{-5}$
Donc on représente 28,5 en virgule flottante par ``0 1011 11001``. $1,11001_{2} \times 2^4$

Alors, la multiplication de 7,25 et 28,5 se résume à :

$$
\begin{align}
7,25 \times 28,5 &= 1,11010_{2} \times 2^2 \times 1,11001_{2} \times 2^4 \\
&= (1,11010_{2} \times 1,11001_{2}) \times 2^6 \\
&= 11,001110101_{2} \times 2^6 \\
&= 1,1001110101_{2} \times 2^7 \\
\text{On tronque et arrondit} &= 1,10011_{2} \times 2^7
\end{align}
$$
Et $1,10011_{2} = 2^{-1} + 2^{-4} + 2^{-5} = 0,59375$ donc $7,25 \times 28,5 = 1,59375 \times 128 = 204$ lorsque l'on multiplie en base 2 et que l'on arrondit à l'inférieur en tronquant.
Par ailleurs, ce chiffre se représente en binaire : ``0 1110 10011``

Le résultat réel est $206.625$ donc on voit bien qu'on a arrondi.

## Exercice 6

### 1. Représenter 16, 10 et 0,75 en virgule flottante.

On remarque que $16,00 = 1,00 \times 2^4$. On sait déjà que l'on veut un exposant vrai égal à 4, c'est-à-dire un exposant égal à 11.
On souhaite la mantisse la plus proche de 0.
Ainsi, on représente 16 par le binaire suivant : ``0 1011 00000``

10 se représente par $1,25\times 2^3$, c'est-à-dire un exposant vrai égal à 10 et une mantisse la plus proche de 0,25.
Alors, on représente 10 par le binaire suivant : ``0 1010 01000``.

De même, $0,75=1,5*2^{-1}$, l'exposant vrai vaut 6 et pour la mantisse on a $0,5=2^{-1}$
C'est-à-dire que 0,75 se représente : ``0 0110 10000``

### 2. Expliciter l’addition flottante de 16 et 10. Que donne l’addition de 16 et 0,75 si on arrondit inférieurement ?


On a alors :
$$
\begin{align}
16 + 10 &= 1,00000 \times 2^4 + 1,01000 \times 2^3 \\
&= 1,00000 \times 2^4 + 0,101000 \times 2^4 \\
&= (1,00000 + 0,101000) \times 2^4 \\
&= 1,10100 \times 2^4 \\
&= 2^4 + 2^{3} + 2^1= 16+8+2 \\
&= 26
\end{align}
$$
De la même manière, on va additionner 16 et 0,75.

$$
\begin{align}
16 + 0,75 &= 1,00000 \times 2^4 + 1,10000 \times 2^{-1} \\
&= 1,00000 \times 2^4 + 0,000011 \times 2^4 \\
&= (1,00000 + 0,000011) \times 2^4 \\
&= 1,000011 \times 2^4 \\
\text{On doit arrondir pour la mantisse}
&= 1,00001 \times 2^4 \\
&= 2^4 + 2^{-1} = 16,5
\end{align}
$$

### 3. On écrit le code ci-dessous. Quelle valeur aura la variable f après l’exécution ? Et quelle aurait été sa valeur si on avait simplement écrit : ``float f = 16.0 + (10 * 0.75);``

```C
float f = 16.0;
for (i = 0; i < 10; i++)
	f = f + 0.75;
```

On sait que 16 se représente par $1,0 \times 2^4$, c'est-à-dire par ``0 1011 00000``.
On sait que 10 se représente par $1,25 \times 2^3$, c'est-à-dire par ``0 1010 01000``.
On sait que 0,75 se représente par $1,5 \times 2^{-1}$, c'est-à-dire par ``0 0110 10000``.

Déjà, on sait que $16 + 10,75 = 23,5$ donc on est sûr que toutes les additions se rapporteront en puissances de 4 puisque l'on commence à 16.
A chaque fois, on additionnera 0,75 à un chiffre exprimé en puissance de 4. Donc à chaque fois, on devra arrondir 0,75 puisqu'il sera représenté par $0,000011 \times 2^4$ et qu'on l'arrondira à $0,00001 \times 2^4$.
On ajoutera donc à chaque fois 0,5.
On se retrouvera donc avec $16 + 0,5 \times 10 = 16+5=21$

Si on avait simplement écrit ``float f = 16.0 + (10 * 0.75);``

On aurait multiplié en premier lieu 10 par 0,75 :

$$
\begin{align}
10 \times 0,75 &= 1,01 \times 2^3 \times 1,1 \times 2^{-1} \\
&= (1,01 \times 1,1) \times 2^2 \\
&= 1,111 \times 2^2 \\
\end{align}
$$
puis additionné ce résultat avec $16 = 1,0 \times {2}^4$.

$$
\begin{align}
16 + (10 \times 0,75) &= 1,0 \times 2^4 + 1,111 \times 2^2 \\
&= 1,0 \times 2^4 + 0,01111 \times 2^2 \\
&= 1,01111 \times 2^4 \\
&= 2^4 + 2^2 + 2^1 + 2^0 + 2^{-1} = 16 + 4 + 2+ 1 + 0,5 \\
&= 23,5
\end{align}
$$
Ce qui donne le résultat exact.
